package com.mycompany.myapp;

import android.app.Activity;
import android.content.Intent;
import android.media.midi.MidiDevice;
import android.media.midi.MidiDeviceInfo.PortInfo;
import android.media.midi.MidiDeviceInfo;
import android.media.midi.MidiDeviceService;
import android.media.midi.MidiDeviceStatus;
import android.media.midi.MidiInputPort;
import android.media.midi.MidiManager.DeviceCallback;
import android.media.midi.MidiManager;
import android.media.midi.MidiOutputPort;
import android.media.midi.MidiReceiver;
import android.net.Uri;
import android.os.Bundle;
import android.os.Debug;
import android.os.Handler;
import android.os.Looper;
import android.util.Log;
import java.io.IOException;

import org.qtproject.qt5.android.bindings.QtActivity;

class MyJavaNatives
{
    // declare the native method
    public static native void onIncomingMidi(int n);
}

public class MyAppActivity extends QtActivity
{
  private static MyAppActivity s_activity = null;

  // Midi logic heavily inspired/copied from https://github.com/philburk/android-midisuite
  private MidiManager m_midiManager;
  private MidiDevice m_openDevice;
  private MidiReceiver m_loggingReceiver;
  private MidiInputPort m_inputPort;
  private MidiOutputPort m_outputPort;
  private MyDeviceCallback m_myDeviceCallback;

  private void logByteArray(String prefix, byte[] value, int offset, int count) {
    StringBuilder builder = new StringBuilder(prefix);
    for (int i = 0; i < count; i++) {
      builder.append(String.format("0x%02X", value[offset + i]));
      if (i != count - 1) {
        builder.append(", ");
      }
    }
    Log.d("MyAppActivity","logByteArray " + builder.toString());
    MyJavaNatives.onIncomingMidi(2);
  }

  class MyDirectReceiver extends MidiReceiver {
    @Override
    public void onSend(byte[] data, int offset, int count,
                       long timestamp) throws IOException {
      String prefix = String.format("0x%08X, ", timestamp);
      logByteArray(prefix, data, offset, count);
    }
  }


  protected class MyDeviceCallback extends DeviceCallback {

    private int findPortI(final MidiDeviceInfo info, int type) {
      PortInfo[] ports = info.getPorts();
      for (PortInfo portInfo : ports) {
        if (portInfo.getType() == type ) {
          return portInfo.getPortNumber();
        }
      }
      Log.d("MyAppActivity", "no PortInfo with type 1");
      return 1;
    }

    @Override
    public void onDeviceAdded(final MidiDeviceInfo info) {

      m_midiManager.openDevice(info, new MidiManager.OnDeviceOpenedListener() {
          // TODO: Don't run the callback on the UI thread because openOutputPort might take a while.
          @Override
          public void onDeviceOpened(MidiDevice device) {
            if (device == null) {
              Log.d("MyAppActivity", "null device in onDeviceOpened");
            } else {
              m_openDevice = device;
              Log.d("MyAppActivity", "success (it seems?) in onDeviceOpened");

              m_outputPort = m_openDevice.openOutputPort(findPortI(info, MidiDeviceInfo.PortInfo.TYPE_OUTPUT));
              if (m_outputPort == null) {
                Log.d("MyAppActivity", "null result from openOutputPort");
              } else {
                Log.d("MyAppActivity", "after openOutputPort, going to CONNECT it...");
                m_outputPort.connect(m_loggingReceiver);
              }

              m_inputPort = m_openDevice.openInputPort(findPortI(info, MidiDeviceInfo.PortInfo.TYPE_INPUT));
              if (m_inputPort == null) {
                Log.d("MyAppActivity", "null result from openInputPort");
              }
            }
          }
        }, null); // end call to m_midiManager.openDevice
    }

    @Override
    public void onDeviceRemoved(final MidiDeviceInfo device) {
      Log.d("MyAppActivity", "onDeviceRemoved");
    }

