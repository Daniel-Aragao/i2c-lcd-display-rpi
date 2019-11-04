/*!
** @file Events.h
** @version 01.00
** @brief
**         This is user's event module.
**         Put your event handler code here.
*/         
/*!
**  @addtogroup Events_module Events module documentation
**  @{
*/         


#ifndef __LCD_H
#define __LCD_H


#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#include <stdbool.h>
#include <stdint.h>

/* MODULE LCD */


void LCD_TurnOnBacklight (void);
void LCD_TurnOffBacklight (void);
void LCD_SetCursor(uint8_t addr);
void LCD_Clear(void);
void LCD_SendString(char *pString);
void LCD_Init(bool backLight);
void LCD_End();


/* END LCD */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

#endif 
/* ifndef __LCD_H*/
/*!
** @}
*/
