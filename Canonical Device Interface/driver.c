
#include "driver.h"

char status = 0;
char command = 0;
char data[dataSize];

// Semaphore
sem_t sem;
// Thread
void* run(void *arg);
pthread_t thread;
volatile int running = 1;


void* run(void *arg){
    while (1)
    {
    if(running == 0 ){
        sem_post(&end);
        break;}

    if (command == 1) // Read
    {
        setStatus(1);

        
        for (int i = (dataSize-1); i >= 0; i--)
        {
            ind--;
            data[i] = internalData[ind];
            internalData[ind] = 0;
            if(ind < 0){
                setStatus(2);
                break;
            }
            
        }
        
        

        printData();
        setStatus(0);
        setCommand(0);
    }
    if (command == 2) // Write
    {
        setStatus(1);

        // Problem Memory gets deleted every time
        for (int i = 0; i < dataSize; i++)
        {
            internalData[ind++] = data[i];
            data[i] = 0;
            if(ind > internalDataSize){
                setStatus(2);
                break;
            }
        }

        printData();
        setStatus(0);    
        setCommand(0);

    }
    if (command == 4) // Reset
    {
        setStatus(1);
        
        ind = 0;
        
        printData();  
        setStatus(0);
        setCommand(0);
    }
    if (command == 8) // Delete
    {
        setStatus(1);

        do
        {
            ind--;
            internalData[ind] = 0;
        } while (ind > 0);

        for (int i = 0; i < dataSize; i++)
        {
            data[i] = 0;
        }        
        
        printData(); 
        status = 0;
        setCommand(0);
    }
    sem_wait(&sem);
    }
   
}

void startDriver(){
    running = 1;
    sem_init(&sem,0,0);
    sem_init(&end,0,0);
    pthread_create(&thread,NULL,&run,NULL);
    pthread_detach(thread);
    
}
void stopDriver(){
    running = 0;
};

void printData(){
    printf("\nSTATUS:%d",status);
    printf("\nINTERNALDATA:[");
    for (int i = 0; i < internalDataSize; i++)
    {
         
        char temp = internalData[i];

        if(temp == 0){
            temp = '_';
        }
        
        printf("%c", temp);
    }
    
    printf("]\n");     
}




