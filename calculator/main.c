/*
 * GccApplication3.c
 *
 * Created: 9/5/2024 11:02:30 AM
 * Author : Mohamed_Salama
 */ 

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "KPD_interface.h"

u8 operation = 0;
u8 num1 = 0, num2 = 0, result = 0;

int main(void) {
	LCD_voidInit();
	KPD_voidInit();

	while (1) {
		u8 key;
		KPD_voidGetValue(&key);

		if (key != KPD_NOT_PRESSED) {
			if (key >= '0' && key <= '9') {
				// Handle digit input
				if (operation == 0) {
					num1 = (num1 * 10) + (key - '0');
					LCD_voidDisplayChar(key);
					} else {
					num2 = (num2 * 10) + (key - '0');
					LCD_voidDisplayChar(key);
				}
				} else if (key == '+' || key == '-' || key == '*' || key == '/') {
				// Handle operation input
				operation = key;
				LCD_voidDisplayChar(key);
				} else if (key == '=') {
				// Handle calculation
				switch (operation) {
					case '+': result = num1 + num2; break;
					case '-': result = num1 - num2; break;
					case '*': result = num1 * num2; break;
					case '/': result = (num2 != 0) ? num1 / num2 : 0; break;
				}
				LCD_voidClear();
				LCD_voidDisplayNumber(result);
				} else if (key == 'C') {
				// Handle clear
				num1 = num2 = result = operation = 0;
				LCD_voidClear();
			}
		}
	}
}
