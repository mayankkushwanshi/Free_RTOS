#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core

#define GREEN  GPIO_PIN_12
#define ORANGE GPIO_PIN_13
#define RED    GPIO_PIN_14
#define BLUE   GPIO_PIN_15

void GPIO_Init(void);
void  vLedControllerTask(void *pvParameters);

const uint16_t *blueLed = (uint16_t*)BLUE;
const uint16_t *redLed = (uint16_t*)RED;
const uint16_t *greenLed = (uint16_t*)GREEN;
const uint16_t *orangeLed = (uint16_t*)ORANGE;

int main()
{
	 GPIO_Init();
	
	 xTaskCreate(vLedControllerTask,
							 "Blue Led Controller",
								100,
								(void *)blueLed,
								1,
								NULL
								);
	 xTaskCreate(vLedControllerTask,
							 "Red Led Controller",
								100,
								(void *)redLed,
								1,
								NULL
								);
	 xTaskCreate(vLedControllerTask,
							 "Green Led Controller",
								100,
								(void *)greenLed,
								1,
								NULL
								);
	 xTaskCreate(vLedControllerTask,
							 "Orange Led Controller",
								100,
								(void *)orangeLed,
								1,
								NULL
								);

   vTaskStartScheduler();
	 
	 while(1){};
}



void  vLedControllerTask(void *pvParameters)
{
	int i;
	while(1)
	{
		HAL_GPIO_TogglePin(GPIOD,(uint16_t)pvParameters);
		for(i=0;i<600000;i++){}
	}
}


void GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct;

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOD, GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15, GPIO_PIN_RESET);

  /*Configure GPIO pins : PD12 PD13 PD14 PD15 */
  GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);	
}

