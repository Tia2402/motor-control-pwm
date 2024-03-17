#include <xc.h>
#define _XTAL_FREQ 4000000
#define ADC_MAX  1023
void initPWM1ms ()
{
      PR2 = 61; //  perioada PWM 1ms
      T2CON = 0b00000111; //prescaler de 16
      CCP1CON = 0b00001100;    //config ccp1 ca pwm 
}

void initPWM2_5ms()
{
      PR2 = 155; // pr2 155 si prescaler de 16 =>pwm = 2.5ms
      T2CON = 0b00000111; //prescaler de 16
      CCP1CON = 0b00001100;    //config ccp1 ca pwm 
}

unsigned char map(unsigned int value)
{
    return (unsigned char)((value * PR2) / ADC_MAX );   //conversie pentru ca valoarea sa fie intre 0 si PR2
}

void main(void)
 {
   TRISA  = 1; //porta intrare pentru potentiometru
   TRISC  = 0;  //portc iesire pentru rotatie motor
   TRISB  = 1;  //portb intrare pentru buton
   ADCON0 = 0b10000001; //10 freq osc, 0000-caanal0(AN0), 01-final conversie si activare modul adcon 
   initPWM1ms ();
    
   while (1)
   {	
      GO_DONE  = 1; //incepere conversie 
      while(GO_DONE );
      CCPR1L = map(ADRESH);
      if(RB0 == 0) // daca butonul este apasat 
      {
	    __delay_ms(50); //debounce
	    if(RB0 == 0)
	    {
	       if(PR2 == 62)
		  initPWM2_5ms();
	       else
		  initPWM1ms ();
		while(RB0 == 0);
	    }
	}
   }
 }
