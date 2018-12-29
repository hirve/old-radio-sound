# old-radio-sound
The server to emulate old warm AM radio sound on Raspberry Pi

### Installation
Install dependencies
```shell
sudo apt install icecast2 ffmpeg vorbis-tools ezstream pv
```
When Icecast asks to configure it say no, because we will use the config we have in the project.


Clone the project
```shell
git clone https://github.com/hirve/old-radio-sound/
```

Build the sound processing tool
```shell
cd old-radio-sound/generate-am-radio/bin/
./build
```

Start Icecast
```shell
cd ../../icecast/
./start-icecast
```
It will start on localhost:8092 so make sure this port is free or change it in the config file.
If you want your server to be available via internet - don't forget to change passwords in icecast/icecast-config.xml and generate-am-radio/bin/play-to-stream-vorbis.xml.tpl from "hackme" to something stronger.

Edit the script generate-am-radio/stream-template-1206am
```shell
#!/bin/bash

DIR=`cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd`

$DIR/bin/stream-radio \
  "PUT_YOUR_FAVORITE_AUDIO_STREAM_HERE"\
  "PUT_HERE_ANY_BACKGROUND_STREAM"\
  1206\
  1\
  &

```
Put here your favorite audio streams and change the other parameters if you want:

1206 means the radio frequency, it will name the icecast stream like .../1206am, and also will initialize the random generator to make "air conditions" repeatable,

1 is the level of main audio stream in microvolts, the value may be in the range 1...10 or other if you like.

If all is ok after starting this script you can hear the old warm radio on localhost:8092/1206am
