// Exemplo de uso da Multi Function Shield - Display
// DQ, dez/2016
// http://dqsoft.blogspot.com
//
// Retirado uso da lib TimerOne - Marcelo Campos - Jun/18
//
//#include<TimerOne.h>
#define TEMPO_ATUALIZACAO  33

const int pinLatch = 4;
const int pinClock = 7;
const int pinDado = 8;

// Desenho dos numeros
const uint8_t numero[10] = {
  0xC0, 0xF9, 0xA4, 0xB0, 0x99, 0x92, 0x82, 0xF8, 0x80, 0x90
};

// Selecao dos digitos
const uint8_t digito[4] = {
  0x01, 0x02, 0x04, 0x08
};

// Valor a apresentar no display
uint8_t valor[4];

// Inicia��o
void setup() {
  Serial.begin(9600);
  // Inicia os pinos ligados ao display
  pinMode (pinLatch, OUTPUT);
  pinMode (pinClock, OUTPUT);
  pinMode (pinDado, OUTPUT);
 
  // Inicia o timer
//  Timer1.initialize(2000); // 2 ms
//  Timer1.attachInterrupt (timerIsr);
}

// Programa principal
void loop()
{
  static int cont = 0;
  static int TEMPO_CONTAGEM = 200;
  static int ultimaContagem = 0;
 
  while (1)
  { 
    if(millis() - ultimaContagem >= TEMPO_CONTAGEM)
    {
      cont++;
      ultimaContagem = millis();
             
      valor[0] = cont / 1000;
      valor[1] = (cont % 1000)/100;
      valor[2] = ((cont % 1000)%100) /10;
      valor[3] = ((cont % 1000)%100) % 10;
    }
 
    AtualizaDisplays();
  }

}

void AtualizaDisplays()
{
  static unsigned long ultimaAtualizacao = millis();
 
  if(millis() - ultimaAtualizacao >= TEMPO_ATUALIZACAO )
  {
   timerIsr();
  }
}

// atualiza o display a cada TEMPO_ATUALIZACAO ms
void timerIsr() {
  static uint8_t iDig = 0;
 
  digitalWrite(pinLatch, LOW);
  shiftOut(pinDado, pinClock, MSBFIRST, numero[valor[iDig]]);
  shiftOut(pinDado, pinClock, MSBFIRST, digito[iDig]);
  digitalWrite(pinLatch, HIGH);
  iDig = (iDig+1) & 3;
}
