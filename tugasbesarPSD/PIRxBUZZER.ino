// Pendeteksi Gerak Manusia dengan Sensor PIR
// Gunk Celulux 2011
/* 
int M = 12;                // pilih digital pin untuk LED
int H = 11;    
int Buzzer =  9;             // pilih digital pin untuk speaker
int inputPin = 8;               // pilih input pin untuk sensor PIR
int pirState = LOW;             // diasumsikan tidak ada gerakan terdeteksi
int val = 0;                    // variable untuk membaca status pin

void setup() {
   pinMode(H, OUTPUT);   
  pinMode(M, OUTPUT);      // deklarasi LED sebagai output
  pinMode(Buzzer, OUTPUT);  // deklarasi speaker sebagai output
  pinMode(inputPin, INPUT);     // deklarasi sensor sebagai input
  Serial.begin(9600);
  for(int i=0;i<3;i++){
    digitalWrite(H ,HIGH); delay(500);
    digitalWrite(H,LOW); delay(500);
  }
  digitalWrite(H ,HIGH);
  digitalWrite(M,LOW);
  
  Serial.println("SISTEM ON!");
  
}

void loop(){
      val = digitalRead(inputPin);  // membaca nilai input
      if (val == HIGH) {            // cek jika input adalah HIGH
        delay(150);
        digitalWrite(H, LOW);
        if (pirState == LOW){
          Serial.println("MALING !");
          while(digitalRead(inputPin)== HIGH){
            tone(Buzzer, 1000, 250);
            digitalWrite(M, HIGH); delay(250);  // LED menyala
            digitalWrite(M, LOW); delay(250);       
          }
        pirState = HIGH;
        }
      }
      else {
        if (pirState == HIGH){
          // hanya memadamkan
          digitalWrite(H, HIGH); // padamkan LED
          Serial.println("Aman..Kondusif !");
          // hanya memunculkan pergantian output, bukan status
          pirState = LOW;
        }
      }
}
*/
