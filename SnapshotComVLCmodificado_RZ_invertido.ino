#include <Adafruit_VC0706.h> //Inclui biblioteca da câmera
#include <SPI.h>
#include <SD.h>
#include <SoftwareSerial.h>

// Using SoftwareSerial (Arduino 1.0+) or NewSoftSerial (Arduino 0023 & prior):
#if ARDUINO >= 100
// On Uno: camera TX connected to pin 2, camera RX to pin 3:
SoftwareSerial cameraconnection = SoftwareSerial(2, 3);
// On Mega: camera TX connected to pin 69 (A15), camera RX to pin 3:
//SoftwareSerial cameraconnection = SoftwareSerial(69, 3);
#else
NewSoftSerial cameraconnection = NewSoftSerial(2, 3);
#endif

Adafruit_VC0706 cam = Adafruit_VC0706(&cameraconnection);

static int Limiar = 500; // Static preserva o dado da variável entre as funções chamadas
static float standardDelay = 10;
static unsigned int signalDelay = 20;
int OK = 5;
int NOK = 10;

void setup() {

  Serial.begin(9600);
  pinMode(5, OUTPUT); //digital PWM 5 on output

  while (analogRead(A0) < Limiar) { // Aguarda comunicação do mestre
    ;
  }
  digitalWrite(5, HIGH);
  delay(signalDelay + signalDelay/2);
  // Try to locate the camera
  if (cam.begin()) {

    Writebyte(OK);
  }
  else {
      Writebyte(NOK);
    return;
  }

  // Set the picture size - you can choose one of 640x480, 320x240 or 160x120
  // Remember that bigger pictures take longer to transmit!

  //cam.setImageSize(VC0706_640x480);        // biggest
  //cam.setImageSize(VC0706_320x240);        // medium
  cam.setImageSize(VC0706_160x120);          // small

  /*while (analogRead(A0) < Limiar) { // Aguarda comunicação do mestre
    ;
  }*/
  delay(signalDelay + signalDelay/2);

  if (! cam.takePicture()) {
    return;
  }
  else {
    digitalWrite(5, LOW); // Liga o Led no pino 3 por 500ms
    delay(signalDelay/2);
    digitalWrite(5, HIGH); // Desliga o Led e espera 500ms
    delay(signalDelay/2);   
  }

  // Get the size of the image (frame) taken
  uint16_t jpglen = cam.frameLength();
  unsigned int x = highByte(jpglen); //Pega o byte mais significativo de jpglen
  unsigned int y = lowByte(jpglen); //Pega o byte menos significativo de jpglen

  Writebyte(x); //Envia a parte mais significativa
  delay(signalDelay);

  Writebyte(y); //Envia a parte menos significativa
  delay(signalDelay);

  pinMode(8, OUTPUT);
  // Read all the data up to # bytes!

  while (jpglen > 0) {

    // read 32 bytes at a time;
    uint8_t *buffer;
    uint8_t bytesToRead = min(32, jpglen); // change 32 to 64 for a speedup but may not work with all setups!
    buffer = cam.readPicture(bytesToRead);
    
    for (int i = 0; i < bytesToRead; i++){
      Writebyte(buffer[i]); //Envia byte a byte para o cartão.
      delay(signalDelay);
    }
    jpglen -= bytesToRead;
  }

}

