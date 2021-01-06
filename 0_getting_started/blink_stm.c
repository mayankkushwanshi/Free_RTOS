#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#define GREEN GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED GPIO_PIN_14
#define BLUE GPIO_PIN_15
 
void GPIO_Init(void); 

int main()
{
	int i;
	GPIO_Init();
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD, GREEN | ORANGE | RED | BLUE );
		for(i=0;i<500000;i++){}
	}
}

void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	//clock initialize
	__HAL_RCC_GPIOH_CLK_ENABLE();
	__HAL_RCC_GPIOD_CLK_ENABLE();
	HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15, GPIO_PIN_RESET);
	//configration of all pins
	GPIO_InitStruct.Pin = GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14 | GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);
	
}

