#ifndef LED_H
#define LED_H //Definierar headern

#include <stdint.h> // Inkludera standardbibliotek för C. 
#include "UART.h" // Inkluderar vår Uart-header, vår drivrutin.
#include "stm32f4xx.h" //Inkludera bibliotek för enhetsspecifika angivelser om hårdvaran

//Definiera vilken GPIO som skall vara ansvarig för LED-funktionen. Alla gånger headern inkluderas och LED_PORT skrivs så är detta synonymt med GPIOB
#define	LED_PORT GPIOB

//Definiera klocksignalen för porten genom att skriva över bit 1 med 1.
#define	LED_PORT_CLOCK (1U<<1)

//Definiera de olika pinsen som används för de olika LED-färgerna genom att ange dom olika pinsen
#define LED_RED_PIN	(1U<<14) //Ex bit 14 sätts till 1.
#define LED_GREEN_PIN (1U<<12)
#define	LED_BLUE_PIN (1U<<15)
#define LED_YELLOW_PIN (1U<<13)

//Definiera mode bits för varje LED-färg
#define LED_RED_MODE_BIT (1U<<28)
#define LED_GREEN_MODE_BIT (1U<<24)
#define LED_YELLOW_MODE_BIT (1U<<26)
#define LED_BLUE_MODE_BIT (1U<<30)

//Definiera de olika LED-färgerna som finns
typedef  enum {
	RED	= 0, //Röd börjar på 0, Grön är 1 osv.
	GREEN,
	YELLOW,
	BLUE
}LedColor_Type; //Döps till LedColor_Type som kan anta en av dom olika färgerna och betecknas 0-3.

//Definierar status/de olika lägen som LED kan befinna sig i, genom numrering.
typedef enum {
	OFF =0,
	ON = 1
}LedState_Type; //Döps till LedState_Type

// Skapa Led_Type som ska bestå av variablerna color och state.
typedef struct {
	LedColor_Type color; 
	LedState_Type state;  
}Led_Type;

//Deklarerar funktionerna för LED-konstruktion och statuskontrollen som ska inkluderas i LED.c
void Led_ctor(Led_Type * const me, LedColor_Type _color, LedState_Type _state);
void Led_setState(Led_Type * const me,LedState_Type _state);
LedState_Type Led_getState(Led_Type * const me);

#endif // Avslutning av headerfil
