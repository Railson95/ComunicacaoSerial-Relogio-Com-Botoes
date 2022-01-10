# Relógio com comunicação serial e botões
Sobre
=================
Neste projeto foi criado um relógio por onde o usuário pode, ajustar horas,minutos, segundos, dias, meses e anos. Além disso, o relógio conta com a função de alarme, o usuário pode configurar o relógio tanto por via de um terminal serial e também com o auxílio de botões

<img src="https://img.shields.io/badge/c-microcontroladores-blue"/> <img src="https://img.shields.io/badge/8%20bits-18f4550-orange"/>

Tabela de conteúdos
=================
<!--ts-->
   * [Sobre](#Sobre)
   * [Tabela de Conteudo](#tabela-de-conteudo)
   * [Instalação](#instalacao)
   * [Como usar](#como-usar)
      * [Pre Requisitos](#pre-requisitos)
      * [Funcionamento botoes](#fun-botoes)
      * [Comunicacao serial](#com-serial)
   * [Tests](#testes)
   * [Tecnologias](#tecnologias)
<!--te-->

Como usar
=================

Pre Requisitos
----
```bash
Para rodar o sistema será necessário a instalação
*MPLAB X IDE v3.55
*XC8 v1.41
*peripheral-libraries-for-pic18-v2.00rc3
*Proteus Professional 8.5 - SP0
```

Funcionamento botoes
----
```bash
Neste sistema a 4 botões
1) Trocar tela -> podendo seguir tanto para Hora e Data ou alarme
2) Trocar cursor -> move o cursor do LCD entre as casas
3) Incrementar 
4) Decrementar
```
Comunicacao serial
----
```bash
Para que a comunicação serial funcione, onde o usuário poderá atualizar o relógio ou mesmo mostrar os dados atuais em outro terminal, é necessário seguir a seguinte lógica
1) Se for digitado 1, 1: Será mostrado a hora atual no segundo terminal
2) se for digital  1, 2: Será mostrado a data atual no segundo terminal
3) se for digital  1, 3: Será mostrado o alarme atual no segundo terminal
4) se for digital  2, 1, HH, MM, SS: Será atualizado a hora do relógio e mostrado no segundo terminal
5) se for digital  2, 2, DD, MM, AA: Será atualizado a data do relógio e mostrado no segundo terminal
6) se for digital  2, 3, HH, MM, SS: Será atualizado o alarme do relógio e mostrado no segundo terminal
```
Tests
----

<div align="center">
<img src="https://github.com/Railson95/ComunicacaoSerial-Relogio-Com-Botoes/issues/1#issue-1098209582" width="700px" />
</div>

		
