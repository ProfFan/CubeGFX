//
// Created by Fan Jiang on 2017/5/4.
//

#ifndef CHASSIS_BSP_CAN_H
#define CHASSIS_BSP_CAN_H

#include "can.h"
#ifdef __cplusplus
extern "C" {
#endif

#define MAX_CAN_CALLBACK 32

void StartCANBusTask(void const *argument);
// void HAL_CAN_RxCpltCallback(CAN_HandleTypeDef *_hcan);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
#include <os/mutex.hpp>
#include <functional>

typedef struct {
  CAN_RxHeaderTypeDef *header;
  uint8_t *data;
} CAN_RxMessageTypeDef;

class CAN {
public:

  CAN(CAN_HandleTypeDef *hcan);

  ~CAN();

  int registerCallback(uint32_t messageID, std::function<void(CAN_RxHeaderTypeDef *, uint8_t *)> callback);

  void processFrame(CAN_RxMessageTypeDef message);

  CAN_HandleTypeDef *hcan;

  int32_t errorCount = 0;

  int sendMessage(uint32_t stdID, uint32_t extID, uint8_t *body, uint8_t size);

private:
  int tableSize = 0;
  uint32_t idTable[MAX_CAN_CALLBACK];

  std::function<void(CAN_RxHeaderTypeDef *, uint8_t *)> callbackTable[MAX_CAN_CALLBACK];

  cpp_freertos::MutexStandard* _mutex;
};

extern CAN *can1;
extern CAN *can2;

#endif

#endif //CHASSIS_BSP_CAN_H
