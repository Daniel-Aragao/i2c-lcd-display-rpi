/*
** @file LCD_I2C.c
** @version 01.00
** @brief
**         This is the driver for the LCD through I2C interface.
*/         
/*!
**  @addtogroup LCD_module LCD module documentation
**  @{
*/         
/* MODULE LCD */



#include<linux/i2c.h>
#include<linux/i2c-dev.h>

#include "LCD_I2C.h"
#include <stdbool.h>
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>


/* User includes (#include below this line is not maintained by Processor Expert) */
#define LCD_MAX_LINE_LENGTH (16) 

#define LCD_ADDRESS (0x27) 

#define LCD_BK_LIT (3)  // Enable bit
#define LCD_EN     (2)  // Enable bit
#define LCD_RW     (1)  // Read/Write bit
#define LCD_RS     (0)  // Register select bit

//   LCD dataline allocation this library only supports 4 bit LCD control
//   D4, D5, D6, D7 LCD data lines pin mapping of the extender module
#define D4 4
#define D5 5
#define D6 6
#define D7 7

#define CONFIG_4BIT_MODE          (0x28) // => 4-bit mode, 2 lines, 5x7 character   
#define CONFIG_8BIT_MODE          (0x38) // => 8-bit mode, 2 lines, 5x7 character   
#define CONFIG_RIGHT_SHIFT_CURSOR (0x06) // => right-shift cursor, don't shift message
#define CONFIG_LCD_ON_NO_CURSOR   (0x0C) // => Turn LCD on, Cursor off, no blink
#define CLR_LCD_HOME_POSITION     (0x01) // => Clear display and go to home position

#define LCD_DATA_MODE    (1 << LCD_RS)    // => LCD data mode
#define LCD_COMMAND_MODE (~LCD_DATA_MODE) // => LCD command mode
#define BUF_LEN (1)

//  Send 0x02 => Go to home position, reset message scroll


uint8_t LCD_control;
bool LCD_Backlight = false;
int file;

void GI2C1_WriteByte(uint8_t data)
{	
	
	char writeBuffer[BUF_LEN];
	
	writeBuffer[0] = data;

	if(write(file, writeBuffer, BUF_LEN) != BUF_LEN) {
		perror("Failed to write to LCD\n");
	}
}

/*
** ===================================================================
**     Method       :  LCD_Send4bit (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method sends one nibble to the alphanumeric LCD through
**         the adapter with I2C interface. 
**		   Only upper nibble of parameter will be sent.
**		   The byte sent through I2C will be mapped to the LCD as follows:
**		   Bit 0 - LCD_RS		// Register select bit
**		   Bit 1 - LCD_RW	    // Read/Write bit
**		   Bit 2 - LCD_EN       // LCD enable bit
**		   Bit 3 - LCD_BK_LIT   // Turn backlight on
**		   
**		   Bit 4 - LCD_D4
**		   Bit 5 - LCD_D5
**		   Bit 6 - LCD_D6
**		   Bit 7 - LCD_D7
**		   
**     @param
**         data     - value whose upper nibble will be sent to the LCD.
**                    Lower nibble will be composed with LCD_control bits
*/          
/* ===================================================================*/
void LCD_Send4bit(uint8_t data)
{
    uint8_t aux;
    
    aux = (data & 0xF0) | LCD_control; 
//    GI2C1_WriteByte(LCD_ADDRESS, aux);
//	WAIT2_Waitus(40);
	
	aux |= (1 << LCD_EN);
	GI2C1_WriteByte(aux);
//	WAIT2_Waitus(40);
	usleep(40);
	
	aux &= ~(1 << LCD_EN);
	GI2C1_WriteByte(aux);
//	WAIT2_Waitus(40);
	usleep(40);
}
	
/*
** ===================================================================
**     Method       :  LCD_SendCommand (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method sends one byte of command to the LCD
**		   
**     @param
**         command  - value to be sent as a command to the LCD.
*/          
/* ===================================================================*/
 void LCD_SendCommand(uint8_t command)
{
	LCD_control &= LCD_COMMAND_MODE; // Set RS to zero 
	LCD_Send4bit(command); 
	LCD_Send4bit(command << 4); 
}	


