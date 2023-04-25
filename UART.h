#ifndef  __UART_H //Kolla om "__UART_H är definierat"
#define  __UART_H //Om inte så definieras det och all kod som följer inkluderas.


#include "stm32f4xx.h" //Inkludera bibliotek för denna microkontroller så att vi kan använda allt som finns i dokumentationen.                 
#include <stdio.h> //Inkludera standardbibliotek.

void USART2_Init(void); //Initiera en funktion som inte returnerar något och ej heller tar parametrar.
void test_setup(void); //Initiera en funktion som inte returnerar något och ej heller tar parametrar.


#endif
