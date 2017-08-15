#include "C:\Users\Ali\Desktop\PIC16F877 Calculator Code\code_finale\code_finale.h"
#define use_portb_kbd
#include <lcd.c>
#include <kbd.c>
#include <stdlib.h>
char key;           
int num1 = 0;      
char func = '+';    
int num2 = 0; 
char c11,c22;
int error;

disp_num(int numb)            //displays number on LCD
{   
   unsigned char UnitDigit  = 0;  //It will contain unit digit of numb
   unsigned char TenthDigit = 0;  //It will contain 10th position digit of numb

   if(numb<0)
   {
      numb = -1*numb;          // Make number positive
      lcd_putc('-');    // Display a negative sign on LCD
   }

   TenthDigit = (numb/10);                     // Findout Tenth Digit

   if( TenthDigit != 0)                     // If it is zero, then don't display
      lcd_putc(TenthDigit+0x30);     // Make Char of TenthDigit and then display it on LCD

   UnitDigit = numb - TenthDigit*10;

   lcd_putc(UnitDigit+0x30);     // Make Char of UnitDigit and then display it on LCD
}

DispError(int numb)           //displays differet error messages
{
   lcd_init();              //clear display
   switch(numb)
   {
   case 0:    lcd_putc("Wrong Input");break;
   case 1:    lcd_putc("Wrong Function");break;
   default:    lcd_putc("Wrong Input");break;
   }
}
int get_num(char ch)         //convert char into int
{
   int num = 0;

   switch(ch)
   {
      case '0': num = 0; break;
      case '1': num = 1; break;
      case '2': num = 2; break;
      case '3': num = 3; break;
      case '4': num = 4; break;
      case '5': num = 5; break;
      case '6': num = 6; break;
      case '7': num = 7; break;
      case '8': num = 8; break;
      case '9': num = 9; break;
      case 'C': lcd_init(); num = Error; break;  //this is used as a clear screen and then reset by setting error
      default: DispError(0); num = Error; break;       //it means wrong input
   }
   return num;
}

char get_func(char chf)            //detects the errors in inputted function
{
   if(chf=='C')                   //if clear screen then clear the LCD and reset
   { 
      lcd_init();          //clear display
      return 'e'; 
   }
   
   if( chf!='+' && chf!='-' && chf!='x' && chf!='/' )  //if input is not from allowed funtions then show error
   { 
      DispError(1); 
      return 'e'; 
   }

   return chf;                        //function is correct so return the correct function
}

void main()
{   
   char key;           // Key char for keeping record of pressed key
   int num1 = 0;       // First number
   char func = '+';    // Function to be performed among two numbers
   int num2 = 0;       // Second number

   kbd_init();       // Initialize Keypad
   lcd_init();         // Initialize LCD

   while(1)
   { 
     //get numb1
     key = kbd_getc();
     lcd_init();          // Clear LCD screen 
    lcd_putc(key);       // Echo the key pressed to LCD
    num1 = get_num(key);       // Get int number from char value, it checks for wrong input as well
     
    if(num1!=Error)            // If correct input then proceed, num1==Error means wrong input
    {
       //get function
       key = kbd_getc();
       lcd_putc(key);             //Echo the key pressed to LCD
       func = get_func(key);            //it checks for wrong func
       
       if(func!='e')                    //if correct input then proceed, func=='e' means wrong input
       {
          //get numb2
          key = kbd_getc();
          lcd_putc(key);         //Echo the key pressed to LCD
          num2 = get_num(key);         //Get int number from char value, it checks for wrong input as well
          
          if(num2!=Error)              //if correct input then proceed, num2==Error means wrong input
          {
             //get equal sign
             key = kbd_getc();
             lcd_putc(key);     //Echo the key pressed to LCD
             
             if(key == '=')           //if = is pressed then proceed
             {
                switch(func)         //switch on function
                {
                case '+': disp_num(num1+num2); break;
                case '-': disp_num(num1-num2); break;
                case 'x': disp_num(num1*num2); break;
                case '/': disp_num(num1/num2); break;
                }
             }
             else                  //key other then = here means error wrong input
             { 
                if(key == 'C')       //if clear screen is pressed then clear screen and reset
                  lcd_init(); // Clear LCD screen 
                else
                  DispError(0);      //Display wrong input error
             }                                 
          }
       }
     }
   }
}

