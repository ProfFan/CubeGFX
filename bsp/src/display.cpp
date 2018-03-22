//
// Created by Fan Jiang on 14/03/2018.
//

#include "bsp/display.h"
#include <cmsis_os.h>
#include <bsp/bsp_can.h>
#include "gfx.h"
#include "gui.h"
#include "bsp/serial.h"

osThreadId displayTaskHandle;

LCD* lcd1;

char printf_buf[255];

void StartDisplayTask(void const *argument){

  lcd1 = new LCD();

  HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);

  lcd1->Init();

  lcd1->Clear(0x001F);

  gfxInit();

  geventListenerInit(&glistener);
  gwinAttachListener(&glistener);

  guiCreate();

  uint32_t lastTick;

  lastTick = HAL_GetTick();

  GEvent* pe;

  while(true){

    if((HAL_GetTick() - lastTick) > 1000){
      lastTick = HAL_GetTick();

      gwinPrintf(ghConsole1, "[%u] CAN ERR: %d\n\r", lastTick , can1->errorCount);
      gwinPrintf(ghConsole1, "[%u] CAN PKT: %d\n\r", lastTick , can1->recvCount);
    }


    pe = geventEventWait(&glistener, 0);
    switch (pe->type) {

    }
//    HAL_GPIO_TogglePin(GPIO_LED_GPIO_Port, GPIO_LED_Pin);

//    snprintf(printf_buf, sizeof(printf_buf), "%u", PMSData.pm2_5_atm);

    osDelay(4);
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

void LCD::Init() {
  id = lcd1->ReadReg(0x00);

  if(id == 0x9328)
  {
    WriteReg(0x00,0x0001);
    WriteReg(0x01,0x0100);
    WriteReg(0x02,0x0700);
    WriteReg(0x03,0x1018);
    WriteReg(0x04,0x0000);
    WriteReg(0x08,0x0202);
    WriteReg(0x09,0x0000);
    WriteReg(0x0A,0x0000);
    WriteReg(0x0C,0x0000);
    WriteReg(0x0D,0x0000);
    WriteReg(0x0F,0x0000);
    WriteReg(0x10,0x0000);
    WriteReg(0x11,0x0000);
    WriteReg(0x12,0x0000);
    WriteReg(0x13,0x0000);
    osDelay(20);
    WriteReg(0x10,0x17B0);
    WriteReg(0x11,0x0137);
    osDelay(5);
    WriteReg(0x12,0x0139);
    osDelay(5);
    WriteReg(0x13,0x1d00);
    WriteReg(0x29,0x0013);
    osDelay(5);
    WriteReg(0x20,0x0000);
    WriteReg(0x21,0x0000);
    WriteReg(0x30,0x0007);
    WriteReg(0x31,0x0302);
    WriteReg(0x32,0x0105);
    WriteReg(0x35,0x0206);
    WriteReg(0x36,0x0808);
    WriteReg(0x37,0x0206);
    WriteReg(0x38,0x0504);
    WriteReg(0x39,0x0007);
    WriteReg(0x3C,0x0105);
    WriteReg(0x3D,0x0808);
    WriteReg(0x50,0x0000);
    WriteReg(0x51,0x00EF);
    WriteReg(0x52,0x0000);
    WriteReg(0x53,0x013F);
    WriteReg(0x60,0xA700);
    WriteReg(0x61,0x0001);
    WriteReg(0x6A,0x0000);
    WriteReg(0x80,0x0000);
    WriteReg(0x81,0x0000);
    WriteReg(0x82,0x0000);
    WriteReg(0x83,0x0000);
    WriteReg(0x84,0x0000);
    WriteReg(0x85,0x0000);
    WriteReg(0x90,0x0010);
    WriteReg(0x92,0x0000);
    WriteReg(0x93,0x0003);
    WriteReg(0x95,0x0110);
    WriteReg(0x97,0x0000);
    WriteReg(0x98,0x0000);
    WriteReg(0x03,0x1018);
    WriteReg(0x07,0x0133);
  }
}

void LCD::Clear(uint16_t color) {
  uint32_t index=0;

  Cursor(0x00, 319);
  _lcd->LCD_REG=0x22;//WriteRAM_Prepare
  for(index=0;index<76800;index++)_lcd->LCD_RAM=color;
}

void LCD::Cursor(uint16_t x, uint16_t y) {
  WriteReg(0x20, x);
  WriteReg(0x21, y);
}
