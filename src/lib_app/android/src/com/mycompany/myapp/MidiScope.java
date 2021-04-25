package com.mycompany.myapp;

import android.app.Activity;
import android.content.Intent;
import android.content.Context;
import android.media.midi.MidiManager;
import android.media.midi.MidiReceiver;
import android.media.midi.MidiDeviceService;
import android.media.midi.MidiDeviceStatus;
import android.media.midi.MidiDeviceInfo;
import android.media.midi.MidiDeviceInfo.PortInfo;
import android.net.Uri;
import android.os.Bundle;
import android.os.Debug;
import android.util.Log;
import java.io.IOException;

// Heavily inspired/copied from https://github.com/philburk/android-midisuite
//
// This whole file/class is here as a placeholder right now. As you can see,
// none of the methods do anything other than log. These ARE being called when
// the app runs, despite doing nothing but log. Our app is doing what we want
// without needing any logic in this class, which probably means we do not need
// this class at all. But I am keeping it in case I find a reason to use these
// hooks. I am doing this out of laziness, so I don't have to re-research how to
// add a MidiDeviceService to a Qt Android app later on.
public class MidiScope extends MidiDeviceService {

  public static void pleaseStart(Context context) {
    context.startService(new Intent(context, MidiScope.class));
    Log.d("MyAppActivity", "(our unused service) MidiScope pleaseStart");
  }

  @Override
  public void onCreate() {
    super.onCreate();
    // Not sure if we would be expected to start a thread here or something?
    // As it stands, onCreate seems to be followed IMMEDIATELY by onDestroy.
    Log.d("MyAppActivity", "(our unused service) MidiScope onCreate");
  }

  @Override
  public void onDestroy() {
    super.onDestroy();
    Log.d("MyAppActivity", "(our unused service) MidiScope DESTROYED");
  }

  @Override
  public MidiReceiver[] onGetInputPortReceivers() {
    Log.d("MyAppActivity", "(our unused service) MidiScope onGetInputPortReceivers");
    return new MidiReceiver[]{};
  }
}
