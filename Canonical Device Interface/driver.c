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
#define internalDataSize 1024
char* internalData[internalDataSize];

pthread_t driver;
int threadRunning = 0;
int iret1;

int i = 0;
char *status = "00";
char *command = "00";
char* data[dataSize];
sem_t sem;
sem_t printMutex;

void startDriver()
{
    sem_init(&sem, 0, 1);
    sem_init(&printMutex, 0, 1);
    iret1 = pthread_create(&driver, NULL, (void *)&threadFunc, NULL);
}

void *threadFunc(void *v)
{
    sem_wait(&printMutex);
    printf("\nstarted running");
    sem_post(&printMutex);  
    
    int index = 0;

    while (1)
    {
        // 00 idle, 01 read, 02 write, 04 reset, 08 delete
        if (strcmp(command, "00") == 0)
        {
            continue;
        }

        if (strcmp(command, "01") == 0)
        {
            sem_wait(&sem);
            
                if (index >= (dataSize-1))
                {
                    for (int i = dataSize; i > -1; i--)
                    {
                        data[i] = internalData[index];
                        internalData[index] = NULL;
                        index--;
                    }
                    status = "00"; 
                    command = "00";
                    printData();
                                        
                }
                else
                {
                    status = "02"; // Set error when max is exceeded
                }
                  
            sem_post(&sem);
        }

        if (strcmp(command, "02") == 0)
        {
            sem_wait(&sem);
            status = "01"; // Set busy
            for (int i = 0; i < dataSize;)
            {
                if (index > internalDataSize)
                {
                    status = "02"; // Set error when max is exceeded
                    sem_post(&sem);
                    break;
                }
                internalData[index] = data[i];
                data[i] = NULL;
                index++;
                i++;
            }
            printData();
            status = "00"; 
            command = "00";
            sem_post(&sem);
        }

        if (strcmp(command, "04") == 0)
        {
            sem_wait(&sem);
            index = 0; // reset, data stays the same
            status = "00"; 
            command = "00"; 
            sem_post(&sem);
        }

        if (strcmp(command, "08") == 0)
        { 
            sem_wait(&sem);
            status = "01"; 
            while (index > (-1))
            {
                internalData[index] = 0;
                index--;
            }
            status = "00"; 
            command = "00";
            sem_post(&sem);  
            printData();        
        }

        
    }
    return NULL;
}

void printData(){
    sem_wait(&printMutex);
    printf("\n\n|status: %s",status);
    printf("\n|command: %s",command);
    printf("\n|dataSize: %d",dataSize);
    printf("\n|dataSize: %d",internalDataSize);

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
        else printf("-");
    }
    printf("]");
    sem_post(&printMutex);  
}