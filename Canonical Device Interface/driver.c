#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <string.h>
#include <stdio.h>
#include <time.h>

#include "driver.h"

#include <pthread.h>

void *threadFunc(void *v);

// Driver
char* internalData[internalDataSize];

pthread_t driver;
int iret1;

char *status = "00";
char *command = "00";
char* data[dataSize];
sem_t sem;
sem_t printSemt;

void startDriver()
{
    status = "00";
    sem_init(&sem, 0, 1);
    sem_init(&printSemt, 0, 1);
    pthread_detach(driver);
    iret1 = pthread_create(&driver, NULL, (void *)&threadFunc, NULL); 
}

void stopDriver()
{
    pthread_join(driver,NULL);
    
}

void *threadFunc(void *v)
{

    while (1)
    {
        if (strcmp(command,"00") == 0){
            continue;
            sem_post(&sem);
        } // 00 idle

        if (strcmp(command,"01") == 0){
            sem_wait(&sem);

            sem_wait(&printSemt);
            printData();
            sem_post(&printSemt);

            status = "01";
            // --------------------------------------------------------
            // code
            // --------------------------------------------------------
           
            status = "00";
            command = "00";

            sem_wait(&printSemt);
            printData();
            sem_post(&printSemt);

            sem_post(&sem);
            } // 01 read

        if (strcmp(command,"02") == 0){
            sem_wait(&sem);
            
            
            sem_wait(&printSemt);
            printData();
            sem_post(&printSemt);

            status = "01";
            // --------------------------------------------------------
            // code
            // --------------------------------------------------------
            
            status = "00";
            command = "00";

            sem_wait(&printSemt);
            printData();
            sem_post(&printSemt);

            sem_post(&sem);
            } // 02 write

        if (strcmp(command,"04") == 0){
            sem_wait(&sem);
            status = "01";
            // --------------------------------------------------------
            // code
            // --------------------------------------------------------
            status = "00";
            command = "00";
            sem_post(&sem);
        } // 04 reset

        if (strcmp(command,"08") == 0){
            sem_wait(&sem);
            status = "01";
            // --------------------------------------------------------
            // code
            // --------------------------------------------------------
            status = "00";
            command = "00";
            sem_post(&sem);
        } // 08 delete
        
    }
    
    return NULL;
}

void printData(){
    printf("\n\nstatus: %s",status);
    printf("\ncommand: %s",command);
    printf("\ndataSize: %d",dataSize);
    printf("\ninternalDataSize: %d",internalDataSize);

    printf("\nData: [");
    for (int i = 0; i < dataSize; i++)
    {
        printf("%s",data[i]);
    }
    printf("]");

    printf("\nInternalData: [");
    for (int i = 0; i < internalDataSize; i++)
    {
        char* d = internalData[i];
        if(d != NULL) printf("%s",d);
    }
    printf("]");
}