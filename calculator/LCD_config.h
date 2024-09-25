/*
 *
 * @file LCD_config.h
 * @author Kareem Hussein
 * @brief configuration header file contain configuraron macros for LCD
 * @date 17/08/2024      
 * @version 1.0
 *
 */
#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

/* Macros For Rs configuration */
#define LCD_RS_PORT         DIO_PORTB
#define LCD_RS_PIN          DIO_PIN1

/* Macros For RW configuration */
#define LCD_RW_PORT         DIO_PORTB
#define LCD_RW_PIN          DIO_PIN2

/* Macros For Enable configuration */
#define LCD_E_PORT          DIO_PORTB
#define LCD_E_PIN           DIO_PIN3

/* 4 Bit Mode Data Pins Configurtion */
#define LCD_D4_PORT         DIO_PORTA
#define LCD_D4_PIN          DIO_PIN4

#define LCD_D5_PORT         DIO_PORTA
#define LCD_D5_PIN          DIO_PIN5

#define LCD_D6_PORT         DIO_PORTA
#define LCD_D6_PIN          DIO_PIN6

#define LCD_D7_PORT         DIO_PORTA
#define LCD_D7_PIN          DIO_PIN7

#endif /* LCD_CONFIG_H_ */
