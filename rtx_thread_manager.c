#include "rtx_os.h"
#include "cmsis_os2.h"
#include "sys.h"
#include "common.h"

osThreadId_t threadID_Start_Thread = NULL; /*线程ID*/

/****线程属性****/
const osThreadAttr_t thread_start_Attr =
{
  .name       = "APP_Name",         /****线程名字****/
  .stack_size = 512,                /****堆栈大小****/
  .priority   = osPriorityNormal,   /****线程优先级****/
  .attr_bits  = osThreadDetached,   /****线程类型,线程属于osThreadDetached退出后不能通过osThreadJoin重新加入调度****/
}

void thread_APP_Name(void *argument)
{
  const uint16_t Count = 1000;
  uint32_t tick;
  HAL_ResumeTick();                 /****复位HAL库时钟****/
  tick = osKernelGetTickCount();    /****获取HAL库时钟计数****/
  
  while（1）
  {
    tick += Count;
    osDelayUntil(tick);             /****绝对延时1s***/
    osThreadExit();                 /****线程退出****/
  }
  
}


int main(void)
{
  HAL_Init();
  Stm32_Clock_Init(RCC_PLL_MUL9);
  
  osKernelInitialize();        /****初始化内核****/
  
  /****创建线程****/
  threadID_Start_Thread = osThreadNew( thread_APP_Name, NULL, &thread_start_Attr);
  
  osKernelStart();/****启动内核****/
  
  while(1)
  {

  }
}



 void Thread_EventSender (
  void *argument); 
  // thread function 1
 

  void Thread_EventReceiver (
  void *argument); 
  // thread function 2
 

  osThreadId_t tid_Thread_EventSender; 
  // thread id 1
 

  osThreadId_t tid_Thread_EventReceiver; 
  // thread id 2
 
 
 

  osEventFlagsId_t evt_id; 
  // message queue id
 
 
 

  #define FLAGS_MSK1 0x00000001u
 

   
 

  void app_main (
  void)
 

  {
 

   tid_Thread_EventSender = 
  osThreadNew (Thread_EventSender, NULL, NULL);
 
 
  if (tid_Thread_EventSender == NULL) {
 

   ; 
  // do something
 

   }
 

   tid_Thread_EventReceiver = 
  osThreadNew (Thread_EventReceiver, NULL, NULL);
 
 
  if (tid_Thread_EventReceiver == NULL) {
 

   ; 
  // do something
 

   }
 

   ; 
  // do something
 

  }
 
 
 

  void Thread_EventSender (
  void *argument)
 

  {
 

   evt_id = 
  osEventFlagsNew(NULL);
 
 
  while (1) { 
 
 
  osEventFlagsSet(evt_id, FLAGS_MSK1);
 
 
  osDelay (1000); 
  // suspend thread
 

   }
 

  }
 
 
 

  void Thread_EventReceiver (
  void *argument)
 

  {
 

   uint32_t flags;
 
 
  while (1) {
 

   flags = 
  osEventFlagsWait (evt_id,FLAGS_MSK1,
  osFlagsWaitAny, 
  osWaitForever);
 
 
  //handle event
 

   }
 

  }
