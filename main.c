/*
 * Mariam Mohamed Fouad Zaky
 * 20211095
 * Training at: ITI
 * Track: IoT
 * Supervisor: Dr.Mohamed Youssef
 * Project: Calculator
 *
 */


#include "LIB/BIT_MATH.h"
#include "LIB/STD_TYPES.h"
#include "MCAL/DIO/DIO_Interface.h"
#include "HAL/LCD/LCD_Interface.h"
#include "HAL/KPAD/KPAD_Interface.h"
#include <util/delay.h>

void Calculator();

int main()
{
	LCD_VoidInit();
	KPAD_voidInit();

    while(1)
    {
        Calculator();
    }
    return 0;
}


void Calculator() {
    u8 key;
    s32 num1 = 0, num2 = 0, result = 0;
    u8 operation = 0;
    u8 step = 0;

    LCD_VoidClear();
    LCD_VoidWriteString(" Num1: ");

    while (1) {

        key = KPAD_u8GetPressedKey();
      if(key != 'R')
      {
        if (key != 0xff) { // a button is pressed
            if (key >= '0' && key <= '9') {
                if (step == 0) {
                    num1 = num1 * 10 + (key - '0');
                    LCD_VoidWriteData(key);
                } else if (step == 1) {
                    num2 = num2 * 10 + (key - '0');
                    LCD_VoidWriteData(key);
                }
            } else if (key == '+' || key == '-' || key == '*' || key == '/') {
                if (step == 0) {
                    operation = key;
                    step = 1;
                    LCD_VoidClear();
                    LCD_VoidWriteString(" Num2:");
                }
            } else if (key == '=') {
                if (step == 1) {
                    switch (operation) {
                        case '+': result = num1 + num2; break;
                        case '-': result = num1 - num2; break;
                        case '*': result = num1 * num2; break;
                        case '/':
                        	if(num2 != 0)
                        	{
                        		result = num1 / num2; break;
                        	}
                        	else
                        	{
                        		LCD_VoidClear();
                        		LCD_VoidWriteString(" Error: Div by 0");
                        		_delay_ms(1000);
                        		LCD_VoidClear();
                        		LCD_VoidWriteString(" Try again");
                        		_delay_ms(700);
                        		return;
                        	}
                    }
                    LCD_VoidClear();
                    LCD_VoidWriteString(" Result ");
                    LCD_VoidWriteNumber(result);
                    _delay_ms(100);

                }
            }
        }
      }
      else
      {
    	  break;
      }
    }
}
