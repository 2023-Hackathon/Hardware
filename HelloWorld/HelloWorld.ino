#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <LedControl.h>
// #include <PubSubClient.h>
// #include <SoftwareSerial.h>
LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x3F for a 16 chars and 2 line display
LedControl dot = LedControl(13,14,12,1);
const char* ssid = "bssm_guest";
const char* password = "bssm_guest";
ESP8266WebServer server(80);
const int status = 1;
// const int motor = 0;

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid,password);
  while (WiFi.status() != WL_CONNECTED) {
		delay(500);
		Serial.println(".");
	}
  Serial.print("Connecting to ");
	Serial.println(ssid);
	Serial.print("IP address: ");
	Serial.println(WiFi.localIP());
  server.on("/",main_scr);  
  server.on("/talking",talking);
  server.on("/recording",recording);
  server.begin();
  Serial.println("server start");
  lcd.clear();
  dot.shutdown(0,false);
  // pinMode(motor,OUTPUT);
}

byte red[] = {
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111,
  B11111111
};
 
void loop() {
 server.handleClient();
}
void main_scr(){
  lcd.init();      
  lcd.backlight();      // Make sure backlight is on
  lcd.clear();  // Print a message on both lines of the LCD.
  lcd.setCursor(1,0);   //Set cursor to character 2 on line 0
  lcd.print("Hello");
  dot.shutdown(0,true);
  server.send(200,"text/html","<h1>hi</h1>");
}
void talking(){
  lcd.clear();       
  lcd.backlight(); 
  lcd.setCursor(1,0);
  lcd.print("Talking...");
  dot.shutdown(0,false);
  for(int i=0; i<8;i++){
    dot.setRow(0,i,red[i]);
  }
  for(int i =0;i<8;i++){
    if((red[i]&0b10000000)>0){
      red[i] = red[i] <<1;
      red[i] += B00000001;
    }
    else{
      red[i]=red[i]<<1;
    }
  }
  server.send(200,"text/html","<h1>talking</h1>");
}
void recording(){
  lcd.clear();
  lcd.backlight(); 
  lcd.setCursor(2,0);
  lcd.print("Recording...");
  dot.shutdown(0,true);
  server.send(200,"text/html","<h1>recording</h1>");
}