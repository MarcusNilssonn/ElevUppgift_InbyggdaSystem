#include "UART.h"
#include "LED.h"
#include "LED.c"

//Skapa två LED-lampor
Led_Type led1; 
Led_Type led2;

int main(void){ //huvudfunktion som konstruerar och hanterar LED-lamporna
  USART2_Init();
  
  //Anger färg och status till led1 och led 2.
  Led_ctor(&led1,RED,OFF); 
  Led_ctor(&led2,BLUE,ON);
  
  Led_getState(&led1); //Kolla statusen på led1
  Led_setState(&led2,OFF); //Sätt statusen på led2 till off.
  
  while(1){}
  
}