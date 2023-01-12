int dustpin = A0;
int ledpower = 2;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(16,INPUT);
  pinMode(ledpower,OUTPUT);
  pinMode(dustpin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(ledpower,LOW);
  float dustval = analogRead(dustpin);
  digitalWrite(ledpower,HIGH);
  float dustDestiny = (0.172*(dustval*(5/1024.0)))*1000;
  Serial.println(dustval);
  Serial.println(dustDestiny);
    // Serial.println(digitalRead(16));
}
