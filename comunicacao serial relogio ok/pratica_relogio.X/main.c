#include<p18f4550.h>
#include <delays.h>
#include <plib/usart.h>
#include<p18f4550.h>
#include "relogio.h"
#include "lcd.h"
#include "var.h"
#include "UART.h"
#include <stdio.h>
#include <stdlib.h>

#pragma CONFIG WTG=OFF // DESLIGA O WATCHDOG TIMER
#pragma config PBADEN = OFF // NECESSÁRIO PARA USAR O DISPLAY.

void main(void) {
    //INICIALIZAÇÕES  
    //inicialização das variáveis do relógio
    ca.ano = 2004;
    ca.mes = 2;
    ca.dia = 28;
    re.hora=23;
    re.minuto=59;
    re.segundo=35;
    alarme.hora = 5;
    alarme.minuto = 2;
    alarme.segundo = 1;
    flagDisplay = 1;
    flag_inicializacao = 1;
    contador = 0;
    flagTela = 1;
    T1 = 0;
    T2 = 0;
    posCursor = 0;
    posCursorR = 0;
    tempoAlarme = 0;
    
    T0CONbits.TMR0ON=1; // HABILITA O TIMER 0;
    INTCONbits.TMR0IE=1; // HABILITA A FLAG DE INTERRUPÇÃO.
    INTCONbits.TMR0IF=0; // LIMPA A FLAG.
    // CÁLCULO DE CONTADOR DA INTERRUPÇÃO:
    T0CONbits.T08BIT=0;
    T0CONbits.PSA=0;
    T0CONbits.T0PS0=1;
    T0CONbits.T0PS1=0;
    T0CONbits.T0PS2=1;
    T0CONbits.T0CS=0; // UTILIZAR CLOCK INTERNO.
    
    TMR0=2535; // DE ONDE INICIA O CONTADOR. 
    
    T0CONbits.TMR0ON=1;// HABILITA O TIMER0
    
    TRISB = 0; // SETA TODAS AS PORTAS B COMO SAÍDA
    TRISD = 1; // SETA TODAS AS PORTAS D COMO ENTRADA
    
    //HABILITANDO INTERRUPÇÕES
    INTCONbits.GIEH=1; 
    INTCONbits.GIEL=1;
  
    InitXLCD();
    inicializaTela1();
    inicializarUART();
    //inicializaTela2();
       
    while(1){
        if(flagDisplay == 1){
            atualiza_tela();
            flagDisplay = 0;
        }
        
        if(PORTDbits.RD0 == 1){ // botao para mudar tela
            __delay_ms(180);
            LCD_Clear();
            flagTela++;
            if(flagTela>2) flagTela = 1;
            while(PORTDbits.RD0==1){} 
        }
        
        if(PORTDbits.RD1 == 1){ // botão mover cursor
            __delay_ms(180);
            posCursor++;
            posCursorR++;
            if(posCursor > 2) posCursor = 0;
            if(posCursorR > 6) posCursorR = 0;
            while(PORTDbits.RD1==1){}
        }
        
        if(flagTela == 1) ajustarT1();
        if(flagTela == 2 && flagAlarme == 0) ajustarAlarme();  // so ajusto o alarme se estiver na tela 2 e ele nao estiver disparando
        if(despertar() == 1)  flagAlarme = 1; // se o horario do alarme coincidiu vou acionar a variavel de controle
        
        if(flagAlarme == 1) { // se a variavel de controle for acionada vou exibir o aviso na tela por 35 segundos
            if(tempoAlarme < 35){
                despertarAlarme();
            }else{
                flagAlarme = 0;
            }
                
        }
        maquina_estado();
    }
    return;
}

////CONFIGURANDO A INTERRUPÇÃO
//void __interrupt() pic_isr(void){
//    if(TMR0IF){  
//        TMR0=2535;// RESETA CONTADOR PARA O VALOR ESTABELECIDO (AJUSTE PARA OS SEGUNDOS)
//        INTCONbits.TMR0IF=0; //ZERA A FLAG DO TIMER0
//        contador++;
//    }
//    if(contador>1){ // AJUSTE DE CÁLCULO PARA OS SEGUNDOS
//        if(flag_inicializacao == 1 ){ // garantindo que na primeira execução será exibido o segundo "zero"
//            flag_inicializacao = -1;
//        }else{
//            tratar_relogio(&ca, &re); // FUNÇÃO PARA O RELÓGIO SE AJUSTAR
//            flagDisplay = 1;
//            contador=0;
//        }              
//    }
//}

void interrupt SerialRxPinInterrupt(){
    if(TMR0IF){  
        TMR0=2535;// RESETA CONTADOR PARA O VALOR ESTABELECIDO (AJUSTE PARA OS SEGUNDOS)
        INTCONbits.TMR0IF=0; //ZERA A FLAG DO TIMER0
        contador++;
    }
    if(contador>1){ // AJUSTE DE CÁLCULO PARA OS SEGUNDOS
        if(flag_inicializacao == 1 ){ // garantindo que na primeira execução será exibido o segundo "zero"
            flag_inicializacao = -1;
        }else{
            tratar_relogio(&ca, &re); // FUNÇÃO PARA O RELÓGIO SE AJUSTAR
            flagDisplay = 1;
            contador=0;
        }              
    }

    //check if the interrupt is caused by RX pin
    if(PIR1bits.RCIF == 1){
        if(i<7){
        	while(!RCIF);//recepeção de dados concluido? RCIF vale 1
            	dado[i]= converte_char_hex(RCREG);                                 // Retrieve data from reception register
            	i++;  
        }else{
            PIR1bits.RCIF = 0; // clear rx flag
            i=0;
			//ESTADO_COMUNICACAO = COMANDO_RECEBIDO;
            
            
            if (ESTADO_COMUNICACAO == ESPERA_COMANDO){
                ESTADO_COMUNICACAO = COMANDO_OK;
                //entrar = 0;
            } else {
                ESTADO_COMUNICACAO = ENVIA_RESPOSTA;
                
            }   
        } 
    }
}