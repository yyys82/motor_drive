//
// Created by zhangyucong on 2023/11/22.
//

#include "mission_can.h"
#include "can.h"
#include <string.h>
#include "main.h"
#include "mission_uart.h"

uint8_t motorID = 1;       //初始电机ID
uint32_t lastRecvTime = 0; //上次收到CAN数据帧的时间

static void CAN_SetFilters(void) {
    //设置筛选器
    CAN_FilterTypeDef filter;

    filter.FilterBank = 0;                        //筛选器组编号
    filter.FilterMode = CAN_FILTERMODE_IDMASK;    //ID掩码模式
    filter.FilterScale = CAN_FILTERSCALE_32BIT;   //32位
    //不根据ID进行筛选
    filter.FilterIdHigh = 0x0000;               //ID的高十六位
    filter.FilterIdLow = 0x0000;                //ID的低十六位，IDE=0 标准格式帧 RTR=0 数据帧
    filter.FilterMaskIdHigh = 0x0000;           //掩码的高十六位
    filter.FilterMaskIdLow = 0x0000;            //掩码的低十六位，均接受，所有位任意

    filter.FilterFIFOAssignment = CAN_FILTER_FIFO0; //使用FIFO0接收数据
    //filter.SlaveStartFilterBank = 0;          //只有一个CAN模块，该参数无意义
    filter.FilterActivation = CAN_FILTER_ENABLE;  //激活过滤器
  
    HAL_CAN_ConfigFilter(&hcan, &filter);

}

//发送一个反馈数据帧
void CAN_SendState(const float angle, const float speed) {
    CAN_TxHeaderTypeDef header;
    header.StdId = motorID + 0x100;
    header.IDE = CAN_ID_STD;            //标准帧
    header.RTR = CAN_RTR_DATA;          //数据帧
    header.DLC = 8;                     //一共8个字节
    header.TransmitGlobalTime = DISABLE;  //不使用时间戳
    uint8_t data[8];
    memcpy(data, &(int32_t) {angle * 1000}, 4); //角度数据放在前四个字节
    memcpy(&data[4], &(int16_t) {speed * 10}, 2); //转速数据放在第5-6字节
    uint32_t mailbox;
    HAL_CAN_AddTxMessage(&hcan, &header, data, &mailbox);
}

    uint8_t rxData[8];
void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
    CAN_RxHeaderTypeDef header;
    if (HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &header, rxData) != HAL_OK) {
        //出现异常
        return;
    }

//    if (header.StdId == 0x100 && motorID <= 4) //ID=1~4接收0x100数据帧
//    {
//        targetVotage = *(int16_t*)&rxData[(motorID-1)*2] / 1000.0f;
//        lastRecvTime = HAL_GetTick();
//    } else if (header.StdId == 0x200 && motorID > 4) //ID=5~8接收0x200数据帧
//    {
//        targetVotage = *(int16_t*)&rxData[(motorID-5)*2] / 1000.0f;
//        lastRecvTime = HAL_GetTick();
//    }
}

void CAN_Init(void) {
    CAN_SetFilters();              //设置过滤器
    __HAL_CAN_ENABLE_IT(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);//启用FIFO0接收到新消息的中断事件
    HAL_CAN_Start(&hcan);                                  //启动CAN
}


////CAN离线检测，500ms没收到CAN信号则停机
void CAN_offlineCheckProcess(void)
{
    static uint8_t isOffline = 0;
//    if(HAL_GetTick() - lastRecvTime > 500)
//    {
//        if(!isOffline)//离线后只进行一次target归零
//        {
//            HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_SET);
//            targetVotage = 0;
//            isOffline = 1;
//        }
//    }
//    else
//    {
//        isOffline = 0;
//        HAL_GPIO_WritePin(ERROR_LED_GPIO_Port, ERROR_LED_Pin, GPIO_PIN_RESET);
//    } 
}


