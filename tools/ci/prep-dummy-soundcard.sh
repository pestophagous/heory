#!/bin/bash

set -Eeuxo pipefail # https://vaneyckt.io/posts/safer_bash_scripts_with_set_euxo_pipefail/

cat << EOF > $HOME/.asoundrc
       pcm.dummy {
          type hw
          card 0
       }

       ctl.dummy {
          type hw
          card 0
       }
EOF
chmod go+r $HOME/.asoundrc

sudo bash -c 'cat << EOF >> /etc/modules.conf
# OSS/Free portion - card #1
alias sound-slot-0 snd-card-0
alias sound-service-0-0 snd-mixer-oss
alias sound-service-0-1 snd-seq-oss
alias sound-service-0-3 snd-pcm-oss
alias sound-service-0-8 snd-seq-oss
alias sound-service-0-12 snd-pcm-oss
EOF'
sudo modprobe snd-dummy || true  # not working (as of Apr 5, 2020)
sudo modprobe snd-seq || true  # not working (as of Apr 5, 2020)
find /lib/modules/    # no snd modules present (as of Apr 5, 2020)
