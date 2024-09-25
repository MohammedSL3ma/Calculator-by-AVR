/*
 *
 * @file LCD_program.c
 * @author Kareem Hussein
 * @brief main source for LCD functions implementation
 * @date 17/08/2024      
 * @version 1.0
 *
 */

#define F_CPU 16000000UL
#include <util/delay.h>
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "LCD_interface.h"
#include "LCD_config.h"
#include "LCD_private.h"

void LCD_voidInit(void) {
	DIO_voidSetPinDirection(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_E_PORT, LCD_E_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D4_PORT, LCD_D4_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D5_PORT, LCD_D5_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D6_PORT, LCD_D6_PIN, DIO_PIN_OUTPUT);
	DIO_voidSetPinDirection(LCD_D7_PORT, LCD_D7_PIN, DIO_PIN_OUTPUT);

	_delay_ms(35);
	LCD_voidSendCommand(0x02); // 4-bit mode
	LCD_voidSendCommand(0x28); // 2 lines, 5x7 font
	LCD_voidSendCommand(0x0C); // Display ON, Cursor OFF
	LCD_voidSendCommand(0x06); // Increment cursor
	LCD_voidClear();           // Clear display
}

void LCD_voidDisplayChar(u8 copy_u8Data) {
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_HIGH);
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	PRV_voidWriteHalfPort(copy_u8Data >> 4);
	PRV_voidEnableTriggerWrite();
	PRV_voidWriteHalfPort(copy_u8Data);
	PRV_voidEnableTriggerWrite();
}

void LCD_voidSendCommand(u8 copy_u8cmnd) {
	DIO_voidSetPinValue(LCD_RS_PORT, LCD_RS_PIN, DIO_PIN_LOW);
	DIO_voidSetPinValue(LCD_RW_PORT, LCD_RW_PIN, DIO_PIN_LOW);
	PRV_voidWriteHalfPort(copy_u8cmnd >> 4);
	PRV_voidEnableTriggerWrite();
	PRV_voidWriteHalfPort(copy_u8cmnd);
	PRV_voidEnableTriggerWrite();
}

void LCD_voidDisplayString(u8* copy_Pu8String) {
	while (*copy_Pu8String) {
		LCD_voidDisplayChar(*copy_Pu8String++);
	}
}

void LCD_voidClear(void) {
	LCD_voidSendCommand(0x01);
	_delay_ms(2);
}

void LCD_voidDisplayNumber(u32 copy_u32Number) {
	if (copy_u32Number == 0) {
		LCD_voidDisplayChar('0');
		return;
	}

	u8 digits[10];
	u8 i = 0;

	while (copy_u32Number) {
		digits[i++] = (copy_u32Number % 10) + '0';
		copy_u32Number /= 10;
	}

	while (i) {
		LCD_voidDisplayChar(digits[--i]);
	}
}

void LCD_voidGoToSpecificPosition(u8 copy_u8LineNumber, u8 copy_u8Position) {
	u8 address = (copy_u8LineNumber == LCD_LINE_ONE) ? 0x80 : 0xC0;
	address += copy_u8Position;
	LCD_voidSendCommand(address);
}

static void PRV_voidWriteHalfPort(u8 copy_u8Value) {
	DIO_voidSetPinValue(LCD_D4_PORT, LCD_D4_PIN, GET_BIT(copy_u8Value, 0));
	DIO_voidSetPinValue(LCD_D5_PORT, LCD_D5_PIN, GET_BIT(copy_u8Value, 1));
	DIO_voidSetPinValue(LCD_D6_PORT, LCD_D6_PIN, GET_BIT(copy_u8Value, 2));
	DIO_voidSetPinValue(LCD_D7_PORT, LCD_D7_PIN, GET_BIT(copy_u8Value, 3));
}

static void PRV_voidEnableTriggerWrite(void) {
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(LCD_E_PORT, LCD_E_PIN, DIO_PIN_LOW);
}
