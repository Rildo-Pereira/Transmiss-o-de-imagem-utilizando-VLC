static float standardDelay = 1; //500Hz
static int lowlight = 0;

void setup() {
  Serial.begin(9600); // 9600 bits per second
  pinMode(5,OUTPUT); //digital PWM 5 on output
  //int sensorValue = 0;
  digitalWrite(5,HIGH);
  delay(500);
}
void loop() {
  //read every 100ms
  //high A0 value is one, low A0 value is zero
  WriteChar('A');
  WriteChar('B');
  WriteChar('C');
  WriteChar('D');
  WriteChar('E');
  WriteChar('F');
  WriteChar('G');
  WriteChar('H');
  WriteChar('I');
  WriteChar('J');
  WriteChar('K');
  WriteChar('L');
  WriteChar('M');
  WriteChar('N');
  WriteChar('O');
  WriteChar('P');
  WriteChar('Q');
  WriteChar('R');
  WriteChar('S');
  WriteChar('T');
  WriteChar('U');
  WriteChar('V');
  WriteChar('W');
  WriteChar('X');
  WriteChar('Y');
  WriteChar('Z');
}

void WriteChar(char str){

  switch (str - '@'){
    case 1:
      //code for A is 00001
      LightFlash(false, false, false, false, true);
      break;
    case 2:
      //code for B is 00010
      LightFlash(false, false, false, true, false);
      break;
    case 3:
      //code for C is 00011
      LightFlash(false, false, false, true, true);
      break;
    case 4:
      //code for D is 00100
      LightFlash(false, false, true, false, false);
      break;
    case 5:
      //code for E is 00101
      LightFlash(false, false, true, false, true);
      break;
    case 6:
      //code for F is 00110
      LightFlash(false, false, true, true, false);
      break;
    case 7:
      //code for G is 00111
      LightFlash(false,  false, true, true, true);
      break;
    case 8:
      //code for H is 01000
      LightFlash(false, true, false, false, false);
      break;
    case 9:
      //code for I is 01001
      LightFlash(false, true, false, false, true);
      break;
    case 10:
      //code for J is 01010
      LightFlash(false, true, false, true, false);
      break;
    case 11:
      //code for K is 01011
      LightFlash(false, true, false, true, true);
      break;
    case 12:
      //code for L is 01100
      LightFlash(false, true, true, false, false);
      break;
    case 13:
      //code for M is 01101
      LightFlash(false, true, true, false, true);
      break;
    case 14:
      //code for N is 01110
      LightFlash(false, true, true, true, false);
      break;
    case 15:
      //code for O is 01111
      LightFlash(false, true, true, true, true);
      break;
    case 16:
      //code for P is 10000
      LightFlash(true, false, false, false, false);
      break;
    case 17:
      //code for Q is 10001
      LightFlash(true, false, false, false, true);
      break;
    case 18:
      //code for R is 10010
      LightFlash(true, false, false, true, false);
      break;
    case 19:
      //code for S is 10011
      LightFlash(true, false, false, true, true);
      break;
    case 20:
      //code for T is 10100
      LightFlash(true, false, true, false, false);
      break;
    case 21:
      //code for U is 10101
      LightFlash(true, false, true, false, true);
      break;
    case 22:
      //code for V is 10110
      LightFlash(true, false, true, true, false);
      break;
    case 23:
      //code for W is 10111
      LightFlash(true, false, true, true, true);
      break;
    case 24:
      //code for X is 11000
      LightFlash(true, true, false, false, false);
      break;
    case 25:
      //code for Y is 11001
      LightFlash(true, true, false, false, true);
      break;
    case 26:
      //code for Z is 11010
      LightFlash(true, true, false, true, false);
      break;     
    default:
      Serial.println(str - '@');
      Serial.println("Erro na programação");
      break;
  }
}

void LightFlash(boolean a, boolean b, boolean c, boolean d, boolean e){

  
  digitalWrite(5,HIGH); 
  if (a == true){
    analogWrite(5,lowlight);
  }
  delay(standardDelay/2);

  digitalWrite(5,HIGH);
  delay(standardDelay/2);
  if (b == true){
    analogWrite(5,lowlight);
  }
  delay(standardDelay/2);

  digitalWrite(5,HIGH);
  delay(standardDelay/2); 
  if (c == true){
    analogWrite(5,lowlight);
  }
  delay(standardDelay/2);

  digitalWrite(5,HIGH);
  delay(standardDelay/2);
  if (d == true){
    analogWrite(5,lowlight);
  }
  delay(standardDelay/2);

  digitalWrite(5,HIGH);
  delay(standardDelay/2);
  if (e == true){
    analogWrite(5,lowlight);
  }
  delay(standardDelay/2);
 
  digitalWrite(5,HIGH);
  delay(standardDelay); //tempo para o receptor esperar o sinal

  analogWrite(5,lowlight);
  delay(standardDelay/2);
  digitalWrite(5,HIGH);
  delay(standardDelay/2);
  //Serial.println(millis());
}
