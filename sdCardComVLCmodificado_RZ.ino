#include <SD.h> // Utilizar biblioteca para cartão SD
#include <SPI.h> // Utilizar biblioteca da comunicação SPI - Serial Peripheral Interface Bus
#define chipSelect 10

static int Limiar = 500; // Static preserva o dado da variável entre as funções chamadas
static float standardDelay = 5;
static unsigned int signalDelay = 10;
boolean sensorValue1;
boolean sensorValue2;
boolean sensorValue3;
boolean sensorValue4;
boolean sensorValue5;
boolean sensorValue6;
boolean sensorValue7;
boolean sensorValue8;

void setup() {

  // When using hardware SPI, the SS pin MUST be set to an
  // output (even if not connected or used).  If left as a
  // floating input w/SPI on, this can cause lockuppage.
#if !defined(SOFTWARE_SPI)
#if defined(__AVR_ATmega1280__) || defined(__AVR_ATmega2560__)
  if (chipSelect != 53) pinMode(53, OUTPUT); // SS on Mega
#else
  if (chipSelect != 10) pinMode(10, OUTPUT); // SS on Uno, etc.
#endif
#endif

  Serial.begin(9600); // Inicializa a porta serial de comunicação a uma taxa de 9600 bps
  pinMode(5, OUTPUT); //digital PWM 3 on output
  Serial.print("Teste do cartão SD...");

  if (!SD.begin(chipSelect)) { // Se o cartão não inicializar, executa as próximas funções, que são informar a falha e finalizar programa
    Serial.println("Card failed, or not present");
    // don't do anything more:
    return; //finaliza o programa
  }
  Serial.println(" Cartão OK!");

  Serial.print("Testando câmera...");

  digitalWrite(5, HIGH); // Liga o Led no pino 3 por 500ms
  delay(signalDelay/2);
  digitalWrite(5, LOW); // Desliga o Led e espera 500ms
  delay(signalDelay/2);

  Leitura();
  
  unsigned int Teste = pow(2, 7) * sensorValue1 + pow(2, 6) * sensorValue2 + pow(2, 5) * sensorValue3 + pow(2, 4) * sensorValue4 +
                       pow(2, 3) * sensorValue5 + pow(2, 2) * sensorValue6 + pow(2, 1) * sensorValue7 + pow(2, 0) * sensorValue8;

  if (Teste == 10) { // Verifica se o sensor recebe um retorno de que a câmera está funcionando
    Serial.print(" Câmera não encontrada");
    return;
  }
  else if (Teste == 5){
    Serial.println(" Câmera OK!");
  }
  else {
    Serial.print("... Valor Teste = ");
    Serial.print(Teste);
    return;
  }
  delay(signalDelay/2);

  /*digitalWrite(5, HIGH); // Liga o Led no pino 3 por 500ms
  delay(signalDelay/2);
  digitalWrite(5, LOW); // Desliga o Led e espera 500ms
  delay(signalDelay/2);*/
  
  while (analogRead(A0) < Limiar) {
    ;
  }
  //delay(signalDelay/2);
  Serial.println("Câmera tirou foto");

  // Create an image with the name IMAGExx.JPG
  char filename[13];
  strcpy(filename, "IMAGE00.JPG"); //Grava todas as strings do nome da imagem de uma vez no filename.
  for (int i = 0; i < 100; i++) {
    filename[5] = '0' + i / 10; //Soma-se o valor do quociente da divisão.
    filename[6] = '0' + i % 10; //Soma-se o valor do resto da divisão.
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) { //Testa se o nome criado já existe.
      break;
    }
  }

  // Open the file for writing
  File imgFile = SD.open(filename, FILE_WRITE);

  Leitura();
  unsigned int highbyte = pow(2, 15) * sensorValue1 + pow(2, 14) * sensorValue2 + pow(2, 13) * sensorValue3 + pow(2, 12) * sensorValue4 +
                          pow(2, 11) * sensorValue5 + pow(2, 10) * sensorValue6 + pow(2, 9) * sensorValue7 + pow(2, 8) * sensorValue8;

  Leitura();
  unsigned int lowbyte = pow(2, 7) * sensorValue1 + pow(2, 6) * sensorValue2 + pow(2, 5) * sensorValue3 + pow(2, 4) * sensorValue4 +
                         pow(2, 3) * sensorValue5 + pow(2, 2) * sensorValue6 + pow(2, 1) * sensorValue7 + pow(2, 0) * sensorValue8;

  uint16_t jpglen = highbyte + lowbyte;
  Serial.println("A imagem tem ");
  Serial.print(jpglen);
  Serial.println(" bytes");

  int32_t time = millis();
  pinMode(8, OUTPUT);
  
  while (jpglen > 0) { //Executa procedimentos enquanto "varre" todos os bytes da imagem.

    // read 1 byte at a time;
    uint8_t bytesToRead = min(1, jpglen);

    Leitura();

    uint8_t buf = pow(2, 7) * sensorValue1 + pow(2, 6) * sensorValue2 + pow(2, 5) * sensorValue3 + pow(2, 4) * sensorValue4 +
                  pow(2, 3) * sensorValue5 + pow(2, 2) * sensorValue6 + pow(2, 1) * sensorValue7 + pow(2, 0) * sensorValue8;
     
    imgFile.write(buf); //Escreve o valor do byte recebido no arquivo de imagem criado.
    Serial.println(buf);

    jpglen -= bytesToRead; //Decrementa o valor do tamanho da imagem.
    Serial.print("Jpglen = ");
    Serial.println(jpglen);
  }
  imgFile.close();

  time = millis() - time; //Informa o tempo de transferência da imagem para o cartão.
  Serial.println("done!");
  Serial.print(time); Serial.print(" ms elapsed");
}

void Leitura(void) {

  while (analogRead(A0) < Limiar) {
    ;
  }
  delay(signalDelay);

  sensorValue1 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue2 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue3 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue4 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue5 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue6 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue7 = (analogRead(A0) > Limiar);
  delay(standardDelay);

  sensorValue8 = (analogRead(A0) > Limiar);
  delay(standardDelay);
  //delay(standardDelay);
}

void loop() {
  // put your main code here, to run repeatedly:

}
