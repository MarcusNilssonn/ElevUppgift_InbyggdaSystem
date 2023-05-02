#include "LED.h" //Inkludera headerfilen

//Konstruktorn för LED-lamporna med typ, färg och status
void Led_ctor(Led_Type * const me, LedColor_Type _color, LedState_Type _state){
  
	me->color  = _color; //Konstant som pekar till begreppet color. Pekar på adressen till headern där våra faktiska värden ligger.
	me->state  = _state; //Konstant som pekar till begreppet status. Pekar på adressen till headern där våra faktiska värden ligger.

	//Enablea klockan för LED-porten (GPIOB)
	RCC->AHB1ENR |= LED_PORT_CLOCK; //Använder LED_PORT_CLOCK från headern  
	
	//Konfiguera LED-pinsen utifrån färg och status
	switch(_color){
		 
		case RED: //Om röd. 
			LED_PORT->MODER |=LED_RED_MODE_BIT; //Gå in i mode-register och aktivera pins. Sätta portläget för LED-konfigurationen till output
		  if(me->state  == ON){ //Kontrollera outputen. Sätter på LED om statusen är "ON"
			   LED_PORT->ODR |= LED_RED_PIN;
				printf("The RED Led is set ON \n\r");
			}
			else{ //Annars, stäng av LED.
			  LED_PORT->ODR &= ~LED_RED_PIN;
        		printf("The RED Led is set OFF \n\r");

			}
			break;
		//Upprepa samma för övriga färger.
		case YELLOW: 
			LED_PORT->MODER |=LED_YELLOW_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_YELLOW_PIN;
				printf("The YELLOW Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_YELLOW_PIN;
        printf("The YELLOW Led is set OFF \n\r");

			}
		break;
		
		case BLUE: 
			LED_PORT->MODER |=LED_BLUE_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_BLUE_PIN;
				printf("The BLUE Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_BLUE_PIN;
        printf("The BLUE Led is set OFF \n\r");

			}
		break;
		
		case GREEN:
			LED_PORT->MODER |=LED_GREEN_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_GREEN_PIN;
				printf("The GREEN Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_GREEN_PIN;
        printf("The GREEN Led is set OFF \n\r");

			}
		break;
	}
}

void Led_setState(Led_Type * const me,LedState_Type _state){
	//Sätter statusen på LED.
	 me->state =  _state;

	//Kolla färgen på LED för att veta att korrekt LED har manipulerats
	switch(me->color){
		 //om LED har färgen Röd
		case RED:
			LED_PORT->MODER |=LED_RED_MODE_BIT; //Sätt pin till outputläge
		  if(me->state  == ON){ //Om status är ON
			   LED_PORT->ODR |= LED_RED_PIN; //Definiera pinsens output till aktiv
				printf("The RED Led is set ON \n\r"); 
			}
			else{
			  LED_PORT->ODR &= ~LED_RED_PIN; //Sätt pin output till inaktiv
        		printf("The RED Led is set OFF \n\r");

			}
			break;
		//Upprepa allt för övriga färger.
		case YELLOW:
			LED_PORT->MODER |=LED_YELLOW_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_YELLOW_PIN;
				printf("The YELLOW Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_YELLOW_PIN;
        		printf("The YELLOW Led is set OFF \n\r");

			}
			break;
		
		case BLUE:
			LED_PORT->MODER |=LED_BLUE_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_BLUE_PIN;
				printf("The BLUE Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_BLUE_PIN;
        		printf("The BLUE Led is set OFF \n\r");

			}
			break;
		
		case GREEN:
			LED_PORT->MODER |=LED_GREEN_MODE_BIT;
		  if(me->state  == ON){
			   LED_PORT->ODR |= LED_GREEN_PIN;
				printf("The GREEN Led is set ON \n\r");
			}
			else{
			  LED_PORT->ODR &= ~LED_GREEN_PIN;
        		printf("The GREEN Led is set OFF \n\r");

			}
			break;
	
	}
}

LedState_Type Led_getState(Led_Type * const me){

	//Kontollera färgen av den LED som efterfrågas, printa sedan statusen
	switch(me->color){
		
		case RED: //Om LED är röd.
			   printf("The RED Led is cureently %d \n\r",me->state);
				 break;
	  	case GREEN:
			   printf("The GREEN Led is cureently %d \n\r",me->state);
				 break;
		case BLUE:
			   printf("The BLUE Led is cureently %d\n\r",me->state);
				 break;
		case YELLOW:
			   printf("The YELLOW Led is cureently  %d \n\r",me->state);
				 break;
	 }
  
	return me->state; //Returnerar LED-lampas status av vald färg
}
