@echo off
setlocal enabledelayedexpansion

echo Starte STM32 Flash-Programm...

echo.
echo *** Taste druecken fuer die LED Blink Demo ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\LED_BLINK\Debug\LED_BLINK.elf
echo ** AKTUELLES PROGRAMM: .\Software\LED_BLINK\Debug\LED_BLINK.elf **
pause

echo.
echo *** Taste druecken fuer die Relai Blink Demo ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\RELAI_BLINK\Debug\RELAI_BLINK.elf
echo ** AKTUELLES PROGRAMM: .\Software\RELAI_BLINK\Debug\RELAI_BLINK.elf **
pause

echo.
echo *** Taste druecken fuer den GPIO Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\GPIO_TEST\Debug\GPIO_TEST.elf
echo ** AKTUELLES PROGRAMM: .\Software\GPIO_TEST\Debug\GPIO_TEST.elf **
pause

echo.
echo *** Taste druecken fuer den PWM Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\PWM_TEST\Debug\PWM_TEST.elf
echo ** AKTUELLES PROGRAMM: .\Software\PWM_TEST\Debug\PWM_TEST.elf **
pause

echo.
echo *** Taste druecken fuer den Encoder Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\ENC_TEST\Debug\ENC_TEST.elf
echo ** AKTUELLES PROGRAMM: .\Software\ENC_TEST\Debug\ENC_TEST.elf **
pause

echo.
echo *** Taste druecken fuer den I2C BMP280 Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\I2C_BMP280\Debug\I2C_BMP280.elf
echo ** AKTUELLES PROGRAMM: .\Software\I2C_BMP280\Debug\I2C_BMP280.elf **

echo.
echo *** Taste druecken fuer UART oeffnen ***
pause
putty -serial COM4 -sercfg 9600,8,n,1,N
pause

echo.
echo *** Taste druecken fuer den SPI Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\SPI_TEST\Debug\SPI_TEST.elf
echo ** AKTUELLES PROGRAMM: .\Software\SPI_TEST\Debug\SPI_TEST.elf **
pause

echo.
echo *** Taste druecken fuer den DAC/ADC Test ***
pause
STM32_Programmer_CLI -c port=USB1 -d .\Software\DAC_ADC_TEST\Debug\DAC_ADC_TEST.elf
echo ** AKTUELLES PROGRAMM: .\Software\DAC_ADC_TEST\Debug\DAC_ADC_TEST.elf **
pause

echo.
echo *** Alle Flash-Vorgaenge abgeschlossen! ***
pause
