//
// Created by Fan Jiang on 2017/5/1.
//
extern "C" {
#include "FreeRTOS.h"
#include "task.h"
#include "math.h"
#include "cmsis_os.h"
}

#include "bsp/serial.h"
#include "bsp/bsp_can.h"
#include "gui.h"
#include "ros.h"

#include "std_msgs/MultiArrayLayout.h"
#include "std_msgs/MultiArrayDimension.h"
#include <std_msgs/String.h>
#include <std_msgs/Float32.h>
#include <std_msgs/Int32.h>
#include <std_msgs/UInt8MultiArray.h>
#include <bsp/bsp_can.h>
#include <stm32f4xx_hal_can.h>

osThreadId serialTaskHandle;

QueueHandle_t serialQueue;

uint8_t print_buf[256];

uint8_t usbTxBuf[8192];

uint8_t usbRxBuf[256];
uint32_t usbRxLen = 0;

USBSerial *USBSerial1;



void StartSerialTask(void const *argument) {
  // int size;

  USBSerial1 = new USBSerial(&hUsbDeviceFS);

  auto nh = new ros::NodeHandle();

  auto *canData_msg = new std_msgs::UInt8MultiArray();
  // auto *str_msg = new std_msgs::String();
//  auto *encLF_msg = new std_msgs::Int32();
//  auto *encLB_msg = new std_msgs::Int32();
//  auto *encRF_msg = new std_msgs::Int32();
//  auto *encRB_msg = new std_msgs::Int32();

  auto pub_canData = new ros::Publisher("can/msgs", canData_msg);
  // auto chatter = new ros::Publisher("chatter", str_msg);
//  auto pub_encLF = new ros::Publisher("encoder/lf", encLF_msg);
//  auto pub_encLB = new ros::Publisher("encoder/lb", encLB_msg);
//  auto pub_encRF = new ros::Publisher("encoder/rf", encRF_msg);
//  auto pub_encRB = new ros::Publisher("encoder/rb", encRB_msg);
//
//  auto sub_curLF = new ros::Subscriber<std_msgs::Int32>("current/lf", CURRENT_CALLBACK(motorLF));
//  auto sub_curLB = new ros::Subscriber<std_msgs::Int32>("current/lb", CURRENT_CALLBACK(motorLB));
//  auto sub_curRF = new ros::Subscriber<std_msgs::Int32>("current/rf", CURRENT_CALLBACK(motorRF));
//  auto sub_curRB = new ros::Subscriber<std_msgs::Int32>("current/rb", CURRENT_CALLBACK(motorRB));

  auto canError_msg = new std_msgs::Int32();
  auto pub_canError = new ros::Publisher("can/error", canError_msg);


  // char hello[15] = "UAVLab Rover!";

  nh->initNode();
  //nh.advertise(*chatter);

  nh->advertise(*pub_canData);
//  nh->advertise(*pub_encLF);
//  nh->advertise(*pub_encLB);
//  nh->advertise(*pub_encRF);
//  nh->advertise(*pub_encRB);
//
//  nh.subscribe(*sub_curLF);
//  nh.subscribe(*sub_curLB);
//  nh.subscribe(*sub_curRF);
//  nh.subscribe(*sub_curRB);

  nh->advertise(*pub_canError);

  while (!nh->connected()){
    nh->spinOnce();
    osDelay(2);
  }

  canData_msg->layout.dim_length = 1;
  canData_msg->layout.dim = new std_msgs::MultiArrayDimension();
  canData_msg->layout.dim[0].stride = 4 + 8 + 1;
  canData_msg->layout.dim[0].label = "";
  canData_msg->layout.dim[0].size = 4 + 8 + 1;
  canData_msg->layout.data_offset = 0;

  canData_msg->data = (uint8_t *)malloc(sizeof(uint8_t) * (4 + 8 + 1));
  canData_msg->data_length = 4 + 8 + 1;
  (canData_msg->data)[4 + 8] = 0;

  std::function< void(CAN_RxMessageTypeDef*)> canCallback = [=](CAN_RxMessageTypeDef* msg){
    ((uint32_t*)(canData_msg->data))[0] = msg->header.StdId;
    memcpy((void *)(&(canData_msg->data[4])), msg->data, msg->header.DLC);
    (canData_msg->data)[4 + msg->header.DLC] = 0;
    pub_canData->publish(canData_msg);
  };

  can1->registerCallback(0, canCallback);

  portTickType xLastWakeTime;
  const portTickType xFrequency = 1;

  xLastWakeTime = xTaskGetTickCount();

  /* Infinite loop */
  for (;;) {

    //str_msg->data = hello;
    //chatter->publish(str_msg);

    // AHRS Attitude
    if (HAL_GetTick() % 5) {

      canError_msg->data = can1->errorCount;
      pub_canError->publish(canError_msg);

      if(USBSerial1->connected != nh->connected()) {
        USBSerial1->connected = nh->connected();
        gwinSetText(ghLabel1, ((USBSerial1->connected) ? "LINK ACTIVE" : "LINK INACTIVE"), TRUE);
      }


    }


//    if(usbRxLen > 0){
//      USBSerial1->rxISR(usbRxBuf,usbRxLen);
//      usbRxLen = 0;
//    }
    nh->spinOnce();
    USBSerial1->txService();

    vTaskDelayUntil(&xLastWakeTime, xFrequency);

  }
}

extern "C" void CDC_Receive_Hook(USBD_HandleTypeDef *husb, uint8_t *pbuf, uint32_t *Len) {

  if (USBSerial1 != nullptr) {
    USBSerial1->rxISR(pbuf, *Len);
  };

//  std::memcpy(usbRxBuf, pbuf, *Len);
//  usbRxLen = *Len;
}

int USBSerial::write(const uint8_t *buffer, int length) {
  for (int i = 0; i < length; i++) {
    this->txBuffer.put(buffer[i]);
  }
  return length;
}

int USBSerial::read(uint8_t *buffer, int length) {
  if ((int) (this->rxBuffer.available()) >= length) {
    for (int i = 0; i < length; i++) {
      buffer[i] = this->rxBuffer.get();
    }
    return length;
  }
  return -1;
}

char USBSerial::read() {
  if ((int) (this->rxBuffer.available()) >= 1) {
    return this->rxBuffer.get();
  }

  return 0;
}

int USBSerial::readable() {
  return this->rxBuffer.available();
}

void USBSerial::rxISR(const uint8_t *buffer, uint32_t length) {
  for (uint32_t i = 0; i < length; i++) {
    this->rxBuffer.put(buffer[i]);
  }
}

void USBSerial::txService() {
  int i = 0;

  USBD_CDC_HandleTypeDef *hcdc = (USBD_CDC_HandleTypeDef*)hUsbDeviceFS.pClassData;
  if (hcdc->TxState != 0){
    return;
  }

  while (this->txBuffer.available()) {
    usbTxBuf[i] = this->txBuffer.get();
    i = i + 1;
  }
  if (i)
    CDC_Try_Send(usbTxBuf, i, 1);
}

#undef CURRENT_CALLBACK
#undef CURRENT_CALLBACK_DEF