//
// Created by Fan Jiang on 14/03/2018.
//

#include "bsp/display.h"
#include <cmsis_os.h>
#include <fsmc.h>

osThreadId displayTaskHandle;

LCD* lcd1;

void StartDisplayTask(void const *argument){

  lcd1 = new LCD();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  auto volatile state = HAL_SRAM_GetState(&hsram1);

  volatile uint16_t lcdid = 0;
  while(true){
    lcdid = lcd1->ReadReg(0x00);
    state = HAL_SRAM_GetState(&hsram1);
    HAL_GPIO_TogglePin(GPIO_LED_GPIO_Port, GPIO_LED_Pin);

    osDelay(500);
  }
}

uint16_t LCD::ReadReg(uint16_t addr) {
  _lcd->LCD_REG=addr;
  return (_lcd->LCD_RAM);
}

void LCD::WriteReg(uint16_t addr, uint16_t data) {
  _lcd->LCD_REG=addr;
  _lcd->LCD_RAM=data;
}
