// Written by Rupak Poddar
// www.youtube.com/RupakPoddar

/* PINOUT
 *  Fingerprint Sensor      Arduino
 *  Vcc(red)----------------> 5v
 *  Gnd(Black)--------------> Gnd
 *  Tx(green)---------------> Pin 2
 *  Rx(white)---------------> Pin 3
 */

#include <Adafruit_Fingerprint.h>
#include <Servo.h>

Servo myservo;

int pos = 0;

// pin #2 is IN from sensor (GREEN wire)
// pin #3 is OUT from arduino  (WHITE wire)
SoftwareSerial mySerial(2, 3);

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//int door_lock = 9; //connect the door lock to pin 12
int lock_delay = 5000; //change the delay from here

void setup()  
{
    myservo.attach(8);
    pinMode(2,INPUT);
//  pinMode(door_lock, OUTPUT);
//  digitalWrite(door_lock, LOW);
    Serial.begin(9600);
    finger.begin(57600);
  }

void loop()
{
  getFingerprintIDez();
  delay(50);

//Tombol
{
  if(digitalRead(2)==HIGH){
    myservo.attach(9);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees   
  myservo.write(pos);
  delay(lock_delay);
//  digitalWrite(door_lock, LOW);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(lock_delay);
  myservo.detach();
  return finger.fingerID;
    }
  }
  }
  else
    
 myservo.write(0);

}
}

uint8_t getFingerprintID() {
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }
  
  // OK converted!
  p = finger.fingerFastSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }   
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence); 
//  digitalWrite(door_lock, HIGH);
  myservo.attach(9);
  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees   
  myservo.write(pos);
  delay(lock_delay);
//  digitalWrite(door_lock, LOW);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(lock_delay);
  myservo.detach();
  return finger.fingerID;
    }
  }
}
// returns -1 if failed, otherwise returns ID #
  int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;
  
  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID); 
  Serial.print(" with confidence of "); Serial.println(finger.confidence);
//  digitalWrite(door_lock, HIGH);
//  delay(lock_delay);
//  digitalWrite(door_lock, LOW);
//  return finger.fingerID; 
myservo.attach(9);
for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees   
  myservo.write(pos);
  delay(lock_delay);
//  digitalWrite(door_lock, LOW);
  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  myservo.write(pos);              // tell servo to go to position in variable 'pos'
  delay(lock_delay);
  myservo.detach();
  return finger.fingerID;
    }
  }
}
