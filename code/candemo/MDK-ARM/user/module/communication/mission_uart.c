//
// Created by zhangyucong on 2023/11/22.
//

#include "mission_uart.h"
#include "usart.h"
#include "mission_can.h"

#include <string.h>
#include <stdio.h>

char rxProBuf[16];
////单片机软件复位
//void System_Reset(void)
//{
//    __set_FAULTMASK(1);
//    NVIC_SystemReset();
//}


//void bufCommandCheck(const char buf[])
//{

//    if(strstr(buf,"setid"))
//    {
//        int tempid;
//        sscanf(buf,"setid:%d\r\n",&tempid);
//        Flash_SaveMotorID(tempid);
//        System_Reset();
//    } else if (strstr(buf,"erase"))
//    {
//        Flash_EraseAllPages();
//        System_Reset();
//    }
//    else if (strstr(buf,"reboot"))
//    {
//        System_Reset();
//    }
//    if (strstr(buf,"vot:"))
//    {
//      int millivolt;
//      sscanf(buf,"vot:%d\r\n",&millivolt);
//      targetVotage=millivolt/1000.0f;
//      targetVotage = _constrain(targetVotage, -voltage_limit, voltage_limit);
//      printf("votage is %.3f\r\n",targetVotage);
//    }
//    if (strstr(buf,"angle"))
//    {
//      printf("e_angle is %.3f\r\n",electrical_angle);
//    }
//}


void USART_DMA_StartReceive(void)
{
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2,(uint8_t*)rxProBuf,16);
   // __HAL_DMA_DISABLE_IT(&hdma_usart2_rx,DMA_IT_HT);
}


void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
    if(huart->Instance==USART1)
    {
        HAL_UART_DMAStop(huart);  //DMA通道被配置为环模式，每次接收完都需要关闭，防止数据错误
      //  bufCommandCheck(rxProBuf);
        memset(rxProBuf,0,16);      //清理数组
        USART_DMA_StartReceive();
    }
}