void Writebyte(int x) {

  switch (x) {
    case 0:
      
      LightFlash(false, false, false, false, false, false, false, false);
      break;
    case 1:
      LightFlash(false, false, false, false, false, false, false, true);
      break;
    case 2:
      LightFlash(false, false, false, false, false, false, true, false);
      break;
    case 3:
      LightFlash(false, false, false, false, false, false, true, true);
      break;
    case 4:
      LightFlash(false, false, false, false, false, true, false, false);
      break;
    case 5:
      LightFlash(false, false, false, false, false, true, false, true);
      break;
    case 6:
      LightFlash(false, false, false, false, false, true, true, false);
      break;
    case 7:
      LightFlash(false, false, false, false, false, true, true, true);
      break;
    case 8:
      LightFlash(false, false, false, false, true, false, false, false);
      break;
    case 9:
      LightFlash(false, false, false, false, true, false, false, true);
      break;
    case 10:
      LightFlash(false, false, false, false, true, false, true, false);
      break;
    case 11:
      LightFlash(false, false, false, false, true, false, true, true);
      break;
    case 12:
      LightFlash(false, false, false, false, true, true, false, false);
      break;
    case 13:
      LightFlash(false, false, false, false, true, true, false, true);
      break;
    case 14:
      LightFlash(false, false, false, false, true, true, true, false);
      break;
    case 15:
      LightFlash(false, false, false, false, true, true, true, true);
      break;
    case 16:
      LightFlash(false, false, false, true, false, false, false, false);
      break;
    case 17:
      LightFlash(false, false, false, true, false, false, false, true);
      break;
    case 18:
      LightFlash(false, false, false, true, false, false, true, false);
      break;
    case 19:
      LightFlash(false, false, false, true, false, false, true, true);
      break;
    case 20:
      LightFlash(false, false, false, true, false, true, false, false);
      break;
    case 21:
      LightFlash(false, false, false, true, false, true, false, true);
      break;
    case 22:
      LightFlash(false, false, false, true, false, true, true, false);
      break;
    case 23:
      LightFlash(false, false, false, true, false, true, true, true);
      break;
    case 24:
      LightFlash(false, false, false, true, true, false, false, false);
      break;
    case 25:
      LightFlash(false, false, false, true, true, false, false, true);
      break;
    case 26:
      LightFlash(false, false, false, true, true, false, true, false);
      break;
    case 27:
      LightFlash(false, false, false, true, true, false, true, true);
      break;
    case 28:
      LightFlash(false, false, false, true, true, true, false, false);
      break;
    case 29:
      LightFlash(false, false, false, true, true, true, false, true);
      break;
    case 30:
      LightFlash(false, false, false, true, true, true, true, false);
      break;
    case 31:
      LightFlash(false, false, false, true, true, true, true, true);
      break;
    case 32:
      LightFlash(false, false, true, false, false, false, false, false);
      break;
    case 33:
      LightFlash(false, false, true, false, false, false, false, true);
      break;
    case 34:
      LightFlash(false, false, true, false, false, false, true, false);
      break;
    case 35:
      LightFlash(false, false, true, false, false, false, true, true);
      break;
    case 36:
      LightFlash(false, false, true, false, false, true, false, false);
      break;
    case 37:
      LightFlash(false, false, true, false, false, true, false, true);
      break;
    case 38:
      LightFlash(false, false, true, false, false, true, true, false);
      break;
    case 39:
      LightFlash(false, false, true, false, false, true, true, true);
      break;
    case 40:
      LightFlash(false, false, true, false, true, false, false, false);
      break;
    case 41:
      LightFlash(false, false, true, false, true, false, false, true);
      break;
    case 42:
      LightFlash(false, false, true, false, true, false, true, false);
      break;
    case 43:
      LightFlash(false, false, true, false, true, false, true, true);
      break;
    case 44:
      LightFlash(false, false, true, false, true, true, false, false);
      break;
    case 45:
      LightFlash(false, false, true, false, true, true, false, true);
      break;
    case 46:
      LightFlash(false, false, true, false, true, true, true, false);
      break;
    case 47:
      LightFlash(false, false, true, false, true, true, true, true);
      break;
    case 48:
      LightFlash(false, false, true, true, false, false, false, false);
      break;
    case 49:
      LightFlash(false, false, true, true, false, false, false, true);
      break;
    case 50:
      LightFlash(false, false, true, true, false, false, true, false);
      break;
    case 51:
      LightFlash(false, false, true, true, false, false, true, true);
      break;
    case 52:
      LightFlash(false, false, true, true, false, true, false, false);
      break;
    case 53:
      LightFlash(false, false, true, true, false, true, false, true);
      break;
    case 54:
      LightFlash(false, false, true, true, false, true, true, false);
      break;
    case 55:
      LightFlash(false, false, true, true, false, true, true, true);
      break;
    case 56:
      LightFlash(false, false, true, true, true, false, false, false);
      break;
    case 57:
      LightFlash(false, false, true, true, true, false, false, true);
      break;
    case 58:
      LightFlash(false, false, true, true, true, false, true, false);
      break;
    case 59:
      LightFlash(false, false, true, true, true, false, true, true);
      break;
    case 60:
      LightFlash(false, false, true, true, true, true, false, false);
      break;
    case 61:
      LightFlash(false, false, true, true, true, true, false, true);
      break;
    case 62:
      LightFlash(false, false, true, true, true, true, true, false);
      break;
    case 63:
      LightFlash(false, false, true, true, true, true, true, true);
      break;
    case 64:
      LightFlash(false, true, false, false, false, false, false, false);
      break;
    case 65:
      LightFlash(false, true, false, false, false, false, false, true);
      break;
    case 66:
      LightFlash(false, true, false, false, false, false, true, false);
      break;
    case 67:
      LightFlash(false, true, false, false, false, false, true, true);
      break;
    case 68:
      LightFlash(false, true, false, false, false, true, false, false);
      break;
    case 69:
      LightFlash(false, true, false, false, false, true, false, true);
      break;
    case 70:
      LightFlash(false, true, false, false, false, true, true, false);
      break;
    case 71:
      LightFlash(false, true, false, false, false, true, true, true);
      break;
    case 72:
      LightFlash(false, true, false, false, true, false, false, false);
      break;
    case 73:
      LightFlash(false, true, false, false, true, false, false, true);
      break;
    case 74:
      LightFlash(false, true, false, false, true, false, true, false);
      break;
    case 75:
      LightFlash(false, true, false, false, true, false, true, true);
      break;
    case 76:
      LightFlash(false, true, false, false, true, true, false, false);
      break;
    case 77:
      LightFlash(false, true, false, false, true, true, false, true);
      break;
    case 78:
      LightFlash(false, true, false, false, true, true, true, false);
      break;
    case 79:
      LightFlash(false, true, false, false, true, true, true, true);
      break;
    case 80:
      LightFlash(false, true, false, true, false, false, false, false);
      break;
    case 81:
      LightFlash(false, true, false, true, false, false, false, true);
      break;
    case 82:
      LightFlash(false, true, false, true, false, false, true, false);
      break;
    case 83:
      LightFlash(false, true, false, true, false, false, true, true);
      break;
    case 84:
      LightFlash(false, true, false, true, false, true, false, false);
      break;
    case 85:
      LightFlash(false, true, false, true, false, true, false, true);
      break;
    case 86:
      LightFlash(false, true, false, true, false, true, true, false);
      break;
    case 87:
      LightFlash(false, true, false, true, false, true, true, true);
      break;
    case 88:
      LightFlash(false, true, false, true, true, false, false, false);
      break;
    case 89:
      LightFlash(false, true, false, true, true, false, false, true);
      break;
    case 90:
      LightFlash(false, true, false, true, true, false, true, false);
      break;
    case 91:
      LightFlash(false, true, false, true, true, false, true, true);
      break;
    case 92:
      LightFlash(false, true, false, true, true, true, false, false);
      break;
    case 93:
      LightFlash(false, true, false, true, true, true, false, true);
      break;
    case 94:
      LightFlash(false, true, false, true, true, true, true, false);
      break;
    case 95:
      LightFlash(false, true, false, true, true, true, true, true);
      break;
    case 96:
      LightFlash(false, true, true, false, false, false, false, false);
      break;
    case 97:
      LightFlash(false, true, true, false, false, false, false, true);
      break;
    case 98:
      LightFlash(false, true, true, false, false, false, true, false);
      break;
    case 99:
      LightFlash(false, true, true, false, false, false, true, true);
      break;
    case 100:
      LightFlash(false, true, true, false, false, true, false, false);
      break;
    case 101:
      LightFlash(false, true, true, false, false, true, false, true);
      break;
    case 102:
      LightFlash(false, true, true, false, false, true, true, false);
      break;
    case 103:
      LightFlash(false, true, true, false, false, true, true, true);
      break;
    case 104:
      LightFlash(false, true, true, false, true, false, false, false);
      break;
    case 105:
      LightFlash(false, true, true, false, true, false, false, true);
      break;
    case 106:
      LightFlash(false, true, true, false, true, false, true, false);
      break;
    case 107:
      LightFlash(false, true, true, false, true, false, true, true);
      break;
    case 108:
      LightFlash(false, true, true, false, true, true, false, false);
      break;
    case 109:
      LightFlash(false, true, true, false, true, true, false, true);
      break;
    case 110:
      LightFlash(false, true, true, false, true, true, true, false);
      break;
    case 111:
      LightFlash(false, true, true, false, true, true, true, true);
      break;
    case 112:
      LightFlash(false, true, true, true, false, false, false, false);
      break;
    case 113:
      LightFlash(false, true, true, true, false, false, false, true);
      break;
    case 114:
      LightFlash(false, true, true, true, false, false, true, false);
      break;
    case 115:
      LightFlash(false, true, true, true, false, false, true, true);
      break;
    case 116:
      LightFlash(false, true, true, true, false, true, false, false);
      break;
    case 117:
      LightFlash(false, true, true, true, false, true, false, true);
      break;
    case 118:
      LightFlash(false, true, true, true, false, true, true, false);
      break;
    case 119:
      LightFlash(false, true, true, true, false, true, true, true);
      break;
    case 120:
      LightFlash(false, true, true, true, true, false, false, false);
      break;
    case 121:
      LightFlash(false, true, true, true, true, false, false, true);
      break;
    case 122:
      LightFlash(false, true, true, true, true, false, true, false);
      break;
    case 123:
      LightFlash(false, true, true, true, true, false, true, true);
      break;
    case 124:
      LightFlash(false, true, true, true, true, true, false, false);
      break;
    case 125:
      LightFlash(false, true, true, true, true, true, false, true);
      break;
    case 126:
      LightFlash(false, true, true, true, true, true, true, false);
      break;
    case 127:
      LightFlash(false, true, true, true, true, true, true, true);
      break;
    case 128:
      LightFlash(true, false, false, false, false, false, false, false);
      break;
    case 129:
      LightFlash(true, false, false, false, false, false, false, true);
      break;
    case 130:
      LightFlash(true, false, false, false, false, false, true, false);
      break;
    case 131:
      LightFlash(true, false, false, false, false, false, true, true);
      break;
    case 132:
      LightFlash(true, false, false, false, false, true, false, false);
      break;
    case 133:
      LightFlash(true, false, false, false, false, true, false, true);
      break;
    case 134:
      LightFlash(true, false, false, false, false, true, true, false);
      break;
    case 135:
      LightFlash(true, false, false, false, false, true, true, true);
      break;
    case 136:
      LightFlash(true, false, false, false, true, false, false, false);
      break;
    case 137:
      LightFlash(true, false, false, false, true, false, false, true);
      break;
    case 138:
      LightFlash(true, false, false, false, true, false, true, false);
      break;
    case 139:
      LightFlash(true, false, false, false, true, false, true, true);
      break;
    case 140:
      LightFlash(true, false, false, false, true, true, false, false);
      break;
    case 141:
      LightFlash(true, false, false, false, true, true, false, true);
      break;
    case 142:
      LightFlash(true, false, false, false, true, true, true, false);
      break;
    case 143:
      LightFlash(true, false, false, false, true, true, true, true);
      break;
    case 144:
      LightFlash(true, false, false, true, false, false, false, false);
      break;
    case 145:
      LightFlash(true, false, false, true, false, false, false, true);
      break;
    case 146:
      LightFlash(true, false, false, true, false, false, true, false);
      break;
    case 147:
      LightFlash(true, false, false, true, false, false, true, true);
      break;
    case 148:
      LightFlash(true, false, false, true, false, true, false, false);
      break;
    case 149:
      LightFlash(true, false, false, true, false, true, false, true);
      break;
    case 150:
      LightFlash(true, false, false, true, false, true, true, false);
      break;
    case 151:
      LightFlash(true, false, false, true, false, true, true, true);
      break;
    case 152:
      LightFlash(true, false, false, true, true, false, false, false);
      break;
    case 153:
      LightFlash(true, false, false, true, true, false, false, true);
      break;
    case 154:
      LightFlash(true, false, false, true, true, false, true, false);
      break;
    case 155:
      LightFlash(true, false, false, true, true, false, true, true);
      break;
    case 156:
      LightFlash(true, false, false, true, true, true, false, false);
      break;
    case 157:
      LightFlash(true, false, false, true, true, true, false, true);
      break;
    case 158:
      LightFlash(true, false, false, true, true, true, true, false);
      break;
    case 159:
      LightFlash(true, false, false, true, true, true, true, true);
      break;
    case 160:
      LightFlash(true, false, true, false, false, false, false, false);
      break;
    case 161:
      LightFlash(true, false, true, false, false, false, false, true);
      break;
    case 162:
      LightFlash(true, false, true, false, false, false, true, false);
      break;
    case 163:
      LightFlash(true, false, true, false, false, false, true, true);
      break;
    case 164:
      LightFlash(true, false, true, false, false, true, false, false);
      break;
    case 165:
      LightFlash(true, false, true, false, false, true, false, true);
      break;
    case 166:
      LightFlash(true, false, true, false, false, true, true, false);
      break;
    case 167:
      LightFlash(true, false, true, false, false, true, true, true);
      break;
    case 168:
      LightFlash(true, false, true, false, true, false, false, false);
      break;
    case 169:
      LightFlash(true, false, true, false, true, false, false, true);
      break;
    case 170:
      LightFlash(true, false, true, false, true, false, true, false);
      break;
    case 171:
      LightFlash(true, false, true, false, true, false, true, true);
      break;
    case 172:
      LightFlash(true, false, true, false, true, true, false, false);
      break;
    case 173:
      LightFlash(true, false, true, false, true, true, false, true);
      break;
    case 174:
      LightFlash(true, false, true, false, true, true, true, false);
      break;
    case 175:
      LightFlash(true, false, true, false, true, true, true, true);
      break;
    case 176:
      LightFlash(true, false, true, true, false, false, false, false);
      break;
    case 177:
      LightFlash(true, false, true, true, false, false, false, true);
      break;
    case 178:
      LightFlash(true, false, true, true, false, false, true, false);
      break;
    case 179:
      LightFlash(true, false, true, true, false, false, true, true);
      break;
    case 180:
      LightFlash(true, false, true, true, false, true, false, false);
      break;
    case 181:
      LightFlash(true, false, true, true, false, true, false, true);
      break;
    case 182:
      LightFlash(true, false, true, true, false, true, true, false);
      break;
    case 183:
      LightFlash(true, false, true, true, false, true, true, true);
      break;
    case 184:
      LightFlash(true, false, true, true, true, false, false, false);
      break;
    case 185:
      LightFlash(true, false, true, true, true, false, false, true);
      break;
    case 186:
      LightFlash(true, false, true, true, true, false, true, false);
      break;
    case 187:
      LightFlash(true, false, true, true, true, false, true, true);
      break;
    case 188:
      LightFlash(true, false, true, true, true, true, false, false);
      break;
    case 189:
      LightFlash(true, false, true, true, true, true, false, true);
      break;
    case 190:
      LightFlash(true, false, true, true, true, true, true, false);
      break;
    case 191:
      LightFlash(true, false, true, true, true, true, true, true);
      break;
    case 192:
      LightFlash(true, true, false, false, false, false, false, false);
      break;
    case 193:
      LightFlash(true, true, false, false, false, false, false, true);
      break;
    case 194:
      LightFlash(true, true, false, false, false, false, true, false);
      break;
    case 195:
      LightFlash(true, true, false, false, false, false, true, true);
      break;
    case 196:
      LightFlash(true, true, false, false, false, true, false, false);
      break;
    case 197:
      LightFlash(true, true, false, false, false, true, false, true);
      break;
    case 198:
      LightFlash(true, true, false, false, false, true, true, false);
      break;
    case 199:
      LightFlash(true, true, false, false, false, true, true, true);
      break;
    case 200:
      LightFlash(true, true, false, false, true, false, false, false);
      break;
    case 201:
      LightFlash(true, true, false, false, true, false, false, true);
      break;
    case 202:
      LightFlash(true, true, false, false, true, false, true, false);
      break;
    case 203:
      LightFlash(true, true, false, false, true, false, true, true);
      break;
    case 204:
      LightFlash(true, true, false, false, true, true, false, false);
      break;
    case 205:
      LightFlash(true, true, false, false, true, true, false, true);
      break;
    case 206:
      LightFlash(true, true, false, false, true, true, true, false);
      break;
    case 207:
      LightFlash(true, true, false, false, true, true, true, true);
      break;
    case 208:
      LightFlash(true, true, false, true, false, false, false, false);
      break;
    case 209:
      LightFlash(true, true, false, true, false, false, false, true);
      break;
    case 210:
      LightFlash(true, true, false, true, false, false, true, false);
      break;
    case 211:
      LightFlash(true, true, false, true, false, false, true, true);
      break;
    case 212:
      LightFlash(true, true, false, true, false, true, false, false);
      break;
    case 213:
      LightFlash(true, true, false, true, false, true, false, true);
      break;
    case 214:
      LightFlash(true, true, false, true, false, true, true, false);
      break;
    case 215:
      LightFlash(true, true, false, true, false, true, true, true);
      break;
    case 216:
      LightFlash(true, true, false, true, true, false, false, false);
      break;
    case 217:
      LightFlash(true, true, false, true, true, false, false, true);
      break;
    case 218:
      LightFlash(true, true, false, true, true, false, true, false);
      break;
    case 219:
      LightFlash(true, true, false, true, true, false, true, true);
      break;
    case 220:
      LightFlash(true, true, false, true, true, true, false, false);
      break;
    case 221:
      LightFlash(true, true, false, true, true, true, false, true);
      break;
    case 222:
      LightFlash(true, true, false, true, true, true, true, false);
      break;
    case 223:
      LightFlash(true, true, false, true, true, true, true, true);
      break;
    case 224:
      LightFlash(true, true, true, false, false, false, false, false);
      break;
    case 225:
      LightFlash(true, true, true, false, false, false, false, true);
      break;
    case 226:
      LightFlash(true, true, true, false, false, false, true, false);
      break;
    case 227:
      LightFlash(true, true, true, false, false, false, true, true);
      break;
    case 228:
      LightFlash(true, true, true, false, false, true, false, false);
      break;
    case 229:
      LightFlash(true, true, true, false, false, true, false, true);
      break;
    case 230:
      LightFlash(true, true, true, false, false, true, true, false);
      break;
    case 231:
      LightFlash(true, true, true, false, false, true, true, true);
      break;
    case 232:
      LightFlash(true, true, true, false, true, false, false, false);
      break;
    case 233:
      LightFlash(true, true, true, false, true, false, false, true);
      break;
    case 234:
      LightFlash(true, true, true, false, true, false, true, false);
      break;
    case 235:
      LightFlash(true, true, true, false, true, false, true, true);
      break;
    case 236:
      LightFlash(true, true, true, false, true, true, false, false);
      break;
    case 237:
      LightFlash(true, true, true, false, true, true, false, true);
      break;
    case 238:
      LightFlash(true, true, true, false, true, true, true, false);
      break;
    case 239:
      LightFlash(true, true, true, false, true, true, true, true);
      break;
    case 240:
      LightFlash(true, true, true, true, false, false, false, false);
      break;
    case 241:
      LightFlash(true, true, true, true, false, false, false, true);
      break;
    case 242:
      LightFlash(true, true, true, true, false, false, true, false);
      break;
    case 243:
      LightFlash(true, true, true, true, false, false, true, true);
      break;
    case 244:
      LightFlash(true, true, true, true, false, true, false, false);
      break;
    case 245:
      LightFlash(true, true, true, true, false, true, false, true);
      break;
    case 246:
      LightFlash(true, true, true, true, false, true, true, false);
      break;
    case 247:
      LightFlash(true, true, true, true, false, true, true, true);
      break;
    case 248:
      LightFlash(true, true, true, true, true, false, false, false);
      break;
    case 249:
      LightFlash(true, true, true, true, true, false, false, true);
      break;
    case 250:
      LightFlash(true, true, true, true, true, false, true, false);
      break;
    case 251:
      LightFlash(true, true, true, true, true, false, true, true);
      break;
    case 252:
      LightFlash(true, true, true, true, true, true, false, false);
      break;
    case 253:
      LightFlash(true, true, true, true, true, true, false, true);
      break;
    case 254:
      LightFlash(true, true, true, true, true, true, true, false);
      break;
    case 255:
      LightFlash(true, true, true, true, true, true, true, true);
      break;
    default:
      Serial.println("Erro inesperado");
      break;
  }
}

void LightFlash(boolean a, boolean b, boolean c, boolean d, boolean e, boolean f, boolean g, boolean h) {

  digitalWrite(5, LOW);
  delay(signalDelay/2);
  digitalWrite(5, HIGH);
  delay(signalDelay/2);

  //digitalWrite(5, LOW);
  if (a == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (b == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (c == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (d == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (e == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (f == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (g == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  if (h == true) {
    digitalWrite(5, LOW);
  }
  delay(standardDelay/2);

  digitalWrite(5, HIGH);
  delay(standardDelay/2);
  //delay(standardDelay);
}

void loop() {
}

