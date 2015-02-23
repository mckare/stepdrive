

// Define our three input button pins
#define  LEFT_PIN  4
#define  STOP_PIN  3
#define  RIGHT_PIN 2


// Define our analog pot input pin
#define  RAMP_PIN 1
#define  SPEED_PIN 0

#define DIR_PIN 9
#define STEP_PIN 8

char sign;

void setup() { 
  pinMode(DIR_PIN, OUTPUT); 
  pinMode(STEP_PIN, OUTPUT); 
  
  pinMode(LEFT_PIN, INPUT_PULLUP);
  pinMode(STOP_PIN, INPUT_PULLUP);
  pinMode(RIGHT_PIN, INPUT_PULLUP);
  Serial.begin(9600);
} 

void loop(){ 
 
  
  if (digitalRead(LEFT_PIN) == 0 ) {
    sign = 1;
     Serial.println("LEFT");
      
   
  }
  else if (digitalRead(RIGHT_PIN) == 0 ) {    
    sign = -1;
     Serial.println("RIGHT");
  }
  else if (digitalRead(STOP_PIN) == 0) {
    sign = 0;
    Serial.println("DUR");
    
  }
  //rotate a specific number of degrees 


 
  unsigned int rampVAL = analogRead(RAMP_PIN);
  rampVAL= map( rampVAL, 0, 1023, 0 , 10);
    
  
  // print out the value you read:

 
 rampVAL = constrain(rampVAL, 0, 10);

  switch (rampVAL) 
  {
  case 10:    // your hand is on the sensor
    rampVAL =  1;
    Serial.println ((rampVAL),DEC);
    break;
  case 9:    // your hand is close to the sensor
    rampVAL = .9 ;
      Serial.println (rampVAL);
    break;
  case 8:    // your hand is a few inches from the sensor
     rampVAL = .8 ;
       Serial.println (rampVAL);
    break;
  case 7:    // your hand is nowhere near the sensor
    rampVAL = .7 ;
      Serial.println (rampVAL);
    break;
    case 6:    // your hand is nowhere near the sensor
     rampVAL = .6 ;
       Serial.println (rampVAL);
    break;
    case 5:    // your hand is nowhere near the sensor
     rampVAL = .5 ;
       Serial.println (rampVAL);
    break;
    case 4:    // your hand is nowhere near the sensor
      rampVAL = .4 ;
        Serial.println (rampVAL);
    break;
    case 3:    // your hand is nowhere near the sensor
     rampVAL = .3 ;
       Serial.println (rampVAL);
    break;
    case 2:    // your hand is nowhere near the sensor
     rampVAL = .2 ;
       Serial.println (rampVAL);
    break;
    case 1:    // your hand is nowhere near the sensor
    rampVAL = .1 ;
      Serial.println (rampVAL);
    break;
  } 
  

 

 
  rotate(sign * 360, rampVAL); 
 Serial.print ("RAMP"); 

delay(500);





 // rotateDeg(-360, 1);  //reverse
 // delay(1000); 


  //rotate a specific number of microsteps (8 microsteps per step)
  //a 200 step stepper would take 1600 micro steps for one full revolution
//rotate(sign * 360, ); 


 // rotate(-1600, .25); //reverse
 // delay(1000); 
}



void rotate(int steps, float speed){ 
  //rotate a specific number of microsteps (8 microsteps per step) - (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (steps > 0)? HIGH:LOW;
  steps = abs(steps);

  digitalWrite(DIR_PIN,dir); 
int speedVAL= analogRead(SPEED_PIN);
   speedVAL= map( speedVAL, 0, 1023, 50, 100);
  float usDelay = (1/speed) *  speedVAL ;
Serial.print ("Speed"); 
Serial.print (speedVAL);
  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
} 

void rotateDeg(float deg, float speed){ 
  //rotate a specific number of degrees (negitive for reverse movement)
  //speed is any number from .01 -> 1 with 1 being fastest - Slower is stronger
  int dir = (deg > 0)? HIGH:LOW;
  digitalWrite(DIR_PIN,dir); 

  int steps = abs(deg)*(1/0.225);
  float usDelay = (1/speed) * 50;

  for(int i=0; i < steps; i++){ 
    digitalWrite(STEP_PIN, HIGH); 
    delayMicroseconds(usDelay); 

    digitalWrite(STEP_PIN, LOW); 
    delayMicroseconds(usDelay); 
  } 
}
