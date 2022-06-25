 # freertos study

[source code](https://sourceforge.net/)

# Task create function

    BaseType_t xTaskCreate(TaskFunction_t pxTaskCode,
                                const char * const pcName,
                                const configSTACK_DEPTH_TYPE usStackDepth,
                                void * const pvParameters,
                                UBaseType_t uxPriority,
                                TaskHandle_t * const pxCreatedTask)
                           
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

    #define RTOS_TEST_QUEUE_LEN    0x10
    typedef struct{
        uint8_t type;
        void *p_data;
    }queue_item;

    void *rtos_study_queue_handle;
    queue_item item;
    rtos_study_queue_handle = xQueueCreate(RTOS_TEST_QUEUE_LEN,sizeof(queue_item));
    xQueueSend(rtos_study_queue_handle,&item,0x1000);
    xQueueReceive(rtos_study_queue_handle,&item,1000);
