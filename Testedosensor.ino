  int sensorvalue1 = 0;
  int sensorvalue2 = 0;
  
void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);

}

void loop() {
  digitalWrite(5, HIGH);
  sensorvalue1 = analogRead(A0);
  Serial.print("Valor digitalizado do sensor");
  Serial.print(" = ");
  Serial.println(sensorvalue1);
  delay(500);

  /*analogWrite(5, 128);
  sensorvalue2 = analogRead(A0);
  Serial.print("Valor do sensor na corrente mÃ©dia");
  Serial.print(" = ");
  Serial.println(sensorvalue2);
  delay(50);*/
}

