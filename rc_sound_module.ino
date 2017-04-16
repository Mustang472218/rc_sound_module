  #include <SD.h>       // need to include the SD library
  #define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins
  #include <TMRpcm.h>           //  also need to include this library...
  #include <SPI.h>
  #include <Servo.h>
 
  
  TMRpcm tmrpcm;   // create an object for use in this sketch
  
  
  unsigned long time = 0;
  int numLoop = 0;
  int throttle = 0;
  int prevThrottle = 0;
  int currThrottle = 0;
  int playingSound = 0;
  
  //RC scale Variable Declarations
  int rc_pin = 2;
  unsigned long duration;
  unsigned long prevDuration;
  
 Servo myservo; // creat an object for landing light servo
 int pos = 0;



 // read gear values.
 int raw_gear;
 int pos2;

 


 
  void setup(){
    
    tmrpcm.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
    
    Serial.begin(9600);
    
    myservo.attach(9);
    
    pinMode(10, INPUT); //read gear channel values
    pos2 = 0; // assign gear value to 0 initially

    pinMode(LED_BUILTIN, OUTPUT); //SET LED TO OUPUT MODE
  
 
    if (!SD.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
      Serial.println("SD fail");  
      return;   // don't do anything more if not
    }
    else{   
      Serial.println("SD ok");   
    }
    //PLay init file to tell sound version
    Serial.println("beginsound.wav");
    tmrpcm.play("beginsound.wav");
    while(tmrpcm.isPlaying()){
    delay(2000); 
  }; 
    Serial.println("setup end");
  }

  
  void loop(){
    

       raw_gear = pulseIn(10, HIGH, 25000);

    if (raw_gear >= 1050 && raw_gear <= 1150){
      pos2 = 0;
    }
    else if (raw_gear >= 1850 && raw_gear <= 1950){
      pos2 = 1;
    }

   if (pos2 = 0){
     myservo.write(180);
     digitalWrite(LED_BUILTIN, HIGH);    
   }
   else if (pos2 = 1){
    myservo.write(0);
    digitalWrite(LED_BUILTIN, LOW);
   }
 Serial.println(pos);
 delay(100);

  
    //Read throttle value
   ++numLoop;
    if (numLoop == 30000){
        noInterrupts();
        duration = pulseIn(rc_pin, HIGH);
        interrupts();
        
        numLoop = 0;
        Serial.println(currThrottle);
        //Set new throttle value
        
     if(duration <= 990){
        currThrottle = 0;
     };
     if((duration > 990) && (duration <= 1050)){
        currThrottle = 1;
     };
      if((duration > 1050) && (duration <= 1167)){
        currThrottle = 2;
      };
      if((duration > 1167) && (duration <= 1332)){
        currThrottle = 3;
      };
      if((duration > 1332) && (duration <= 1498)){
        currThrottle = 4;
      };
      if((duration > 1498) && (duration <= 1664)){
        currThrottle = 5;
      };
      if((duration > 1664) && (duration <= 1830)){
        currThrottle = 6;
      };
      if(duration > 1830){
        currThrottle = 7;
      };
    
      //If currThrottle != prevThrottle set start playing new file
      if(currThrottle != prevThrottle){
        
        if((currThrottle == 0) && (prevThrottle > 0)){
            tmrpcm.play("shut.wav");
             Serial.println("shut.wav");
             while(tmrpcm.isPlaying()){}
             prevThrottle = currThrottle;
        }
        if(currThrottle == 1){
             if(currThrottle > prevThrottle){
             tmrpcm.play("start.wav");
             Serial.println("start.wav");
             while(tmrpcm.isPlaying()){}
             }
             playingSound = 1;
             prevThrottle = currThrottle;
        }
        if(currThrottle == 2){
          tmrpcm.play("1.wav");
          Serial.println("1.wav");
          prevThrottle = currThrottle;
          playingSound = 1;
        }
        if(currThrottle == 3){
          tmrpcm.play("2.wav");
          Serial.println("2.wav");
          prevThrottle = currThrottle;
          playingSound = 2;
        }
        if(currThrottle == 4){
          tmrpcm.play("3.wav");
          Serial.println("3.wav");
          prevThrottle = currThrottle;
          playingSound = 3;
        }
         if(currThrottle == 5){
          tmrpcm.play("4.wav");
          Serial.println("4.wav");
          prevThrottle = currThrottle;
          playingSound = 4;
        }
         if(currThrottle == 6){
          tmrpcm.play("5.wav");
          Serial.println("flyby.wav");
          prevThrottle = currThrottle;
          playingSound = 5;
         }
         if(currThrottle == 7){
          tmrpcm.play("6.wav");
          Serial.println("whistle.wav");
          prevThrottle = currThrottle;
          playingSound = 6;
        }

        // DON'T FORGET THE TAKEOFF SOUND!!!
    }
    // Serial.println(tmrpcm.isPlaying());
     if((currThrottle = prevThrottle) && (tmrpcm.isPlaying() == 0)){
    
        if(playingSound == 1){
          tmrpcm.play("1.wav");
          Serial.println("again 1.wav");
          prevThrottle = currThrottle;
        }
        if(playingSound == 2){
          tmrpcm.play("2.wav");
          Serial.println("again 2.wav");
          prevThrottle = currThrottle;
        }
        if(playingSound == 3){
          tmrpcm.play("3.wav");
          Serial.println("again 3.wav");
          prevThrottle = currThrottle;
        }
         if(playingSound == 4){
          tmrpcm.play("4.wav");
          Serial.println("again 4.wav");
          prevThrottle = currThrottle;
         }
         if(playingSound == 5){
          tmrpcm.play("5.wav");
          Serial.println("again 5.wav");
          prevThrottle = currThrottle;
         }
         if(playingSound == 6){
          tmrpcm.play("6.wav");
          Serial.println("again 6.wav");
          prevThrottle = currThrottle;
        }
     }
  }
}

