/*!
** @file main.c
** @version 01.01
** @brief
**         Main module.
**         This module contains user's application code.
*/         
/*!
**  @addtogroup main_module main module documentation
**  @{
*/         
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "LCD_I2C.h"

int main(void)
{
  LCD_Init(true);  // Backlight off
  LCD_SendString("Texto da linha 1");
  LCD_SetCursor(0xC0);
  LCD_SendString("Texto da linha 2");
  LCD_End();
} 

/* END main */
