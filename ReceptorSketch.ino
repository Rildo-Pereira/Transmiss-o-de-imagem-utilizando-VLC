static int TRESHOLD = 700;
static float standardDelay = 1; //500Hz
uint32_t time;

void setup() {
  Serial.begin(9600); // 9600 bits per second
  int sensorValue = 0;
  while(analogRead(A0)<TRESHOLD){;}
  delay(500);
  time = millis();

}
void loop() {
    
  boolean sensorValue1 = (analogRead(A0)>TRESHOLD);
  delay(standardDelay);

  boolean sensorValue2 = (analogRead(A0)>TRESHOLD);
  delay(standardDelay);

  boolean sensorValue3 = (analogRead(A0)>TRESHOLD);
  delay(standardDelay);

  boolean sensorValue4 = (analogRead(A0)>TRESHOLD);
  delay(standardDelay);

  boolean sensorValue5 = (analogRead(A0)>TRESHOLD);
  delay(standardDelay);

  long result = 10000*sensorValue1 + 1000*sensorValue2 + 100*sensorValue3
                + 10*sensorValue4 + 1*sensorValue5;
  Serial.println(result);
  
  PrintChar(result);
}

void PrintChar(long binary){
  
  switch (binary){
    case 1:
      //code for A is 00001
      Serial.println("A");
      break;
    case 10:
      //code for B is 00010
      Serial.println("B");
      break;
    case 11:
      //code for C is 00011
      Serial.println("C");
      break;
    case 100:
      //code for D is 00100
      Serial.println("D");
      break;
    case 101:
      //code for E is 00101
      Serial.println("E");
      break;
    case 110:
      //code for F is 00110
      Serial.println("F");
      break;
    case 111:
      //code for G is 00111
      Serial.println("G");
      break;
    case 1000:
      //code for H is 01000
      Serial.println("H");
      break;
    case 1001:
      //code for I is 01001
      Serial.println("I");
      break;
    case 1010:
      //code for J is 01010
      Serial.println("J");
      break;
    case 1011:
      //code for K is 01011
      Serial.println("K");
      break;
    case 1100:
      //code for L is 01100
      Serial.println("L");
      break;
    case 1101:
      //code for M is 01101
      Serial.println("M");
      break;
    case 1110:
      //code for N is 01110
      Serial.println("N");
      break;
    case 1111:
      //code for O is 01111
      Serial.println("O");
      break;
    case 10000:
      //code for P is 10000
      Serial.println("P");
      break;
    case 10001:
      //code for Q is 10001
      Serial.println("Q");
      break;
    case 10010:
      //code for R is 10010
      Serial.println("R");
      break;
    case 10011:
      //code for S is 10011
      Serial.println("S");
      break;
    case 10100:
      //code for T is 10100
      Serial.println("T");
      break;
    case 10101:
      //code for U is 10101
      Serial.println("U");
      break;
    case 10110:
      //code for V is 10110
      Serial.println("V");
      break;
    case 10111:
      //code for W is 10111
      Serial.println("W");
      break;
    case 11000:
      //code for X is 11000
      Serial.println("X");
      break;
    case 11001:
      //code for Y is 11001
      Serial.println("Y");
      break;
    case 11010:
      //code for Z is 11010
      Serial.println("Z");
      time = millis() - time;
      Serial.println(time);
      break;
    case 0:
      Serial.println("Algo impede a transmissão!");
      break;
    default:
      Serial.println(binary);
      Serial.println("Erro de sincronismo");
      break;
  }
  
  while(analogRead(A0)<TRESHOLD){;} //Aguarda sinal para manter sincronismo
  delay(standardDelay);
  //Serial.println(millis());
}
