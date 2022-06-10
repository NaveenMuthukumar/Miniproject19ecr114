#include <16F877A.h>
#device ADC=10

#FUSES NOWDT                    //No Watch Dog Timer
#FUSES NOPUT                      //Power Up Timer
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#fuses HS

#use delay(crystal=8000000)

#define LCD_ENABLE_PIN PIN_D2
#define LCD_RS_PIN PIN_D0
#define LCD_RW_PIN PIN_D1
#define LCD_DATA4 PIN_D4
#define LCD_DATA5 PIN_D5
#define LCD_DATA6 PIN_D6
#define LCD_DATA7 PIN_D7

#include <lcd.c>
char temperature[] = " 00.0 C ";
unsigned int16 temp;

void main(){
  
  setup_adc(ADC_CLOCK_INTERNAL);                 // ADC Module uses its internal oscillator
  setup_adc_ports(AN0);                          // Configure AN0 pin as analog
  set_adc_channel(0);                            // Select channel 0 (AN0)
 
  lcd_init();                                    // Initialize LCD module
  lcd_putc('\f');                                // Clear LCD
  lcd_gotoxy(3, 1);                              // Go to column 3 row 1
  printf(lcd_putc, "Temperature");

  while(TRUE){
   
    delay_ms(1000);
    temp = read_adc() * 0.489;                   // Read analog voltage and convert it to degree celsius (0.489 = 500/1023)
    
    if (temp > 99)
       temperature[0]  = 1 + 48;                  // Put 1 (of hundred)
    else
       temperature[0]  = ' ';                     // Put space
       temperature[1]  = (temp / 10) % 10  + 48;
       temperature[2]  =  temp % 10  + 48;
       temperature[5] = 223;                        // Degree symbol
       lcd_gotoxy(5, 2);                            // Go to column 5 row 2
       printf(lcd_putc,temperature );               // Display LM35 temperature result
  }
}
