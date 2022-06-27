//General Notes: MOSFET Driver SIG pin connects to GPIO pin on Arduino. MOSFET must be programmed in order to use. 


#define control 11 


const int in1 = 8;  //Default value: 14, can be any input pin 
const int in2 = 7;  //Default value: 15, can be any input pin 
const int in3 = 2;  //Default value: 16, can be any input pin 
const int in4 = 5;  //Default value: 17, can be any input pin 

//NOTE: Numbers appearing after " = " is the pin number on the Arduino Nano. EX: ENA = 9 represents D9 on Nano (PWM)

//Motor A Enable Lines (Need to be PWM (Pulse Width Modulation))
const int ENA = 9;
//Motor B Enable Lines (Need to be PWM (Pulse Width Modulation))
const int ENB = 10;

//Front Ultrasonic Sensor 
const int trig_front = 13;
const int echo_front = 12;

//Left Ultrasonic Sensor
const int trig_left = 3;
const int echo_left = A1;

//Right Ultrasonic Sensor
const int trig_right = 6;
const int echo_right = 4;

long duration_frontsensor; 
long duration_leftsensor;
long duration_rightsensor; 
int front_distance; 
int left_distance;
int right_distance; 


void setup() //Always need to run a setup 
{
 //Set all motor control pins outputs 
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT); 
 pinMode(in1, OUTPUT);
 pinMode(in2, OUTPUT);
 pinMode(in3, OUTPUT);
 pinMode(in4, OUTPUT);
 //Set all sensor pin I/O 
 pinMode(trig_front, OUTPUT); 
 pinMode(echo_front, INPUT);  
 pinMode(trig_right, OUTPUT); 
 pinMode(echo_right, INPUT); 
 pinMode(trig_left, OUTPUT); 
 pinMode(echo_left, INPUT); 
 //Set Vacuum Cleaner to 11 
 pinMode(control, OUTPUT); 
 Serial.begin(9600); 
 
}


//Pseudocode for ultrasonic sensor integration 
//Front sensor = sensor_1; Right sensor = sensor_2; Left sensor = sensor_3
//Check only front sensor ALL the time. If (sensor_1 distance < 5 (or 10) inches), check right and left sensors. 
//Whichever sensor has the most distance, turn towards that direction at a random angle range between 20-50 degrees 


void loop()
{ 

  digitalWrite(control, HIGH); 
  
  //Front ultrasonic sensor

  digitalWrite(trig_front, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trig_front, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(trig_front, LOW); 
  duration_frontsensor = pulseIn(echo_front, HIGH); 
  front_distance = duration_frontsensor * 0.0344 / 2;
  Serial.print("Front Distance: "); 
  Serial.print(front_distance);
  
   if (front_distance >= 55) {

    //Function to run motors in both directions at fixed speeds 
    //Turning on Motor A 

    digitalWrite(in1, LOW); 
    digitalWrite(in2, HIGH); 

    //Set speed to 200 out of 0-255
    analogWrite(ENA, 125); 

    //Turning on Motor B 
  
    digitalWrite(in3, LOW); 
    digitalWrite(in4, HIGH); 
  
    //Set speed to 200 out of 0-255
    analogWrite(ENB, 130);  //Set 5 more higher than ENA   
      
  } else {

    //Take into account of right and left sensors 
    digitalWrite(trig_left, LOW);
    digitalWrite(trig_right, LOW); 
    delayMicroseconds(2); 
    digitalWrite(trig_left, HIGH); 
    digitalWrite(trig_right, HIGH); 
    delayMicroseconds(10); 
    digitalWrite(trig_left, LOW); 
    digitalWrite(trig_right, LOW); 
    duration_leftsensor = pulseIn(echo_left, HIGH); 
    duration_rightsensor = pulseIn(echo_right, HIGH);
    left_distance = duration_leftsensor * 0.0344 / 2;
    right_distance = duration_rightsensor * 0.0344 / 2;
    Serial.print("Right Distance: ");
    Serial.print(right_distance); 
    Serial.print("Left Distance: "); 
    Serial.print(left_distance); 

    if (right_distance > left_distance) {

      //Turn right 
      //If turns other way, might have to switch a pair from LOW-HIGH to HIGH-LOW

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 

      //Back up 
      digitalWrite(in1, HIGH); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW); 
      delay(500);

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 

      //Turn at an angle towards the right
      
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH); 
      digitalWrite(in4, LOW);
      
      delay(random(400,600)); //Turns for this amount of time 

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 

    } else { 

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 
      
      //Back up
      digitalWrite(in1, HIGH); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, HIGH);
      digitalWrite(in4, LOW); 
      delay(500);

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 
      
      //Turn at an angle towards the left
      digitalWrite(in1, LOW);
      digitalWrite(in2, HIGH);
      digitalWrite(in3, HIGH); 
      digitalWrite(in4, LOW); 
      delay(random(400,600)); //Turns for this amount of time (might set to random time later)

      //Stop
      digitalWrite(in1, LOW); 
      digitalWrite(in2, LOW); 
      digitalWrite(in3, LOW);
      digitalWrite(in4, LOW);
      delay(500); 
    }   
  }
}