/*
** ===================================================================
**     Method       :  LCD_SendData (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method sends one byte of data to the LCD
**		   
**     @param
**         data  - value to be sent as a data to the LCD.
*/          
/* ===================================================================*/
void LCD_SendData(uint8_t data)
{
	LCD_control |= LCD_DATA_MODE; // Set RS to 1 
	LCD_Send4bit(data); 
	LCD_Send4bit(data << 4); 
}	

/*
** ===================================================================
**     Method       :  LCD_TurnOnBacklight (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method Turns on the backlight of the LCD
**		   
**     @param
**         none.
*/          
/* ===================================================================*/
void LCD_TurnOnBacklight (void)
{
	LCD_control |= (1 << LCD_BK_LIT); 
    GI2C1_WriteByte(LCD_control);
//	WAIT2_Waitus(40);
	usleep(40);
}

/*
** ===================================================================
**     Method       :  LCD_TurnOffBacklight (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method Turns off the backlight of the LCD
**		   
**     @param
**         none.
*/          
/* ===================================================================*/
void LCD_TurnOffBacklight (void)
{
	LCD_control &= ~(1 << LCD_BK_LIT); 
    GI2C1_WriteByte(LCD_control);
//	WAIT2_Waitus(40);
	usleep(40);
}

/*
** ===================================================================
**     Method       :  LCD_SetCursor (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method sends the parameter as a command to the LCD
**		   
**     @param
**         addr  - value to be sent as a command to the LCD.
*/          
/* ===================================================================*/
void LCD_SetCursor(uint8_t addr)
{
	LCD_SendCommand(addr); 
}

/*
** ===================================================================
**     Method       :  LCD_Clear (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method clears the LCD screen and sets cursor to home position. 
**		   
**     @param
**         none.
*/          
/* ===================================================================*/
void LCD_Clear(void)
{
	LCD_SendCommand(CLR_LCD_HOME_POSITION); 
}

/*
** ===================================================================
**     Method       :  LCD_SendString (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method sends one null-terminated string to the LCD
**		   
**     @param
**         *pString  - char pointer to the null-terminated string.
*/          
/* ===================================================================*/
void LCD_SendString(char *pString)
{
	uint8_t count = 0;
	while ( (*pString != 0) && (count++ < LCD_MAX_LINE_LENGTH) )
	{
		LCD_SendData(*pString++);
	}  
}	


/*
** ===================================================================
**     Method       :  LCD_Init (module LCD)
**
**     Component   :  LCD through I2C
*/
/*!
**     @brief
**         This method initializes LCD to the following configurations:
**         Send 0x28 => 4-bit mode, 2 lines, 5x7 character   
**         Send 0x06 => right-shift cursor, don't shift message
**         Send 0x0C => Turn LCD on, Cursor off, no blink
**         Send 0x01 => Clear display and go to home position
**         Send 0x02 => Go to home position, reset message scroll
**		   
**     @param
**         backLight  - TRUE if backlight must be turned on.
*/          
/* ===================================================================*/
void LCD_Init(bool backLight)
{
	if((file=open("/dev/i2c-1", O_RDWR)) < 0) {
		perror("FAILED TO OPEN THE BUS \n");
	}

	if(ioctl(file, I2C_SLAVE, LCD_ADDRESS) < 0 ) {
		perror("Failed to connect to the sensor\n");
	}
	LCD_control = 0;
	if (backLight)
		LCD_control |= (1 << LCD_BK_LIT); 

//	WAIT2_Waitms(50);
    usleep(50 * 1000);
	LCD_Send4bit(CONFIG_4BIT_MODE); // send upper nibble only
//	LCD_Send4bit(CONFIG_4BIT_MODE); // send upper nibble only
//	WAIT2_Waitms(50);
	usleep(50 * 1000);
	LCD_SendCommand(CONFIG_4BIT_MODE); 
//	LCD_SendCommand(CONFIG_4BIT_MODE); 
//	WAIT2_Waitms(50);
	usleep(50 * 1000);
	LCD_SendCommand(CONFIG_RIGHT_SHIFT_CURSOR); 
	LCD_SendCommand(CONFIG_LCD_ON_NO_CURSOR); 
	LCD_SendCommand(CLR_LCD_HOME_POSITION);
//	WAIT2_Waitms(10);
	usleep(10 * 1000);
}	
void LCD_End()
{
	close(file);
}
/* END LCD */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
**  @}
*/ 
