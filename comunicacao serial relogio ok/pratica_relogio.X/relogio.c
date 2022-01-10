#include "relogio.h"
#include "var.h"

int qtdDias_mes[] = {31,28,31,30,31,30,31,31,30,31,30,31}; // dias para cada mês do ano

void verifica_b(int ano){ // VERIFICAÇÃO E AJUSTE SE O ANO EM QUESTÃO É BISSEXTO OU NÃO
    if(ano%4==0){
        qtdDias_mes[1] = 29;
    }else{
        qtdDias_mes[1] = 28;
    }
}

void tratar_relogio(calendario *c, relogio *r){ // AJUSTE DO FUNCIONAMENTO DO RELÓGIO
    r->segundo++;
    verifica_b(c->ano);
    if(tempoAlarme < 35 && flagAlarme == 1){
        tempoAlarme++;
    }else{
        tempoAlarme = 0;
    }
        
    if(r->segundo > 59){
        r->minuto++;
        r->segundo = 0;
    }
    if(r->minuto > 59){
        r->hora++;
        r->minuto = 0;
    }    
    if(r->hora > 23){
        c->dia++;
        r->hora = 0;
    }    
    if(c->dia > qtdDias_mes[c->mes-1]){
        c->mes++;
        c->dia = 1;
    }    
    if(c->mes > 12){
        c->ano++;
        c->mes = 1;
        c->dia = 1;
        verifica_b(c->ano);
    } 
    if(c->dia < 1){
        c->dia = qtdDias_mes[c->mes -2];
        c->mes--;
    }
    if(c->mes < 1){
        c->mes = 12;
        c->ano--;
        verifica_b(c->ano);
    }
    
    if(c->ano < 0) c->ano = 0;
    
    if(r->hora < 0){
        c->dia--;
        r->hora = 23;
    }

    if(r->minuto < 0){
        r->minuto = 59;
        r->hora--;
    }
    
    if(r->segundo < 0){
        r->segundo = 59;
        r->minuto--;
    }
  
    
    
}

void tratar_alarme(relogio *c){
    if(c->hora > 23) c->hora = 0;
    
    if(c->minuto > 59) c->minuto = 0;
    
    if(c->segundo > 59) c->segundo = 0;
    
    if(c->hora < 0) c->hora = 23;
    
    if(c->minuto < 0) c->minuto = 59;
    
    if(c->segundo < 0) c->segundo = 59;
    
}

int despertar(){
    if(re.hora == alarme.hora && re.minuto == alarme.minuto && re.segundo == alarme.segundo){
        return 1;
    }else{
        return 0;
    }
    
}