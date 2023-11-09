/*
 * MIDIUSB_test.ino
 *
 * Created: 12/10/2021
 * Author: Nazo Tajrian
 * Modified by Nazo Tajrian (2021)
 */ 
#include "MIDI.h"

MIDI_CREATE_DEFAULT_INSTANCE();

boolean btnAOn = false;
boolean btnBOn = false;
boolean btnCOn = false;
int currentPC = 0;

const int MidiChannel = 1;
const int ButtonPins[3] = {2, 3, 4};
int LastButtonState[3] = {0};
int ccDelayValue = 300;
int pcDelayValue = 500;
boolean looperMode = false;

void setup() {
 
for(int i=0; i < 3; i++)
  pinMode(ButtonPins[i],INPUT_PULLUP);
 
  MIDI.begin(MIDI_CHANNEL_OFF);        
}


void loop() {
   boolean btnA = !digitalRead(4); 
   boolean btnB = !digitalRead(3); 
   boolean btnC = !digitalRead(2); 
   boolean isPCChange = false; 
   
   if(btnB && btnC && !btnA)
   {
        isPCChange = true;
         currentPC = currentPC + 1;
         MIDI.sendProgramChange(currentPC, MidiChannel);
          //_time = millis();
          delay(pcDelayValue);
          
                          
    }else if(btnB && btnA && !btnC)
      {
           isPCChange = true;
            currentPC = currentPC - 1;
           MIDI.sendProgramChange(currentPC, MidiChannel);
            delay(pcDelayValue);
                         
     }

       if(!isPCChange)
       {
         for(int i=0; i < 3; i++)
         {
       
              boolean curentPinPressed = !digitalRead(ButtonPins[i]); 
       
              
                   
                  
              if (curentPinPressed != LastButtonState[i])
              {
                 LastButtonState[i] = curentPinPressed;
                         
                
                 if (curentPinPressed)
                 {      
                        
                           switch(ButtonPins[i])
                            {
                              case 4:  
                                       MIDI.sendControlChange(86,127,MidiChannel); 
                                       delay(ccDelayValue);        
//                                  if(btnAOn)
//                                    {
//                                       MIDI.sendControlChange(86,0,MidiChannel); 
//                                       delay(ccDelayValue);
//                                    }else{
//                                       MIDI.sendControlChange(86,127,MidiChannel); 
//                                       delay(ccDelayValue);
//                                    }                      
//                                    btnAOn = !btnAOn;                      
                                  break;                       
                               case 3:
                                 if(btnBOn)
                                    {
                                       MIDI.sendControlChange(87,0,MidiChannel); 
                                       delay(ccDelayValue);
                                    }else{
                                       MIDI.sendControlChange(87,127,MidiChannel); 
                                       delay(600);
                                    } 
                                    btnBOn = !btnBOn;  
                                 break;                            
                               case 2:
                                       MIDI.sendControlChange(88,127,MidiChannel); 
                                       delay(ccDelayValue);
//                                 if(btnCOn)
//                                    {
//                                       MIDI.sendControlChange(88,0,MidiChannel); 
//                                       delay(ccDelayValue);
//                                    }else{
//                                      MIDI.sendControlChange(88,127,MidiChannel); 
//                                      delay(ccDelayValue);
//                                    } 
//                                    btnCOn = !btnCOn;  
                                  break;
                            
                             }
                          
                        
                  
                      }else{
                                 switch(ButtonPins[i])
                                 {
                                  case 4: 
                                              MIDI.sendControlChange(86,0,MidiChannel); 
                                              delay(ccDelayValue);
                                  break;
        
                                  case 2:
                                               MIDI.sendControlChange(88,0,MidiChannel); 
                                               delay(ccDelayValue);
                                  break;
                                  }
                        }
      
                 }
                
              }  
       }
       
    
        
}
