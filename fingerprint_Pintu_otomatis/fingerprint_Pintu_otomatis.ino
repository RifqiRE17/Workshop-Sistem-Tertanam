#include <Adafruit_Fingerprint.h> //Untuk memanggil library sidik jari
#include <Servo.h> //Untuk memanggil library Servo

Servo myservo; //Membuat deklarasi servo agar bisa dikendalikan

int pos = 0; //Deklarasi variabel untuk posisi sudut
  
#if (defined(__AVR__) || defined(ESP8266)) && !defined(__AVR_ATmega2560__) //Mendefinisikan perangkat untuk perangkat selain arduino uno yaitu Arduino Mega

SoftwareSerial mySerial(4, 5); //Untuk mendklarasikan letak pin fingerprint

#else

#define mySerial Serial1 //Untuk mendifinisikan serial arduino uno yaitu serial 1

#endif

Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial); //Untuk memberi vaiabel bahwa Adafruit_fingerprint finger merupakan Adafruit_Fingerprint(&mySerial);

int lock_delay = 16000; //Lock Delay Buat Nutup
int lock_delay_2 = 16000; //Lock Delay Buat Buka

int buttonPin = 2; //memberi variabel bahwa buttonPin merupakan pin 2

int limitSwitchPin = 7; //memberi variabel bahwa limitSwitchPin merupakan pin 7


void setup()
{
  myservo.attach(9); //Mendefinisikan pin yang digunakan untuk dipasang servo
  pinMode(buttonPin, INPUT_PULLUP); //Mendefinisikan pin yang digunakan untuk buttonpin
  finger.begin(57600); //serial untuk fingerprint
  pinMode(10, OUTPUT); // mendifinisikan led yang tersambung dengan pin 10 led warna hijau 
  pinMode(11, OUTPUT); // mendifinisikan led yang tersambung dengan pin 11 led warna merah
}

void loop() {

  if (digitalRead(limitSwitchPin) == LOW) //mendeklarasikan jika limitswitch menjadi low atau tertekan maka button pin jika ditekan membuat servo menjadi berputar ke kiri
  {
    while (digitalRead(buttonPin) == HIGH )  //Ketika tombol ditekan atau dalam keadaan high
    {
      digitalWrite(11, LOW); //mematikan led pin 11 yaitu pin berwarna merah
      digitalWrite(10, HIGH); //menghidupkan led pin 10 yaitu pin berwarna hijau
      myservo.attach(9); //Mendefinisikan pin yang digunakan untuk dipasang servo
      for (pos = 180; pos >= 0; pos -= 1) { //perintah agar servo bergerak sebesar 180 derajat dan mengarah ke kanan 
        myservo.write(pos); //membaca variabel pos
        delay(lock_delay); //membaca delay lock_delay
        myservo.detach(); //menghentiak servo
        return finger.fingerID; //kembali ke awal yaitu ada di Adafruit_Fingerprint finger
      }
    }
  }
  //Jika limit switch tidak tertekan atau menjadi high maka servo menjadi berputar ke kanan
  else while (digitalRead(buttonPin) == HIGH ) //Ketika tombol ditekan atau dalam keadaan high
    {

      digitalWrite(10, LOW); //Mematika led pin 10 yaitu pin berwarna hijau
      digitalWrite(11, HIGH); //Menghidupkan led pin 10 yaitu pin berwarna hijau
      myservo.attach(9); //Mendefinisikan pin yang digunakan untuk dipasang servo
      for (pos = 0; pos <= 180; pos += 1) { //perintah agar servo bergerak sebesar 180 derajat dan mengarah ke kiri
        myservo.write(pos); //membaca variabel pos
        delay(lock_delay_2); //membaca delay lock_delay_2
        myservo.detach(); //menghentiak servo
        return finger.fingerID; //kembali ke awal yaitu ada di Adafruit_Fingerprint finger
      }
    }


  {
    getFingerprintIDez(); //untuk mengambil gambar fingerprint dari sensor fingerprint
    delay(50);
  }
}


uint8_t getFingerprintID() { //mendapatkan id dari fingerprint
  uint8_t p = finger.getImage(); //mendapatkan gambar dari fingerprint

  // OK success!

  p = finger.image2Tz(); //meminta sensor untuk mengkonversikan gambar sidik jari menjadi fitur template adafruit fingerprint

  // OK converted!
  p = finger.fingerSearch(); //Minta sensor untuk mencocokkan template yang disimpan. Lokasi yang cocok disimpan di fingerID
  
  // found a match!
  if (digitalRead(limitSwitchPin) == LOW) //mendeklarasikan jika limitswitch menjadi low atau tertekan maka button pin jika ditekan membuat servo menjadi berputar ke kiri
  {
    digitalWrite(11, LOW); //mematikan led pin 11 yaitu pin berwarna merah
    digitalWrite(10, HIGH); //menghidupkan led pin 10 yaitu pin berwarna hijau
    myservo.attach(9); //Mendefinisikan pin yang digunakan untuk dipasang servo
    for (pos = 180; pos >= 0; pos -= 1) { //perintah agar servo bergerak sebesar 180 derajat dan mengarah ke kanan
      myservo.write(pos); //membaca variabel pos
      delay(lock_delay); //membaca delay lock_delay
      myservo.detach(); //menghentiak servo
      return finger.fingerID; //kembali ke awal yaitu ada di Adafruit_Fingerprint finger
    }
  } else {
    digitalWrite(10, LOW); //mematikan led pin 10 yaitu pin berwarna hijau
    digitalWrite(11, HIGH); //menghidupkan led pin 10 yaitu pin berwarna merah
    myservo.attach(9); //Mendefinisikan pin yang digunakan untuk dipasang servo
    for (pos = 0; pos <= 180; pos += 1) { //perintah agar servo bergerak sebesar 180 derajat dan mengarah ke kiri
      myservo.write(pos); //membaca variabel pos
      delay(lock_delay_2); //membaca delay lock_delay_2
      myservo.detach(); //menghentikan servo
      return finger.fingerID; //kembali ke awal yaitu ada di Adafruit_Fingerprint finger
    }
  }
}
// returns -1 if failed, otherwise returns ID #
int getFingerprintIDez() {
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK)  return -1; //mengembalikan

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK)  return -1;

  p = finger.fingerFastSearch();
  if (p != FINGERPRINT_OK)  return -1;

  // found a match!
  if (digitalRead(limitSwitchPin) == LOW)
  {
    digitalWrite(11, LOW);
    digitalWrite(10, HIGH);
    myservo.attach(9);
    for (pos = 180; pos >= 0; pos -= 1) {
      myservo.write(pos);
      delay(lock_delay);
      myservo.detach();
      return finger.fingerID;
    }
  } else {

    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
    myservo.attach(9);
    for (pos = 0; pos <= 180; pos += 1) { 
      myservo.write(pos);
      delay(lock_delay_2);
      myservo.detach();
      return finger.fingerID;
    }
  }
}
