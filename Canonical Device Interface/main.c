#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "driver.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void writeData(char* c);
char* readData();

char* data1 = "AA";
char* data2 = "BB";

int main(int argc, char const *argv[])
{
    startDriver();
    writeData(data1);
    writeData(data2);
    writeData(data1);
    writeData(data2);
    readData();
    stopDriver();
    
    return 0;
}

void writeData(char* c){

    sem_wait(&sem);

        for (int i = 0; i < dataSize; i++)
        {
            data[i] = "";
        }
        
        for (int i = 0; i < dataSize; i++)
        {
            data[i] = c;
        }

        command = "02";

        usleep(500);
        
        sem_wait(&printSemt);
        printData();
        sem_post(&printSemt);

    sem_post(&sem);
    
}
char* readData(){
    sem_wait(&sem);
    command = "01";
    sem_post(&sem);  
}