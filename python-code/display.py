import I2C_LCD_driver
import socket
import fcntl
import struct
from time import *

mylcd = I2C_LCD_driver.lcd()
mylcd.lcd_display_string("Hello world", 1)
mylcd.lcd_display_string("Hello world", 2)


#### Position
# mylcd.lcd_display_string("Hello World!", 2, 3)


#### CLEAR SCREEN
# mylcd.lcd_display_string("This is how you", 1)
# sleep(1)
# mylcd.lcd_clear()
# mylcd.lcd_display_string("clear the screen", 1)
# sleep(1)
# mylcd.lcd_clear()


#### Blink text
# while True:
#     mylcd.lcd_display_string(u"Hello world!")
#     time.sleep(1)
#     mylcd.lcd_clear()
#     time.sleep(1)


#### Print datetime
# while True:
#     mylcd.lcd_display_string("Time: %s" %time.strftime("%H:%M:%S"), 1)    
#     mylcd.lcd_display_string("Date: %s" %time.strftime("%m/%d/%Y"), 2)


#### Print IP address
# def get_ip_address(ifname):
#     s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     return socket.inet_ntoa(fcntl.ioctl(
#         s.fileno(),
#         0x8915, 
#         struct.pack('256s', ifname[:15])
#     )[20:24])
#
# mylcd.lcd_display_string("IP Address:", 1) 
# mylcd.lcd_display_string(get_ip_address('eth0'), 2)


#### String scroll right to left
# str_pad = " " * 16
# my_long_string = "This is a string that needs to scroll"
# my_long_string = str_pad + my_long_string

# while True:
#     for i in range (0, len(my_long_string)):
#         lcd_text = my_long_string[i:(i+16)]
#         mylcd.lcd_display_string(lcd_text,1)
#         sleep(0.4)
#         mylcd.lcd_display_string(str_pad,1)



#Programa: Display LCD I2C com Raspberry Pi
#Autor: Arduino e Cia

# import I2C_LCD_driver
# import socket
# import fcntl
# import struct
# import time

# lcdi2c = I2C_LCD_driver.lcd()

# #Exibe informacoes iniciais
# lcdi2c.lcd_display_string("Arduino e Cia", 1,1)
# lcdi2c.lcd_display_string("LCD I2C e RPi", 2,1)
# time.sleep(4)

# #Apaga o display
# lcdi2c.lcd_clear()

# def get_ip_address(ifname):
#     s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     return socket.inet_ntoa(fcntl.ioctl(
#         s.fileno(),
#         0x8915, 
#         struct.pack('256s', ifname[:15])
#     )[20:24])

# #Mostra o endereco IP
# lcdi2c.lcd_display_string("IP", 1)
# lcdi2c.lcd_display_string(get_ip_address('wlan0'), 1,3)
 
# while True:
# #Mostra a data no display
#     lcdi2c.lcd_display_string("Data: %s" %time.strftime("%d/%m/%y"), 2,1)
