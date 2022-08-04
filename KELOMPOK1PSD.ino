#define pinSensor A0  // mendefinisikan pin A0 sebagai pin yang berhubungan dengan sensor
#include <ESP8266WiFi.h>
#include <PubSubClient.h> 


//-------- Customise these values -----------
const char* ssid = "Black13_";
const char* password = "Rxxx1113";

#define ORG "26q8fk"
#define DEVICE_TYPE "kelompok1ehe"
#define DEVICE_ID "nodemcu"
#define TOKEN "qwerty123"

//-------- Customise the above values --------

char server[] = ORG".messaging.internetofthings.ibmcloud.com";
char topic[] = "iot-2/evt/status/fmt/json";
char authMethod[] = "use-token-auth";
char token[] = TOKEN;
char clientId[] = "d:" ORG ":" DEVICE_TYPE ":" DEVICE_ID;

WiFiClient wifiClient;

PubSubClient client(server, 1883, NULL, wifiClient);

int sensorValue = 0; // variable untuk menampung nilai baca dari sensor dalam bentuk integer
float tinggiAir = 0; // variabel untuk menampung ketinggian air
float sensorVoltage = 0; // untuk menampung nilai ketinggian air


int nilaiMax = 1023; // nilai "sensorValue" saat sensor terendam penuh kedalam air, bisa dirubah sesuai sensor dan jenis air yang anda pakai
float panjangSensor = 4.0 ; // 4.0 cm, bisa dirubah, menyesuikan dengan panjang sensor yang kalian gunakan

void setup() {
  Serial.begin(9600); // mengatur boudrate komunikasi serial antara arduino dengan PC
  Serial.println("Pembacaan Ketinggian Air");

 
 Serial.print("Connecting to "); Serial.print(ssid);
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 } 
 Serial.println("");

 Serial.print("WiFi connected, IP address: "); Serial.println(WiFi.localIP());
}

void loop() {
  
  sensorValue = analogRead(pinSensor); // membaca tengan dari sensor dalam bentuk integer
  tinggiAir = sensorValue*panjangSensor/nilaiMax;


  if (!client.connected()) {
 Serial.print("Reconnecting client to ");
 Serial.println(server);
 while (!client.connect(clientId, authMethod, token)) {
 Serial.print(".");
 delay(500);
 }
 Serial.println();
 }

 String payload = "{\"kelompok1\":{\"Name\":\" Sensor Tinggi air\"";
 payload += ",\"sensorValue\":";
 payload += sensorValue;
 payload += ",\"tinggiAir\":";
 payload += tinggiAir;
 payload += "}}";
 
 Serial.print("Sending payload: ");
 Serial.println(payload);
 
 if (client.publish(topic, (char*) payload.c_str())) {
 Serial.println("Publish ok");
 } else {
 Serial.println("Publish failed");
 }

 delay(5000);
}
