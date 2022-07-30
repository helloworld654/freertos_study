
# List #

    #include<stdio.h>

    struct list_head{
        struct list_head *prev,*next;
    };

    static void add_to_list(struct list_head *new,struct list_head *prev,struct list_head *next)
    {
        prev->next = new;
        next->prev = new;
        new->prev = prev;
        new->next = next;
    }

    void add_entry_to_tail(struct list_head *new,struct list_head *head)
    {
        add_to_list(new,head->prev,head);
    }

    void add_entry_to_head(struct list_head *new,struct list_head *head)
    {
        add_to_list(new,head,head->next);
    }

    int list_is_empyt(struct list_head *head)
    {
        return (head == head->next);
    }

    int del_entry_from_list(struct list_head *del,struct list_head *head)
    {
        if(list_is_empyt(head)){
            return 1;
        }
        del->prev->next = del->next;
        del->next->prev = del->prev;
        return 0;
    }

    struct list_head head = {&head,&head};

    typedef struct{
        int num;
        struct list_head list;
    }struct_list;

    struct_list stru_arr[] = {
        [0] = {
            .num = 0
        },
        [1] = {
            .num = 1
        },
        [2] = {
            .num = 2
        }
    };

    #define FIND_STRU(list,type,name)  \
        (type *)((unsigned int)list-(unsigned int)((unsigned int)&(((type *)(0))->name)))

    #define FOR_EACH_LIST(pos,head)  \
        for(pos=(head)->next;pos!=head;pos=(pos)->next)

    int main(void)
    {
        struct list_head *each_list,*head_list;
        int i;
        struct_list *stru_entry;
        head_list = &head;
        
        // add entry to tail test
        for(i=0;i<sizeof(stru_arr)/sizeof(stru_arr[0]);i++){
            add_entry_to_tail(&((stru_arr+i)->list),head_list);
        }
        if(!list_is_empyt(head_list)){
            FOR_EACH_LIST(each_list,head_list)
            {
                stru_entry = FIND_STRU(each_list,struct_list,list);
                printf("num:%d\r\n",stru_entry->num);
            }
        }

        // del entry from list test
        FOR_EACH_LIST(each_list,head_list)
        {
            del_entry_from_list(each_list,head_list);
        }
        if(list_is_empyt(head_list))
            printf("List is empty\r\n");

        // add entry to head test
        for(i=0;i<sizeof(stru_arr)/sizeof(stru_arr[0]);i++){
            add_entry_to_head(&((stru_arr+i)->list),head_list);
        }
        if(!list_is_empyt(head_list)){
            FOR_EACH_LIST(each_list,head_list)
            {
                stru_entry = FIND_STRU(each_list,struct_list,list);
                printf("num:%d\r\n",stru_entry->num);
            }
        }

        return 0;
    }
