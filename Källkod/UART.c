#include "UART.h" // Inkludera headerfilen UART med tillhörande källkod.
#include "stm32f4xx.h" //Inkludera bibliotek med tillhörande funktioner och källkod för microkontrollern.
#include <stdio.h>

// Definiera funktion som inte tar några argument för att initiera Usart-protokollet och dess beståndsdelar. Denna funktion utgör en drivrutin.
void USART2_Init(void){ //USART specificerar att vi kan köra asynkront och synkront. 

    // 1. Enablea klocktillgång för UART2
    RCC->APB1ENR  |=  0x20000; // Aktiverar UART2 genom att sätta bit 17 i APB1ENR till 1.
    // 2. Enablea klocktillgång för port A
    RCC->AHB1ENR   |=0x01; // Aktiverar GPIO genom att sätta bit 0 i AHB1ENR till 1.
    // 3. Enablea pins relaterade till vald port, för alternativ funktion= betyder att den konverteras till att den används till. Vanliga funktionen är I/O, men när det gäller UART protokkollet är det inte längre en vanlig utan klassas. Är det vanlig I/O är inte alternativt, är det  
    GPIOA->MODER &=~0x00F0; // Rensar bitarna 4-7 för att förbereda pins PA2 och PA3 ifall dessa är i andra lägen. 
    GPIOA->MODER |= 0x00A0; // Sätter bitarna 5 och 7 till 1 för att aktivera alternativ funtionalitet på pins PA2 och PA3
    // 4. Välja typen av alternativ funktion för de valda pinsen, hakperenteserna syftar till att välja början av AFR-LOW/HIGH
    GPIOA->AFR[0] &= ~0xFF00; // Rensar bitarna 8-15 för att förbereda pins PA2 och PA3.
    GPIOA->AFR[0] |= 0x7700; // Sätter bitarna 8-11 samt 12-14 till formatet 0111
    // Nu är UART konfigurerad och pin 2 och 3 är redo för att överföra med UART-kommunikation.

    // Konfiguration av UART
    USART2->BRR  =  0x0683; // Sätter baud-rate med hjälp av hexadecimalen 0x0683 till standard, 9600bps
    USART2->CR1  =  0x000C; // Sätter transmit och receive till att arbeta i 8 bitars data. (8 bitars data, 1 stop bit, ingen paritet)
    USART2->CR2  =  0x000; // Nollställer CR2
    USART2->CR3  =  0x000; // Nollställer CR3
    USART2->CR1  |=  0x2000; // Omställer bit 13 (Uart-aktiveringen) till 1
}
// UART Write-regler
int USART2_write(int ch){ // Deklarerar skrivfunktionen (Överföringen av data till terminalen)
    //En loop för att skicka byte för byte
	while(!(USART2->SR & 0x0080)){} // Krav som kontrollerar att statusen på överföringsdataregistret (bit 7) är tom och kan ta emot nästa byte.
	USART2->DR = (ch & 0xFF); // Sätter överföringen av byten till dataregistret
	
  return ch;
}
//UART Read-regler
int USART2_read(void){ // Deklarerar läsfunktionen (mottagning av information)
  while(!(USART2->SR & 0x0020)){} // Sätter ett krav som kontrollerar om det finns mer data att hämta
	return USART2->DR; // Returnerar och läser ut datan
}
// Interface för standard I/O i C
// En omdiregering till att utge datan i terminalen, alltså den data som förs över. 
struct __FILE {int handle; }; // Strukturerar våra huvudsakliga överföringsströmmar
FILE __stdin  = {0};
FILE __stdout = {1};
FILE __stderr = {2};

//Funktion för att läsa en byte från standardinmatningen.
int fgetc(FILE *f) { // fget hämtar en byte från standardströmmen och behandlar även teckenreturer
    int c;

    c = USART2_read();     

    if (c == '\r') {        
        USART2_write(c);    
        c = '\n';
    }

    USART2_write(c);       

    return c;
}
//Funktion för att skriva ut till terminalen.
int fputc(int c, FILE *f) { // fput skriver en byte till standardströmmen
    return USART2_write(c);
}


int n; // Deklarerar en byte för användning i testfunktionen.
char str[80]; // Sätter en begränsningn av antal karaktärer i överföringen.

// Funktion som testar läs- och skrivfunktionen.	
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
