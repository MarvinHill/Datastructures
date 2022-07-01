
#include "driver.h"
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



// Print Methode
void printData();

// Semaphore
sem_t sem;

// Thread
void* run(void *arg);
pthread_t thread;
volatile int running = 1;


void writeData(char* inData){
    for (int i = 0; i < dataSize; i++)
    {
        data[i] = *inData;
        inData++;
    }

    command = "02";
    sem_post(&sem);
}

char* readData(){
    // Implementierung
    sem_post(&sem);
} 
char* getStatus(){
    return status;
}

void* run(void *arg){
    while (1)
    {
    
    if (strcmp(command, "00") == 0) // Idle
    {
        if(running == 0 ){
            printData();
            sem_post(&end);
            pthread_exit(0);
            break;}
    }
    if (strcmp(command, "01") == 0) // Read
    {
        status = "01";
        

        printData();
        status = "00";
        command = "00";
    }
    if (strcmp(command, "02") == 0) // Write
    {
        status = "01";

        // Problem Memory gets deleted every time
        for (int i = 0; (i < dataSize) && (ind < internalDataSize); i++)
        {
            internalData[ind++] = data[i];
            data[i] = 0;
        }

        printData();
        status = "00";
        command = "00";

    }
    if (strcmp(command, "04") == 0) // Reset
    {
        status = "01";

        printData();  
        status = "00";
        command = "00";
    }
    if (strcmp(command, "08") == 0) // Delete
    {
        status = "01";
        
        printData();
        status = "00";
        command = "00";
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
    printf("\nDATA:[");
    for (int i = 0; i < dataSize; i++)
    {
        
        char temp = data[i];

        if(temp == 0){
            temp = '_';
        }
        
        printf("%c", temp);
    }
    
    printf("]");
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


char* data1 = "HalloHalloHalloHallo";
char* data2 = "BalloBalloBalloBallo";



int main(int argc, char const *argv[])
{
    startDriver();
    writeData(data1);
    writeData(data2);
    stopDriver();
    sem_wait(&end);
    return 0;
}

