int calibrationTime = 1;
String vo;

//led
int
led1 = 51,
led2 = 52,
led3 = 53;

//ultrasonic sensor // defines pins numbers
const int trigPin = 7;
const int echoPin = 6;

// defines variables
long duration;
int distance;
int counter = 0;

//servo
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
int gate = 2;

//SETUP
void setup() {
  Serial.begin(9600);
  delay(10); //Delay added to make thing stable

  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
  pinMode(led3, OUTPUT);

  myservo.attach(gate);  // attaches the servo on pin 2 to the servo object

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input

  //give the sensor some time to calibrate
  Serial.print("calibrating sensor ");
  for (int i = 0; i < calibrationTime; i++) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(" done");
  Serial.println("SENSOR ACTIVE");
  delay(50);
}

//LOOP
void loop() {
  //sensor 1
  // Clears the trigPin1
  digitalWrite(trigPin, LOW);
  delayMicroseconds(4);

  // Sets the trigPin on HIGH state for 3 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(3);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Calculating the distance
  distance = duration * 0.034 / 4;
  distance = duration * 0.034 / 4;

  if (distance <= 3 && counter <= 5) {
    Serial.println("Gate Open");
    myservo.write(0);
    delay(2000);
    Serial.println("Gate close");
    counter++;
    myservo.write(180);
    delay(2000);
    Serial.println("Gate Reset");
    Serial.print("Counter = ");
    Serial.println(counter);
    Serial.println();
  }

  if (distance >= 15 && distance <= 20 && counter > 0) {
    Serial.print("Distance was = ");
    Serial.println(distance);
    counter--;
    Serial.println("Gate Reset");
    Serial.print("Counter = ");
    Serial.println(counter);
    delay(3000);
    Serial.println();
  }
  delay(100);

  //LED
  if (counter == 1) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, LOW);
  }
  if (counter == 2) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  if (counter == 3) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  if (counter == 4) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, LOW);
  }
  if (counter == 5) {
    digitalWrite(led1, HIGH);
    digitalWrite(led2, LOW);
    digitalWrite(led3, HIGH);
  }
  if (counter == 6) {
    digitalWrite(led1, LOW);
    digitalWrite(led2, HIGH);
    digitalWrite(led3, HIGH);
  }

  //BT
  while (Serial.available()) { //Check if there is an available byte to read
    delay(10); //Delay added to make thing stable
    char c = Serial.read(); //Conduct a serial read
    if (c == '#') {
      break; //Exit the loop when the # is detected after the word
    }
    vo += c; //Shorthand for vo = vo + c
  }

  //bluetooth for version 3.1
  if (vo.length() > 0) {
    Serial.println(vo);
    //-----------------------------------------------------------------------//
    //---------- give the status of the ultrasonic sensors to find out number of occupied parkings ----------//
    if (vo == "*12|99|99|khushhal") {
      digitalWrite(13, HIGH);
      Serial.println(counter);
    }
    //version 3.1 khushhal
    vo = ""; //Reset the variable after initiating
  }
}
