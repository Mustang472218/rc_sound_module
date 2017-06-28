#include <pcmConfig.h>
#include <pcmRF.h>
#include <TMRpcm.h>

  #include <SD.h>       // need to include the SD library
  #define SD_ChipSelectPin 10  //using digital pin 10 on arduino nano 328, can use other pins
  #include <SPI.h>
  
  TMRpcm audio;   // create an object for use in this sketch
  
  
  unsigned long time = 0;
  int numLoop = 0;
  int numLoop1 = 0;
  int gearPos = 0;
  int throttle = 0;
  int prevThrottle = 0;
  int currThrottle = 0;
  int playingSound = 0;
  
  //RC scale Variable Declarations
  int rc_pin = 2;
  int rc_pin2 = 4;
  
  unsigned long duration;
  unsigned long prevDuration;
  unsigned long gearVal;

  

 
  void setup(){

    
     audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
    Serial.begin(9600);  
    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
      Serial.println("SD fail");  
       return;   // don't do anything more if not
    }
    else{   
      Serial.println("SD ok");   
    }
    //PLay init file to tell sound version
    Serial.println("beginsound.wav");
    audio.play("beginsound.wav");
    while(audio.isPlaying()){ 
  };

    Serial.println("setup end");
  }
  

  
  void loop(){ 
// Read ch5 for landing gear
    ++numLoop1;
     if (numLoop1 == 30000){
         noInterrupts();
         gearVal = pulseIn(rc_pin2, HIGH);
         interrupts();
         
         numLoop1 = 0;
         

        if((gearVal > 1100) && (gearVal < 1200)){
          gearPos = 0; 
          // if gear is down
        };
        
        if((gearVal > 1900) && (gearVal < 1950)){
          gearPos = 1;
          // if gear is up 
        };

        Serial.println(gearPos); 
         
     };        

  //Read throttle value

  ++numLoop;
    if (numLoop == 30000){
        noInterrupts();
        duration = pulseIn(rc_pin, HIGH);
        interrupts();
        Serial.println(duration);
        
        numLoop = 0;
        Serial.println(currThrottle);
       //Set new throttle value
        
     if(duration <= 990){
        currThrottle = 0;
     };
     if((duration > 990) && (duration <= 1040)){
        currThrottle = 1;
     };
      if((duration > 1040) && (duration <= 1167)){
        currThrottle = 2;
      };
      if((duration > 1167) && (duration <= 1332)){
        currThrottle = 3;
      };
      if((duration > 1332) && (duration <= 1550)){
        currThrottle = 4;
      };
      if((duration > 1550) && (duration <= 1664)){
        currThrottle = 5;
      };
      if((duration > 1664) && (duration <= 1870)){
        currThrottle = 6;
      };
      if(duration > 1870){
        currThrottle = 7;
      };
    
      //If currThrottle != prevThrottle set start playing new file
      if(currThrottle != prevThrottle){
        
        if((currThrottle == 0) && (prevThrottle > 0)){
             audio.play("shut.wav");
             Serial.println("shut.wav");
             while(audio.isPlaying()){}
             prevThrottle = currThrottle;
        }
        if(currThrottle == 1){
          if(currThrottle > prevThrottle)
          audio.play("start.wav");
          Serial.println("start.wav");
          while(audio.isPlaying()){}
          }
          playingSound = 1;
          prevThrottle = currThrottle;
        }
        if(currThrottle == 2){
          audio.play("1.wav");
          Serial.println("1.wav");
          prevThrottle = currThrottle;
          playingSound = 1;
        }
        if(currThrottle == 3){
          audio.play("2.wav");
          Serial.println("2.wav");
          prevThrottle = currThrottle;
          playingSound = 2;
        }
        if(currThrottle == 4){
          audio.play("3.wav");
          Serial.println("3.wav");
          prevThrottle = currThrottle;
          playingSound = 3;
        }
         if(currThrottle == 5){
          audio.play("5.wav");
          Serial.println("5.wav");
          prevThrottle = currThrottle;
          playingSound = 5;
        }
        if(currThrottle == 5 && gearPos == 1){
          audio.play("4.wav");
          Serial.println("4.wav");
          prevThrottle = currThrottle;
          playingSound = 4; 
        }
         if(currThrottle == 6){
          audio.play("4.wav");
          Serial.println("4.wav");
          prevThrottle = currThrottle;
          playingSound = 4;
        }
         if(currThrottle == 6 && gearPos == 1){
          audio.play("6.wav");
          Serial.println("6.wav");
          prevThrottle = currThrottle;
          playingSound = 6; 
        }
         if(currThrottle == 7){
          audio.play("7.wav");
          Serial.println("7.wav");
          prevThrottle = currThrottle;
          playingSound = 7;
        }

  
    
//      Serial.println(tmrpcm.isPlaying());
    
  if((currThrottle = prevThrottle) && (audio.isPlaying() == 0)){
    
        if(playingSound == 1){
          audio.play("1.wav");
          Serial.println("again 1.wav");
          prevThrottle = currThrottle;
        }
        if(playingSound == 2){
          audio.play("2.wav");
          Serial.println("again 2.wav");
          prevThrottle = currThrottle;
        }
        if(playingSound == 3){
          audio.play("3.wav");
          Serial.println("again 3.wav");
          prevThrottle = currThrottle;
        }
         if(playingSound == 4){
          audio.play("4.wav");
          Serial.println("again 4.wav");
          prevThrottle = currThrottle;
         }
         if(playingSound == 5){
          audio.play("5.wav");
          Serial.println("again 5.wav");
          prevThrottle = currThrottle;
         }
         if(playingSound == 6){
          audio.play("6.wav");
          Serial.println("again 6.wav");
          prevThrottle = currThrottle;
        }
        if(playingSound == 7){
          audio.play("7.wav");
          Serial.println("again 7.wav");
          prevThrottle = currThrottle;
           }
        }
       }  
   
      }
   
   


