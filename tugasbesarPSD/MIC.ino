/*int micPin = 13; // Use Pin as our Input
int micVal = HIGH; // This is where we record our Sound Measurement
boolean bAlarm = false;
int M = 12, H = 11, index = 0; 
int IN1=4, IN2=5, IN3=6, IN4=7, delaytime=2; //makin kecil delay, makin cepat motor berputar
unsigned long lastSoundDetectTime; // Record the time that we measured a sound


int micTimer = 500; // Number of milli seconds to keep the sound alarm high


void setup ()
{
  Serial.begin(9600);  
  pinMode (micPin, INPUT) ; // input from the Sound Detection Module
  pinMode(M,OUTPUT);
  pinMode(H  ,OUTPUT);

  pinMode(IN1,OUTPUT);
pinMode(IN2,OUTPUT);
pinMode(IN3,OUTPUT);
pinMode(IN4,OUTPUT);
}
void loop ()
{
  micVal = digitalRead(micPin) ; // read the sound alarm time
  
  if (micVal == LOW) // If we hear a sound
  {
  
    lastSoundDetectTime = millis(); // record the time of the sound alarm
    // The following is so you don't scroll on the output screen
    if (!bAlarm){
      Serial.println("LOUD, LOUD");
      index++;
      if((index%2==1) || (index==1)){
        digitalWrite(H,HIGH);
        digitalWrite(M,LOW);
        Serial.println("NYALA");
        buka();
        Serial.println(index);
      }
      else if(index%2==0){
        digitalWrite(M,HIGH);
        digitalWrite(H,LOW);
        Serial.println("MATI");
        tutup();
        Serial.println(index);
      }
      bAlarm = true;
    }
  }
  else
  {
    if( (millis()-lastSoundDetectTime) > micTimer  &&  bAlarm){
      Serial.println("quiet");
      bAlarm = false;
    }
  }
}

void buka(){
    //  digitalWrite(H, HIGH); delay(3000);
      for (int i=0; i<270; i++){
        maju();
      }
     // digitalWrite(H, LOW); delay(1000);
    }

void tutup(){
 // digitalWrite(M, HIGH); delay(3000);
      for (int i=0; i<270; i++){
        mundur();
      }
}

void maju(){

//step 4
step1();
delay(delaytime);

//step 3
step2();
delay(delaytime);

//step 2
step3();
delay(delaytime);

//step 1
step4();
delay(delaytime);
}

void mundur(){

//step 4
step4();
delay(delaytime);

//step 3
step3();
delay(delaytime);

//step 2
step2();
delay(delaytime);

//step 1
step1();
delay(delaytime);
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
}*/
