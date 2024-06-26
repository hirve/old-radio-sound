# Old Radio Sound
<img src="https://github.com/hirve/old-radio-sound/blob/master/receiver.jpg" alt="The old receiver photo." width="100%">
The server to emulate old warm AM radio sound on Raspberry Pi

### The video how it works
https://youtu.be/I7pTWe61BHY

### Installation
Install dependencies
```shell
sudo apt install git icecast2 ffmpeg pv
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
<br/>
<img src="https://github.com/hirve/old-radio-sound/blob/master/dissident-receiver.jpg" alt="The old receiver photo." width="100%">

### Usage
Start Icecast
```shell
cd ../../icecast/
./start-icecast
```
It will start on **localhost:8092** so make sure this port is free or change it in the config file.
If you want your server to be available via internet - don't forget to change passwords in **icecast/icecast-config.xml** and **generate-am-radio/bin/stream-radio** from "hackme" to something stronger.

Go to **generate-am-radio** folder
```shell
cd ../generate-am-radio/
```
and edit the script **stream-template-1206am**
```shell
#!/bin/bash

DIR=`cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd`

$DIR/bin/stream-radio \
  "PUT_YOUR_FAVORITE_AUDIO_STREAM_HERE" \
  "PUT_HERE_ANY_BACKGROUND_STREAM" \
  1206 \
  1 \
  "Radio Station Name or City" \
  &

```
Put here your favorite audio streams and change the other parameters if you want:

- **1206** means the radio frequency, it will name the icecast stream like .../**1206am.ogg**, and also will initialize the random generator to make "air conditions" repeatable,

- **1** is the level of main audio stream in microvolts, the value may be in the range **1...10** or other if you like.

If all is ok after starting this script you can hear the vintage AM radio on **localhost:8092/1206am.ogg**

You can copy this script with different audio streams and different frequencies and run them simultaneously, for me it worked well with about 5 streams on Raspberry Pi 2.

<br/>
<img src="https://github.com/hirve/old-radio-sound/blob/master/radio-scale.jpg" alt="The old receiver photo." width="100%">

### Autostart and restart of some streams

```shell
./start-some-streams
```
Now it's just a test mode, this script may be unstable.

To set streams you want to watch, edit the line:
```shell
streams='stream-template-1206am one-more-radio-station-1035am'
```
Notice that this script takes frequency from the station script name (stream-template-**1206am**).
