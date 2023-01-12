#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SoftwareSerial.h>
const char* ssid = "BSSM_EN";
const char* password = "12345678";
const char* mqtt_server = "192.168.4.99";
int dustpin = A0;
int ledpower = 2;

WiFiClient espClient;
PubSubClient client(espClient);
void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived on topic:");
  Serial.print(topic);
  Serial.print(".Message:");
  String messageTemp;
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
    messageTemp += (char)message[i];
  }
  Serial.println();
}
void setup_wifi() { 
  delay(10);
  Serial.println();
  Serial.print("Connecting");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.println("");
  Serial.print("WiFi connected - ESP IP address:");
  Serial.println(WiFi.localIP());
}
void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection");
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
    } else {
      Serial.print(" failed,rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}
void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  delay(1000);

  pinMode(16,INPUT);
  pinMode(ledpower,OUTPUT);
  pinMode(dustpin,INPUT);
}
void loop() {
  digitalWrite(ledpower,LOW);
  float dustval = analogRead(dustpin);
  digitalWrite(ledpower,HIGH);
  float dustDestiny = (0.172*(dustval*(5/1024.0)))*1000;
  bool sun = digitalRead(16);
  if (!client.connected()) {
    reconnect();
  }
  if (!client.loop())
    client.connect("ESP8266Client");
  static char dustVal[7];
  
  Serial.println(dustval);
  delay(3000);
  dtostrf(dustval, 6, 2,dustVal);
  Serial.print(dustval);
  Serial.println("send");
  client.publish("MY_TOPIC", dustVal);
      
}
