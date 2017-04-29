byte Channel = 0xB0; //0xB0 (176) is the first of 16 control change channels
void setup(){
  Serial.begin(9600);    //31250 was Special baud rate for MIDI, however we using hairless-midi
//   analogReference(EXTERNAL);     //This changes the Analog voltage reference to the current maximum Luminance detected by the reference photoresistor
                                  //Not recommended to go below 0.625V. Anything above the ARef however, would become 1023 readings (i.e. max). 
}

/* 
   * The Arduino uses a 10-bit (0-1023) analogue to digital converter (ADC) on each of its analogue inputs.
   * The ADC isn't very high resolution, so if a pot is in a position such that the output voltage is 'between'
   * what it can detect (say 2.505V or about 512.5 on a scale of 0-1023) then the value read will constantly
   * fluctuate between two integers (in this case 512 and 513).

   * To combat this, we require that the analogue input value must change by a certain threshold amount before
   * we register that it is actually changing. This is good in avoiding a constantly fluctuating value, but has
   * the negative effect of a reduced input resolution. 
   * However, in this scenario, as the light intensity always changes, the threshold amount gives very little effect
   * and therefore using a delay() function would be easier to combat the noise signals
*/
void loop(){
  int number = 0;
  if (digitalRead(25) == 1){      //If switch 1 is on
    analogReference(EXTERNAL);
  }
  else if (digitalRead(25) == 0){  //If switch 1 is off
    analogReference(DEFAULT);
  }

  
  if (digitalRead(22) == 1){        //If switch 2 is on -> control the MIDI message output. if On, output. Off, stop output.
    for(int i = 0; i < 9; i++){   //we have 9 sliders, so i < 9
      int value = analogRead(i)/8;    //1024/8 = 128 (which is 7 bit essentially)
            
      sendMIDIMessages(Channel, 70+i , value);   
      delay(10);
    }
  }
  else{}
}


void sendMIDIMessages(byte channel, byte ccNumber, byte cValue){
  Serial.write(channel);    //Send MIDI CC channel
  Serial.write(ccNumber);    //Send MIDI CC messages
  Serial.write(cValue);     //Send Velocity 
}

