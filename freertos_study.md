 
 # FREERTOS STUDY

[Source code](https://sourceforge.net/)

# Task create function

    #include "FreeRTOS.h"
    #include "task.h"
    /*
    BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                                const char * const pcName,
                                const configSTACK_DEPTH_TYPE usStackDepth,
                                void * const pvParameters,
                                UBaseType_t uxPriority,
                                TaskHandle_t * const pxCreatedTask)
    */
    #define RTOS_TASK_STACK_SIZE    2048
    #define RTOS_TASK_PRIORITY    1

    void *rtos_study_task_handle;

    static void rtos_study_task(void *arg)
    {
        printf("[%s] enter\r\n",__func__);
        while(1){
            printf("[%s] every cycle\r\n",__func__);
            vTaskDelay(1500/portTICK_PERIOD_MS);
        }
    }

    void task_create_test(void)
    {
        xTaskCreate(rtos_study_task,"study_task",RTOS_TASK_STACK_SIZE,NULL,RTOS_TASK_PRIORITY,rtos_study_task_handle);
    }

# Queue use example

    #include "freertos/queue.h"
    #define RTOS_TEST_QUEUE_LEN    0x10
    typedef struct{
        uint8_t type;
        void *p_data;
    }queue_item;

    void *rtos_study_queue_handle;
    queue_item item;
    // xQueueCreate( uxQueueLength, uxItemSize )
    rtos_study_queue_handle = xQueueCreate(RTOS_TEST_QUEUE_LEN,sizeof(queue_item));
    // xQueueSend( xQueue, pvItemToQueue, xTicksToWait )
    xQueueSend(rtos_study_queue_handle,&item,1000);
    // xQueueReceive( QueueHandle_t xQueue, void * const pvBuffer, TickType_t xTicksToWait )
    xQueueReceive(rtos_study_queue_handle,&item,1000);

# Sem use example

    #include "semphr.h"
    void *rtos_study_sem_handle;
    // xSemaphoreCreateCounting( uxMaxCount, uxInitialCount )
    rtos_study_sem_handle = xSemaphoreCreateCounting(1,0);
    // xSemaphoreGive( xSemaphore )
    xSemaphoreGive(rtos_study_sem_handle);
    // xSemaphoreTake( xSemaphore, xBlockTime )
    xSemaphoreTake(rtos_study_sem_handle,1000);

# Mutex 互斥量使用方法

和二值信号量相比，增加优先级继承机制，防止中间优先级任务抢占，出现优先级反转问题

    void *rtos_study_mutex_handle;

    void rtos_study_task_a(void *arg){
        rtos_study_mutex_handle = xSemaphoreCreateMutex();
        while(1){
            printf("\r\n[%s] try to take mutex",__func__);
            if(xSemaphoreTake(rtos_study_mutex_handle,1000/portTICK_PERIOD_MS)){  // timeout 1000ms
                printf("\r\n[%s] take the mutex success",__func__);
                vTaskDelay(1500/portTICK_PERIOD_MS);  // take the mutex for 1500ms
                printf("\r\n[%s] give the mutex",__func__);
                xSemaphoreGive(rtos_study_mutex_handle);
            }
            else{
                printf("\r\n[%s] take the mutex timeout",__func__);
            }
        }

    void rtos_study_task_b(void *arg){
        while(1){
            if(rtos_study_mutex_handle){
                printf("\r\n[%s] try to take mutex",__func__);
                if(xSemaphoreTake(rtos_study_mutex_handle,1000/portTICK_PERIOD_MS)){  // timeout 1000ms
                    printf("\r\n[%s] take the mutex success",__func__);
                    vTaskDelay(500/portTICK_PERIOD_MS);  // take the mutex for 500ms
                    printf("\r\n[%s] give the mutex",__func__);
                    xSemaphoreGive(rtos_study_mutex_handle);
                }
                else{
                    printf("\r\n[%s] take the mutex timeout",__func__);
                }
            }
        }
    }

    void task_create_test(void)
    {
        xTaskCreate(rtos_study_task_a,"study_task_A",2048,NULL,1,rtos_study_task_handle_A);
        xTaskCreate(rtos_study_task_b,"study_task_B",2048,NULL,1,rtos_study_task_handle_B);
    }

    /*
    [18:19:35.365] [rtos_study_task_a] try to take mutex  // task A try to take mutex
    [18:19:35.365] [rtos_study_task_a] take the mutex success  // task A take mutex success
    [18:19:35.375] [rtos_study_task_b] try to take mutex  // task B try to take mutex

    [18:19:36.355] [rtos_study_task_b] take the mutex timeout  // task B take the mutex timeout,1000ms
    [18:19:36.355] [rtos_study_task_b] try to take mutex  // task B try to take the mutex second time

    [18:19:36.855] [rtos_study_task_a] give the mutex  // task A give the mutex,have used 1500ms
    [18:19:36.855] [rtos_study_task_b] take the mutex success  // task B take mutex success
    [18:19:36.865] [rtos_study_task_a] try to take mutex  // task A take mutex second time

    [18:19:37.359] [rtos_study_task_b] give the mutex  // task B give mutex,have used 500ms
    [18:19:37.378] [rtos_study_task_a] take the mutex success  // task A take mutex success second time
    [18:19:37.378] [rtos_study_task_b] try to take mutex  // task B try to take mutex third time
    */

# EventGroup use example

    EventBits_t xEventGroupSetBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToSet )

    EventBits_t xEventGroupWaitBits( EventGroupHandle_t xEventGroup, const EventBits_t uxBitsToWaitFor,
     const BaseType_t xClearOnExit, const BaseType_t xWaitForAllBits, TickType_t xTicksToWait )
    /*
    xClearOnExit : whether clear bits after exit this api
    xWaitForAllBits : whether wait for all bits are ready
    */

    void *event_group_handle;

    static void rtos_event_task_A(void *arg)
    {
        printf("\r\n[%s] enter",__func__);
        event_group_handle = xEventGroupCreate();
        while(1){
            vTaskDelay(500/portTICK_PERIOD_MS);
            printf("\r\n[%s] SET event bit 0x80",__func__);
            xEventGroupSetBits(event_group_handle,0x80);
            
            vTaskDelay(500/portTICK_PERIOD_MS);
            printf("\r\n[%s] SET event bit 0x800",__func__);
            xEventGroupSetBits(event_group_handle,0x800);
        }
    }

    static void rtos_event_task_B(void *arg)
    {
        printf("\r\n[%s] enter",__func__);
        while(1){
            if(event_group_handle){
                printf("\r\n[%s] start wait event 0x80",__func__);
                if(xEventGroupWaitBits(event_group_handle,0x80,true,false,1000/portTICK_PERIOD_MS)){
                    printf("\r\n[%s]get the event SUCCESS",__func__);
                }
                else{
                    printf("\r\n[%s]get event timeout",__func__);
                }
            }
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }

    static void rtos_event_task_C(void *arg)
    {
        printf("\r\n[%s] enter",__func__);
        while(1){
            if(event_group_handle){
                printf("\r\n[%s] start wait event 0x880",__func__);
                if(xEventGroupWaitBits(event_group_handle,0x880,true,true,1000/portTICK_PERIOD_MS)){
                    printf("\r\n[%s]get the event SUCCESS",__func__);
                }
                else{
                    printf("\r\n[%s]get event timeout",__func__);
                }
            }
            vTaskDelay(10/portTICK_PERIOD_MS);
        }
    }

    void task_create_test(void)
    {
        xTaskCreate(rtos_event_task_A,"event_task_A",2048,NULL,1,NULL);
        xTaskCreate(rtos_event_task_B,"event_task_B",2048,NULL,1,NULL);
        xTaskCreate(rtos_event_task_C,"event_task_C",2048,NULL,1,NULL);
    }

    /*
    [20:29:26.643] [rtos_event_task_B] start wait event 0x80
    [20:29:26.643] [rtos_event_task_C] start wait event 0x880

    [20:29:27.123] [rtos_event_task_A] SET event bit 0x80
    [20:29:27.123] [rtos_event_task_B]get the event SUCCESS
    [20:29:27.133] [rtos_event_task_B] start wait event 0x80

    [20:29:27.623] [rtos_event_task_A] SET event bit 0x800
    [20:29:27.633] [rtos_event_task_C]get the event SUCCESS
    [20:29:27.643] [rtos_event_task_C] start wait event 0x880

    [20:29:28.134] [rtos_event_task_A] SET event bit 0x80
    [20:29:28.138] [rtos_event_task_B]get the event SUCCESS
    [20:29:28.138] [rtos_event_task_C]get the event SUCCESS
    [20:29:28.138] [rtos_event_task_C] start wait event 0x880
    [20:29:28.144] [rtos_event_task_B] start wait event 0x80

    [20:29:28.623] [rtos_event_task_A] SET event bit 0x800

    [20:29:29.124] [rtos_event_task_A] SET event bit 0x80
    [20:29:29.124] [rtos_event_task_C]get the event SUCCESS
    [20:29:29.133] [rtos_event_task_B]get the event SUCCESS
    [20:29:29.133] [rtos_event_task_B] start wait event 0x80
    [20:29:29.143] [rtos_event_task_C] start wait event 0x880
    */

# Timer test

    #include "freertos/timers.h"
    TimerHandle_t xTimerCreate(const char * const pcTimerName,
                                    const TickType_t xTimerPeriodInTicks,
                                    const UBaseType_t uxAutoReload,
                                    void * const pvTimerID,
                                    TimerCallbackFunction_t pxCallbackFunction );
    xTimerStart( xTimer, xTicksToWait );
    void *pvTimerGetTimerID( const TimerHandle_t xTimer );
