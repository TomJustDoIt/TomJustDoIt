#include "rtx_os.h"
#include "cmsis_os2.h"

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
