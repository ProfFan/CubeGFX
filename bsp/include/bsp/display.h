//
// Created by Fan Jiang on 14/03/2018.
//

#ifndef CANBRIDGE_DISPLAY_H
#define CANBRIDGE_DISPLAY_H

#include <stm32f407xx.h>
typedef struct
{
  volatile uint16_t LCD_REG;
  volatile uint16_t LCD_RAM;
} LCD_TypeDef;
#define LCD_BASE    ((uint32_t)(0x60000000 | 0x0C000000))
#ifdef __cplusplus

extern "C" {
#endif

void StartDisplayTask(void const *argument);

#ifdef __cplusplus
};

class LCD {
public:
  explicit LCD(){
    //fsmc = _fsmc;
  }

  ~LCD() = default;

  uint16_t ReadReg(uint16_t addr);

  void WriteReg(uint16_t addr, uint16_t data);

private:
  //FSMC_Bank1_TypeDef fsmc;
  LCD_TypeDef* _lcd =    ((LCD_TypeDef *) LCD_BASE);
protected:

};

extern LCD* lcd1;

#endif

#endif //CANBRIDGE_DISPLAY_H
