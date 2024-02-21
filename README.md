# Arduino SID Music Player
Emulates the C64 SID chip on Arduino to play music files.

* Requires [SID Arduino library](https://github.com/cybernesto/sid-arduino-lib)

You can embed (short) tunes into the code using C header files, but that involves converting the music into a dump and then converting the dump into a C header array:

* Extract SID music data from SID files using [SID Dumper by Johannes Ahlebrand](https://github.com/cbmeeks/SIDDumper.git) Windows application (not to be confused with the multi-platform SID Dumper)
* JConverter.jar is required to convert dumped SID music files into C header files - this is abandonware, searching for JConverter now brings up a Joomla migration tool!

Instead I extended the example to first load a specific file from SD card (```arduino_SD_sid_player_.ino```), and then a further example to read a list of .DMP files and then pick one at random (```arduino_SD_RANDOM_sid_player.ino```)

## Player: 
Connect Pin 9, 10 and Ground:  
![C7EE5FB0-F280-4DF3-9D0F-346BD573F5B7_1_105_c](https://github.com/omiq/arduino-sid-player/assets/3143825/12d17a56-7812-40f3-be4e-6ca883c3824c)

## With SD Card: 

In addition to the above:
 * MOSI - pin 11
 * MISO - pin 12
 * CLK - pin 13
 * CS - pin 4 

Then connect 3v power, Ground.


![6C18D19F-E417-4D01-83F4-2C12D93176B2_4_5005_c](https://github.com/omiq/arduino-sid-player/assets/3143825/c48b72ab-bd48-4eca-a225-463bac40a005)
