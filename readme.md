 # freertos study

[source code](https://sourceforge.net/)

# task function

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
