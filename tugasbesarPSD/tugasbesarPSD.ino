  /* ============================================================================= *
   * ==================== TUGAS BESAR PENGANTAR SISTEM DIGITAL =================== *
   * ================================ KELOMPOK 1 ================================= *
   *                            - Ainiyah                                          *
   *                            - Erika Maulidiya                                  *
   *                            - Mahrudin                                         *
   *                            - Muhammad Rizal                                   *
   *                            - Rizka Ardiyanti                                  *
   *                            - Windi Wulandari                                  *                                                                              *
   * ============================================================================= */

//============================ DEKLARASI GLOBAL VARIABEL ========================= //

  boolean securityMode;
  int Merah      = 12;           // Pin LED Merah
  int Hijau      = 11;           // Pin LED Hijau
  boolean respon = true;
  int micPin     = 10;           // Pin Sensor Suara
  int micVal     = HIGH;         // Nilai Read Modul Sensor suara
  int buzPin     = 9;            // digital pin untuk speaker
  int pirPin     = 8;            // pilih input pin untuk sensor PIR
  int pirState   = LOW;          // diasumsikan tidak ada gerakan terdeteksi
  int IN1        = 7;            // IN = Pin Motor Stepper
  int IN2        = 6;
  int IN3        = 5;
  int IN4        = 4; 
  int buttonPin  = 3;
  int delaytime  = 2;            // delay untuk kecepatan Motor Stepper
  unsigned long timer;           // variable untuk menyimpan estimasi waktu program
  int micTimer = 500;            // waktu membaca Sensor Suara
  int index, count;
  int pirVal, buttonVal;

//====================================== SETUP =================================== //
  
  void setup(){
    Serial.begin(9600);  
    pinMode(Merah,OUTPUT);    
    pinMode(Hijau,OUTPUT);  
    pinMode(micPin,INPUT);       // input dari Modul sensor suara
    pinMode(pirPin,INPUT);       // deklarasi sensor PIR sebagai input 
    pinMode(buttonPin,INPUT);    // deklarasi tombol sebagai input 
    pinMode(buzPin,OUTPUT);      // deklarasi speaker sebagai output
    pinMode(IN1,OUTPUT);         // deklarasi Stepper sebagai output
    pinMode(IN2,OUTPUT);
    pinMode(IN3,OUTPUT);
    pinMode(IN4,OUTPUT);
  
    Serial.println("======= SYSTEM AKTIF ======");  
    for(int i=0; i<10; i++){                         
      digitalWrite(Hijau,HIGH);
      digitalWrite(Merah,LOW); delay(250);
      digitalWrite(Hijau,LOW);
      digitalWrite(Merah,HIGH); delay(250);
    }
    Serial.println("MENUNGGU RESPON ...");
  }

//================================ EKSEKUSI PROGRAM ============================== //

  void loop(){
    buttonVal = digitalRead(buttonPin);     // kode di eksekusi jika terdapat
    if(buttonVal == 1){                     // inputan pada tombol
      count++;
      delay(250);
      if(count==1){
        Serial.println("====== securityMode ON ======");
        securityMode = true;
        if((index%2==1) || (index==1)){     // di eksekusi jika pintu
          index++;                          // dalam keadaaan terbuka
          digitalWrite(Hijau,LOW);
          tutup();
        }
        tone(buzPin, 1000, 1000); 
        digitalWrite(Merah,HIGH);
        delay(1000);
        digitalWrite(Merah,LOW);
        delay(1000);
        digitalWrite(Merah,HIGH);
      }
      if(count==2){
        Serial.println("====== securityMode OFF =====");
        securityMode = false;
        count=0;
      }
    }
    
    if(securityMode == false){       // ====================== securityMode OFF    
      micVal = digitalRead(micPin) ;        // mode READ sensor suara
      if (micVal == LOW){                   // kondisi jika terdeteksi suara
      timer = millis();                     // waktu estimasi mulai sistem aktif (ms)
        if(respon){                         // Kondisi jika mendapat Respon (Tepukan)
          index++;                          // index akan bertamah
          if((index%2==1) || (index==1)){   // index ganjil = TERBUKA
            Serial.println("======== PINTU TERBUKA ======");
            digitalWrite(Hijau,HIGH);
            digitalWrite(Merah,LOW);
            buka();
          }
          else if(index%2==0){              // index genap = TERTUTUP
            Serial.println("======= PINTU TERTUTUP ======");
            digitalWrite(Merah,HIGH);
            digitalWrite(Hijau,LOW);
            tutup();
          }
          respon = false;                  // Pengeset-an agar ke Mode Tunggu
        }
      }
      else{                                // Mode menunggu Respon User (Tepukan)
        if((millis()-timer) > micTimer && !respon){
          Serial.println("MENUNGGU RESPON ...");
          respon = true;
        }
      }
    }
    else{                             // ====================== securityMode ON
      
      pirVal = digitalRead(pirPin);       // membaca nilai input PIR
      if (pirVal == HIGH) {               // pengecekan jika input adalah HIGH
        delay(150);
        if (pirState == LOW){
          Serial.println("MALING !");
          while(digitalRead(pirPin)== HIGH){      // berhenti ketika tak ada gerakan
            tone(buzPin, 1000, 250);              // Buzzer aktif
            digitalWrite(Merah,HIGH); delay(250); // LED menyala
            digitalWrite(Merah,LOW); delay(250);  // LED mati
          }
        pirState = HIGH;
        }
      }
      else {                             // pengecekan jika input adalah LOW
        if(pirState == HIGH){
          digitalWrite(Merah, HIGH);
          Serial.println(" SIAGA ..."); 
          pirState = LOW;
        }
      }
    }
  }

// ============================ FUNCTION MOTOR STEPPER =========================== //

  void buka(){                    // membuka Pintu
    for (int i=0; i<270; i++){    // Melawan Arah Jarum jam 180 derajat
      step1(); delay(delaytime);
      step2(); delay(delaytime);
      step3(); delay(delaytime);
      step4(); delay(delaytime);
    }
  }
  
  void tutup(){                  // menutup pintu
    for (int i=0; i<270; i++){   // seArah Jarum jam 180 derajat
      step4(); delay(delaytime);  
      step3(); delay(delaytime);
      step2(); delay(delaytime);
      step1(); delay(delaytime);
    }
  }
  
  void step1(){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,HIGH);
  }
  
  void step2(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,LOW);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,HIGH);
  }
  
  void step3(){
    digitalWrite(IN1,HIGH);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,LOW);
    digitalWrite(IN4,LOW);
  }
  
  void step4(){
    digitalWrite(IN1,LOW);
    digitalWrite(IN2,HIGH);
    digitalWrite(IN3,HIGH);
    digitalWrite(IN4,LOW);
  }

//================================ AKHIR BARIS KODE ============================= //
