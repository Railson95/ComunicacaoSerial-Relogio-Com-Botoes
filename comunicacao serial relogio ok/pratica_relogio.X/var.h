#include "relogio.h"

#define ESPERA_COMANDO      0x00
#define COMANDO_RECEBIDO    0x01
#define VERIFICAR_COMANDO   0x02
#define COMANDO_OK          0x03
#define COMANDO_NOK         0x04
#define ENVIA_RESPOSTA      0x05
#define COMANDO_LEITURA     0x01
#define COMANDO_ALTERACAO   0x02
#define HORA                0x01
#define DDATA               0x02
#define ALARME              0x03

#define _XTAL_FREQ 80000000 // DEFINE A FREQUÊNCIA
#define POLY 0x8408
#define FREQ 80000000    // Frequency = 12MHz
#define baud 9600
#define spbrg_value (((FREQ/64)/baud)-1)    // Refer to the formula for Baud rate calculation in Description tab

unsigned char ESTADO_COMUNICACAO;
unsigned char serial_data;
unsigned int i ;
unsigned char dado[7];
unsigned char BUFFRESP[7];


//VARIÁVEIS GLOBAIS
calendario ca;
relogio re;
relogio alarme;
int flagDisplay; // controla a atualização da hora no display
int flag_inicializacao; // garante que a primeira contagem inicie no 0
int contador; // ajusta o cálculo para contagem dos segundos

int flagTela; // controle de qual tela exibir
int T1, T2; // controle de inicializações das telas
int posCursor; // controla a posicao do cursor para a tela de alarme
int posCursorR; // controla a posicao do cursor para a tela do relogio
int flagAlarme;// controla se o alarme deve ser acionado ou nao
int tempoAlarme;// control o tempo que o alarme permanesce acionado
int entrar;
