#include "stm8s.h"

#define SECOND		1900
#define TEN_SECONDS	19000
#define FLASH_DELAY	38

uint8_t alarm = 0;

void delay(uint16_t ms)
{
	for (uint16_t i = 0; i <= ms; i++) {
		for (uint16_t j = 0; j < 120; j++);
	}
}

void main(void) 
{
	// Init LED Port, Pin
	GPIO_Init(GPIOD, GPIO_PIN_4, GPIO_MODE_OUT_PP_LOW_FAST);
	// EEPROM init / de-initialize flash registers
	FLASH_DeInit();

	alarm = FLASH_ReadByte(0x4000);
	delay(FLASH_DELAY);

	GPIO_WriteLow(GPIOD, GPIO_PIN_4);
	delay(SECOND);

	if (alarm) {
		FLASH_Unlock(FLASH_MEMTYPE_DATA);
		FLASH_EraseByte(0x4000);
		delay(FLASH_DELAY);
		FLASH_ProgramByte(0x4000, 0x0);
		delay(FLASH_DELAY);
		FLASH_Lock(FLASH_MEMTYPE_DATA);
		GPIO_WriteHigh(GPIOD, GPIO_PIN_4);
	}
}

