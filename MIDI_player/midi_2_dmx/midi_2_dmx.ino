// welcome to MIDI to DMX by moritz Simon geist.
// Ressources, setup and hardware: http://sonicrobots.com/?p=864
// DmxSimple is available from: http://code.google.com/p/tinkerit/
// Help and support: http://groups.google.com/group/dmxsimple       */

#include <DmxSimple.h>
byte incomingByte;
byte note;
byte velocity;
int statusLed = 13;   // select the pin for the LED
int action=2; //0 =note off ; 1=note on ; 2= nada

void setup() {
    pinMode(statusLed,OUTPUT);   // declare the LED's pin as output
  //start serial with midi baudrate 31250 or 38400 for debugging
  Serial.begin(31250);       
  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */

  DmxSimple.usePin(3);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */

  DmxSimple.maxChannel(5);

}
void loop () {
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    // wait for as status-byte, channel 1, note on or off
    if (incomingByte== 144){ // note on message starting starting
      action=1;
    }else if (incomingByte== 128){ // note off message starting
      action=0;
    }else if (incomingByte== 208){ // aftertouch message starting
       //not implemented yet
    }else if (incomingByte== 160){ // polypressure message starting
       //not implemented yet
    }else if ( (action==0)&&(note==0) ){ // if we received a "note off", we wait for which note (databyte)
      note=incomingByte;
      playNote(note, 0);
      note=0;
      velocity=0;
      action=2;
    }else if ( (action==1)&&(note==0) ){ // if we received a "note on", we wait for the note (databyte)
      note=incomingByte;
    }else if ( (action==1)&&(note!=0) ){ // ...and then the velocity
      velocity=incomingByte;
      playNote(note, velocity);
      note=0;
      velocity=0;
      action=0;
    }else{
      //nada
    }
  }
}

void playNote(byte note, byte velocity){
  int value=0;
  if (velocity >10){
      value=255;
  }else{
   value=0;
  }
  // =DEVICE 1=
  // DMX CHANEL 1: "2" for seting DMX Mode
  // DMX CHANEL 2: 0 .. 255 Control Red     --> .... MIDI Note "1" (possible C-2)
  // DMX CHANEL 3: 0 .. 255 Control Green   --> .... MIDI Note "2"
  // DMX CHANEL 4: 0 .. 255 Control Blue    --> .... MIDI Note "3"
  // DMX CHANEL 5: NADA
  
  // =DEVICE 2=
  // DMX CHANEL 8: "2" for seting DMX Mode  
  // DMX CHANEL 9: 0 .. 255 Control Red      --> .... MIDI Note 4
  // DMX CHANEL 10: 0 .. 255 Control Green   --> .... MIDI Note 5
  // DMX CHANEL 11: 0 .. 255 Control Blue    --> .... MIDI Note 6
  // DMX CHANEL 12: NADA
  
  

// ADAPT THIS to match your Midi Notes to your DMX Channels
 if(note>=1 && note<10){

    switch (note) {
    case 1:
    DmxSimple.write(2, velocity); 
      break;
    case 2:
    DmxSimple.write(3, velocity); 
      break;
    case 3:
    DmxSimple.write(4, velocity); 
      break;
    case 4:
    DmxSimple.write(9, velocity); 
      break;
    case 5:
    DmxSimple.write(10, velocity); 
      break;
    case 6:
    DmxSimple.write(11, velocity); 
      break;
      //[ ... ] add more channels
  }
   

 }

}

