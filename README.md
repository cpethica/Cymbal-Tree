# Cymbal Tree

Midi controlled, solenoid driven cymbal tree. Solenoids either hit cymbals directly or drive levered beaters.

![](Images/concept.jpg)

![](Images/fact_install.jpg)

## Hardware

[Midi solenoid driver](http://www.j-omega.co.uk/MTP/mtp.shtml#content)

Wemos D1 mini

Solenoids - be careful of maximum current draw!

![](Images/midi_brain.jpg)

## Wiring Diagram

![](Images/brain_outputs.jpg)

## Interface

Wemos D1 mini

[SD card module](https://github.com/espressif/arduino-esp32/tree/master/libraries/SD)

[midi output](https://www.arduino.cc/en/Tutorial/Midi)

Changeover switch - switches from Midi from SD card to Midi from other device via socket on box.

## Software

MIDI_player_switch_control:
Plays midi file stored on SD in loop. Midi file must be stored on the SD card root directory and named the same as file on line 43.

OTA update:
Built in OTA update feature for wireless boards [thanks to jeroenvermeulen](https://github.com/jeroenvermeulen/JeVe_EasyOTA)
