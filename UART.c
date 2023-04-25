#include "UART.h"
#include "stm32f4xx.h"
#include <stdio.h>

void USART2_Init(void){ //Deklarerar en funktion för att initiera UART-protokollet och dess beståndsdelar
 RCC->APB1ENR  |=  0x20000; //Aktiverar UART2 genom att sätta bit 17 till 1.
 RCC->AHB1ENR   |=0x01; //Aktiverar GPIOA genom att sätta bit 0 i AHB1ENR till 1.
 
GPIOA->MODER &=~0x00F0; //Rensar bitarna 4-7 för att förbereda pins PA2 och PA3, så att inget gammalt hänger kvar utan det sätts till 0000
GPIOA->MODER |= 0x00A0; //Sätter bitarna 5 och 7 till 1 för att aktivera alternativ funktionalitet på pins PA2 och PA3.

GPIOA->AFR[0] &= ~0xFF00; //Rensar bitarna 4-7 för att förbereda pins PA2 och PA3
GPIOA->AFR[0] |= 0x7700; //Sätter bitarna 8-11 samt 12-15 till formatet 0111


USART2->BRR  =  0x0683; //Sätter standard baud-rate med hjälp av hexadecimalen 0x0693 som motsvarar standard 9600
USART2->CR1  =  0x000C; //Sätter vi tx och rx till att arbeta i 8 bitars-data. (8 bitars data, 1 stop-bit, ingen paritet.)
USART2->CR2  =  0x000; //Nollstället CR2 för att undvika kommunikationskonflikter
USART2->CR3  =  0x000; //Nollställer CR3
USART2->CR1  |=  0x2000; //Omställer bit 13 (UART-aktiveringen) till 1.
	
	

}

int USART2_write(int ch){

	while(!(USART2->SR & 0x0080)){}
	USART2->DR = (ch & 0xFF);
	
  return ch;
}

int USART2_read(void){
  while(!(USART2->SR & 0x0020)){}
	return USART2->DR;
}

struct __FILE { int handle; };
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};


int fgetc(FILE *f) {
    int c;

    c = USART2_read();     

    if (c == '\r') {        
        USART2_write(c);    
        c = '\n';
    }

    USART2_write(c);       

    return c;
}

int fputc(int c, FILE *f) {
    return USART2_write(c);
}


int n;
char str[80];
		
void test_setup(void){
	
	printf("please enter a number: ");
	scanf("%d", &n);
	printf("the number entered is: %d\r\n", n);
	printf("please type a character string: ");
	gets(str);
	printf("the character string entered is: ");
	puts(str);
	printf("\r\n");
	
}