    public String formatDeviceInfo(MidiDeviceInfo info) {
      StringBuilder sb = new StringBuilder();
      if (info != null) {
        Bundle properties = info.getProperties();
        for (String key : properties.keySet()) {
          Object value = properties.get(key);
          sb.append(key).append(" = ").append(value).append('\n');
        }
        for (PortInfo port : info.getPorts()) {
          sb.append((port.getType() == PortInfo.TYPE_INPUT) ? "input"
                    : "output");
          sb.append("[").append(port.getPortNumber()).append("] = \"").append(port.getName()
                                                                              + "\"\n");
        }
      }
      return sb.toString();
    }

    @Override
    public void onDeviceStatusChanged(final MidiDeviceStatus status) {
      Log.d("MyAppActivity", "onDeviceStatusChanged");

      if (status.isInputPortOpen(0)) {
        Log.d("MyAppActivity","main === connected ===");
        String text = formatDeviceInfo(status.getDeviceInfo());
        Log.d("MyAppActivity","main - "+text);
      } else {
        Log.d("MyAppActivity","main --- disconnected ---");
      }
    }
  } // protected class MyDeviceCallback

  @Override
  public void onCreate(Bundle savedInstanceState)
  {
    super.onCreate(savedInstanceState);
    s_activity = this;

    m_myDeviceCallback = new MyDeviceCallback();
    // Setup MIDI
    m_midiManager = (MidiManager) getSystemService(MIDI_SERVICE);
    Log.d("MyAppActivity", "called getSystemService MIDI_SERVICE");

    MidiScope.pleaseStart(s_activity.getApplicationContext());
    // Receiver that prints the messages.
    m_loggingReceiver = new MyDirectReceiver();
    m_midiManager.registerDeviceCallback(m_myDeviceCallback,
                                         new Handler(Looper.getMainLooper()));
  }

  @Override
  protected void onDestroy()
  {
    super.onDestroy();
    s_activity = null;
  }

  public static void sendMailWithSubject(String subject, String body)
  {
    Log.d("MyAppActivity", "in custom java for sendMail");
    Log.d("MyAppActivity", "s_activity=" + s_activity);
    if (null == s_activity){
      return;
    }

    try
    {
      Uri uri = Uri.parse("mailto:noreply@replaceme_TODO.com")
                .buildUpon()
                .appendQueryParameter("subject", subject)
                .appendQueryParameter("body", body)
                .build();
      Intent intent = new Intent(Intent.ACTION_SEND, uri);
      intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK); // | Intent.FLAG_ACTIVITY_MULTIPLE_TASK);

      intent.setType("message/rfc822"); // supposedly unnecessary, but I needed it.

      // https://stackoverflow.com/questions/8701634/send-email-intent
      // These SHOULD BE REDUNDANT (given the above), but may be useful on some Android versions.
      intent.putExtra(Intent.EXTRA_EMAIL, new String[] {"noreply@replaceme_TODO.com"});
      intent.putExtra(Intent.EXTRA_SUBJECT, subject);
      intent.putExtra(Intent.EXTRA_TEXT, body);

      Intent mailer = Intent.createChooser(intent, "Send mail...");
      mailer.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
      if(mailer == null)
      {
        Log.e("MyAppActivity", "Couldn't get Mail Intent");
        return;
      }
      Log.d("MyAppActivity", "custom java code: got mailer");

      s_activity.getApplicationContext().startActivity(mailer);
    }
    catch (android.content.ActivityNotFoundException ex)
    {
      Log.e("MyAppActivity", "caught android.content.ActivityNotFoundException");
      ex.printStackTrace();
    }

    Log.d("MyAppActivity", "java-code: sendMail(): END");
  }

  public static boolean isAndroidDebuggerConnected()
  {
    Log.d("MyAppActivity", "call to isAndroidDebuggerConnected");
    return Debug.isDebuggerConnected();
  }

  // TODO: add isRunningGoogleFirebaseAutomatedTests https://stackoverflow.com/questions/43598250/how-to-detect-running-in-firebase-test-lab
  //   (we want to make all alerts auto-expire/auto-hide in firebase, so their
  //    "blind" click-everywhere test bot isn't stuck with a modal popup)
}
