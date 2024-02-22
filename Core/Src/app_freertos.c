/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : app_freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os2.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include "lwip.h"
#include "lwip/api.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
/* TCP Client */
typedef enum
{
  REQ = 0,
  RESP = 1
} packet_type;

struct time_packet
{
  uint8_t head; //0xAE
  uint8_t type; //0:REQ, 1:RESP
  uint8_t year;
  uint8_t month;
  uint8_t day;
  uint8_t hour;
  uint8_t minute;
  uint8_t second;
  uint8_t dummy[247]; //you may add more information
  uint8_t tail; //0xEA
};
//256 bytes

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define SERVER_IP1  192 //server ip address
#define SERVER_IP2  168
#define SERVER_IP3  219
#define SERVER_IP4  100
#define SERVER_PORT 7777//server listen port

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
/*TCP Client */
extern struct netif gnetif; //extern gnetif
osThreadId_t tcpClientTaskHandle;  //tcp client task handle
const osThreadAttr_t tcpClientTask_attributes = {
  .name = "tcpClientTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
ip_addr_t server_addr; //server address
struct time_packet packet; //256 bytes time_packet structure


osThreadId_t echoTaskHandle;  //echo server task handle
const osThreadAttr_t echoTask_attributes = {
  .name = "echoTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};
/* USER CODE END Variables */
/* Definitions for defaultTask */
osThreadId_t defaultTaskHandle;
const osThreadAttr_t defaultTask_attributes = {
  .name = "defaultTask",
  .priority = (osPriority_t) osPriorityNormal,
  .stack_size = 1024 * 4
};

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
extern void MX_LWIP_Init(void);
void StartEchoTask(void const *argument);

void StartTcpClientTask(void const *argument); //tcp client task function

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void *argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* GetIdleTaskMemory prototype (linked to static allocation support) */
void vApplicationGetIdleTaskMemory( StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize );

/* Hook prototypes */
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName);

/* USER CODE BEGIN 4 */
void vApplicationStackOverflowHook(xTaskHandle xTask, char *pcTaskName)
{
  /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */

  HAL_GPIO_WritePin(LED3_RED_GPIO_Port, LED3_RED_Pin, GPIO_PIN_SET); //turn on red led when detects stack overflow
}
/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
  /* creation of defaultTask */
  defaultTaskHandle = osThreadNew(StartDefaultTask, NULL, &defaultTask_attributes);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_EVENTS */
  /* add events, ... */
  /* USER CODE END RTOS_EVENTS */

}
/* USER CODE BEGIN Header_StartDefaultTask */
/**
* @brief Function implementing the defaultTask thread.
* @param argument: Not used
* @retval None
*/
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void *argument)
{
  /* USER CODE BEGIN defaultTask */

  MX_LWIP_Init();
  //echoTaskHandle = osThreadNew(StartEchoTask, NULL, &echoTask_attributes);
  tcpClientTaskHandle = osThreadNew(StartTcpClientTask, NULL, &tcpClientTask_attributes);
  /* Infinite loop */
  for(;;)
  {
    HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin);

    osDelay(100);
  }
  /* USER CODE END defaultTask */
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void StartEchoTask(void const *argument)
{
  struct netconn *conn, *newconn;
  err_t err, accept_err;
  struct netbuf *buf;
  void *data;
  u16_t len;

  LWIP_UNUSED_ARG(argument);

  conn = netconn_new(NETCONN_TCP); //new tcp netconn

  if (conn != NULL)
  {
    err = netconn_bind(conn, NULL, 7777); //bind to port 7777

    if (err == ERR_OK)
    {
      netconn_listen(conn); //listen at port 7777

      while (1)
      {
        accept_err = netconn_accept(conn, &newconn); //accept new connection

        if (accept_err == ERR_OK) //accept ok
        {
          while (netconn_recv(newconn, &buf) == ERR_OK) //receive data
          {
            do
            {
              netbuf_data(buf, &data, &len); //receive data pointer & length
              netconn_write(newconn, data, len, NETCONN_COPY); //echo back to the client

              HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin); //toggle data led
            }
            while (netbuf_next(buf) >= 0); //check buffer empty

            netbuf_delete(buf); //clear buffer
          }

          netconn_close(newconn); //close session
          netconn_delete(newconn); //free memory
        }
      }
    }
    else
    {
      netconn_delete(newconn); //free memory
    }
  }
}

void StartTcpClientTask(void const *argument)
{
  err_t err;
  struct netconn *conn;
  struct netbuf *buf;
  void *data;

  u16_t len; //buffer length
  u16_t nRead; //read buffer index
  u16_t nWritten; //write buffer index

  LWIP_UNUSED_ARG(argument);

  while (1)
  {
    if (gnetif.ip_addr.addr == 0 || gnetif.netmask.addr == 0) //gnetif.gw.addr == 0 system has no valid ip address
    {
      osDelay(1000);
      continue;
    }
    else //valid ip address
    {
      osDelay(100); //request interval
    }

    nRead = 0; //clear indexes
    nWritten = 0;

    conn = netconn_new(NETCONN_TCP); //new tcp netconn

    if (conn != NULL)
    {
      IP4_ADDR(&server_addr, SERVER_IP1, SERVER_IP2, SERVER_IP3, SERVER_IP4); //server ip
      err = netconn_connect(conn, &server_addr, SERVER_PORT); //connect to the server

      if (err != ERR_OK)
      {
        netconn_delete(conn); //free memory
        continue;
      }

      memset(&packet, 0, sizeof(struct time_packet));
      packet.head = 0xAE; //head
      packet.type = REQ; //request type
      packet.tail = 0xEA; //tail

      do
      {
        if (netconn_write_partly(
            conn, //connection
            (const void*) (&packet + nWritten), //buffer pointer
            (sizeof(struct time_packet) - nWritten), //buffer length
            NETCONN_NOFLAG, //no copy
            (size_t*) &len) != ERR_OK) //written len
        {
          netconn_close(conn); //close session
          netconn_delete(conn); //free memory
          continue;
        }
        else
        {
          nWritten += len;
        }
      }
      while (nWritten < sizeof(struct time_packet)); //send request

      while (netconn_recv(conn, &buf) == ERR_OK) //receive the response
      {
        do
        {
          netbuf_data(buf, &data, &len); //receive data pointer & length

          memcpy(&packet + nRead, data, len);
          nRead += len;
        }
        while (netbuf_next(buf) >= 0); //check buffer empty
        netbuf_delete(buf); //clear buffer
      }

      if (nRead == sizeof(struct time_packet) && packet.type == RESP) //if received length is valid
      {
        printf("%04d-%02d-%02d %02d:%02d:%02d\n", packet.year + 2000, packet.month, packet.day, packet.hour, packet.minute, packet.second); //print time information
        HAL_GPIO_TogglePin(LED1_GREEN_GPIO_Port, LED1_GREEN_Pin); //toggle data led
      }

      netconn_close(conn); //close session
      netconn_delete(conn); //free memory
    }
  }
}

static StaticTask_t xIdleTaskTCBBuffer;
static StackType_t xIdleStack[configMINIMAL_STACK_SIZE];

void vApplicationGetIdleTaskMemory(StaticTask_t **ppxIdleTaskTCBBuffer, StackType_t **ppxIdleTaskStackBuffer, uint32_t *pulIdleTaskStackSize)
{
  *ppxIdleTaskTCBBuffer = &xIdleTaskTCBBuffer;
  *ppxIdleTaskStackBuffer = &xIdleStack[0];
  *pulIdleTaskStackSize = configMINIMAL_STACK_SIZE;
  /* place for user code */
}
/* USER CODE END Application */
