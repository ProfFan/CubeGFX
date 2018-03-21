//
// Created by Fan Jiang on 2017/5/4.
//

#include <stm32f4xx_hal_can.h>
#include <cmsis_os.h>
#include <climits>
#include <os/queue.hpp>
#include <bsp/bsp_can.h>
#include "bsp/bsp_can.h"

osThreadId canTaskHandle;

CAN *can1;

BaseType_t xResult;
uint32_t ulNotifiedValue;

cpp_freertos::Queue can1RxQueue(10, sizeof(CAN_RxMessageTypeDef));

CAN::CAN(CAN_HandleTypeDef *hcan) {
  this->hcan = hcan;
  this->_mutex = new cpp_freertos::MutexStandard;
}

CAN::~CAN() {
  delete _mutex;
}

int CAN::registerCallback(uint32_t messageID, std::function<void(CAN_RxHeaderTypeDef *, uint8_t *)> callback) {

  _mutex->Lock();

  if (tableSize < MAX_CAN_CALLBACK) {
    uint32_t prim;

    /* Read PRIMASK register, check interrupt status before you disable them */
    /* Returns 0 if they are enabled, or non-zero if disabled */
    prim = __get_PRIMASK();

    __disable_irq();

    idTable[tableSize] = messageID;
    callbackTable[tableSize] = callback;
    tableSize = tableSize + 1;

    if (!prim) __enable_irq();

    _mutex->Unlock();
    return 0;
  } else {
    _mutex->Unlock();
    return 1;
  }
}

void CAN::processFrame(CAN_RxMessageTypeDef message) {
  for (int i = 0; i < tableSize; i++) {
    if (idTable[i] == message.header->StdId) {
      callbackTable[i](message.header, message.data);
    }
  }
  // HAL_GPIO_TogglePin(GPIOE, GPIO_PIN_7);
}

int CAN::sendMessage(uint32_t stdID, uint32_t extID, uint8_t *body, uint8_t size) {
  CAN_TxHeaderTypeDef header;

  header.StdId = stdID;
  header.ExtId = extID;
  header.DLC = size;
  header.IDE = 0;
  header.RTR = 0;
  header.TransmitGlobalTime = DISABLE;

  uint32_t *dummyTxMailbox;
  return HAL_CAN_AddTxMessage(hcan, &header, body, dummyTxMailbox);
}

// extern int messageCount;

extern "C" {
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *_hcan) {

  CAN_RxHeaderTypeDef* hdr;
  uint8_t* data;

  if (_hcan == can1->hcan) {

    //can1->processFrame(_hcan->pRxMsg);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;

    HAL_CAN_GetRxMessage(_hcan, CAN_RX_FIFO0, hdr, data);

    CAN_RxMessageTypeDef msg;

    msg.header = hdr;
    msg.data = data;

    can1RxQueue.EnqueueFromISR(&msg, &xHigherPriorityTaskWoken);

    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    //HAL_CAN_Receive_IT(&hcan1, CAN_FIFO0);
  }
}

void HAL_CAN_ErrorCallback(CAN_HandleTypeDef *_hcan) {
  if (_hcan == can1->hcan) {
    __HAL_CAN_CLEAR_FLAG(can1->hcan, CAN_FLAG_FOV0);
    //__HAL_CAN_ENABLE_IT(can1->hcan, CAN_IT_FMP0);
    HAL_CAN_ActivateNotification(can1->hcan, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING);
  }
}

void StartCANBusTask(void const *argument) {
  can1 = new CAN(&hcan1);

  CAN_FilterTypeDef CAN_FilterConfigStructure;

  CAN_FilterConfigStructure.FilterMode = CAN_FILTERMODE_IDMASK;
      CAN_FilterConfigStructure.FilterScale = CAN_FILTERSCALE_32BIT;
      CAN_FilterConfigStructure.FilterIdHigh = 0x0000;
      CAN_FilterConfigStructure.FilterIdLow = 0x0000;
      CAN_FilterConfigStructure.FilterMaskIdHigh = 0x0000;
      CAN_FilterConfigStructure.FilterMaskIdLow = 0x0000;
      CAN_FilterConfigStructure.FilterFIFOAssignment = CAN_FilterFIFO0;
      CAN_FilterConfigStructure.FilterBank = 14; // Filter Bank 0-14 for CAN1
      CAN_FilterConfigStructure.FilterActivation = ENABLE;

  if (HAL_CAN_ConfigFilter(&hcan1, &CAN_FilterConfigStructure) != HAL_OK) {
    while(1){

    }
  }

  osDelay(10);


  HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING);

  HAL_CAN_Start(&hcan1);

  osDelay(10);

  while (true) {
//    xResult = xTaskNotifyWait(pdFALSE,    /* Don't clear bits on entry. */
//                              ULONG_MAX,        /* Clear all bits on exit. */
//                              &ulNotifiedValue, /* Stores the notified value. */
//                              1000);
//
//    if (xResult == pdPASS) {
//      /* A notification was received.  See which bits were set. */
//
//    } else {
//      /* Did not receive a notification within the expected time. */
//
//    }

    CAN_RxMessageTypeDef tempMsg;

    while(!can1RxQueue.IsEmpty()){
      can1RxQueue.Dequeue(&tempMsg, 0);
      can1->processFrame(tempMsg);
    }

    if(HAL_CAN_GetState(&hcan1)==HAL_CAN_STATE_READY){
      can1->errorCount += 1;
      HAL_CAN_ActivateNotification(&hcan1, CAN_IT_RX_FIFO0_MSG_PENDING | CAN_IT_RX_FIFO1_MSG_PENDING);

    }

    osDelay(1);
  }
}

}