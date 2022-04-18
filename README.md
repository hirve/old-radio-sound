:warning: I was walking down the street when a rocket landed next to me. Some time ago it was simply unbelievable, now the destruction of my city and the killing of civilians is my reality. The organized criminal group has occupied Russia and now is destroying my peaceful city. 

<a title="Mvs.gov.ua, CC BY 4.0 &lt;https://creativecommons.org/licenses/by/4.0&gt;, via Wikimedia Commons" href="https://commons.wikimedia.org/wiki/File:Bomb_attack_on_Saltivske_tram_depot_in_Kharkiv.jpg"><img width="99%" alt="Bomb attack on Saltivske tram depot in Kharkiv" src="https://upload.wikimedia.org/wikipedia/commons/c/cf/Bomb_attack_on_Saltivske_tram_depot_in_Kharkiv.jpg"></a>

<a title="Main Directorate of the State Emergency Service of Ukraine in Kharkiv Oblast, CC BY 4.0 &lt;https://creativecommons.org/licenses/by/4.0&gt;, via Wikimedia Commons" href="https://commons.wikimedia.org/wiki/File:Kharkiv_after_Russian_shelling,_31_March_2022_(14).jpg"><img width="99%" alt="Kharkiv after Russian shelling, 31 March 2022 (14)" src="https://upload.wikimedia.org/wikipedia/commons/thumb/8/85/Kharkiv_after_Russian_shelling%2C_31_March_2022_%2814%29.jpg/1280px-Kharkiv_after_Russian_shelling%2C_31_March_2022_%2814%29.jpg"></a>

<a title="Photo: Kharkivian (Serhii Petrov). From Wikimedia Commons. License CC BY-SA 4.0.Фото: Kharkivian (Сергій Петров). З Wikimedia Commons. Ліцензія CC BY-SA 4.0" href="https://commons.wikimedia.org/wiki/File:Destroyed_apartment_building_3_Kholodnohirska_Street,_Kharkiv_after_Russian_airstrike_by_Kharkivian_(03.2022)_01.jpg"><img width="99%" alt="Destroyed apartment building 3 Kholodnohirska Street, Kharkiv after Russian airstrike by Kharkivian (03.2022) 01" src="https://upload.wikimedia.org/wikipedia/commons/thumb/a/a1/Destroyed_apartment_building_3_Kholodnohirska_Street%2C_Kharkiv_after_Russian_airstrike_by_Kharkivian_%2803.2022%29_01.jpg/1280px-Destroyed_apartment_building_3_Kholodnohirska_Street%2C_Kharkiv_after_Russian_airstrike_by_Kharkivian_%2803.2022%29_01.jpg"></a>

If you are a responsible citizen of Russia, you are personally guilty of this. Stop it. If you are an irresponsible resident of Russia, just ignore this message.

# old-radio-sound
The server to emulate old warm AM radio sound on Raspberry Pi

### The video how it works
https://youtu.be/I7pTWe61BHY

### Installation
Install dependencies
```shell
sudo apt install git icecast2 ffmpeg vorbis-tools ezstream pv
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
It will start on **localhost:8092** so make sure this port is free or change it in the config file.
If you want your server to be available via internet - don't forget to change passwords in **icecast/icecast-config.xml** and **generate-am-radio/bin/play-to-stream-vorbis.xml** from "hackme" to something stronger.

Go to **generate-am-radio** folder
```shell
cd ../generate-am-radio/
```
and edit the script **stream-template-1206am**
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

- **1206** means the radio frequency, it will name the icecast stream like .../**1206am**, and also will initialize the random generator to make "air conditions" repeatable,

- **1** is the level of main audio stream in microvolts, the value may be in the range **1...10** or other if you like.

If all is ok after starting this script you can hear the old warm radio on **localhost:8092/1206am**

You can copy this script with different audio streams and different frequencies and run them simultaneously, for me it worked well with about 5 streams on Raspberry Pi 2.
