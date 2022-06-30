#include <unistd.h>
#include "driver.h"
#include <stdio.h>
#include <string.h>
#include <time.h>

void writeData(char c);
void readData();

char data1 = 1;
char data2 = 4;

int main(int argc, char const *argv[])
{
    startDriver();
    writeData(data1);
    writeData(data2);

    stopDriver();
    

    return 0;
}

void writeData(char c){


    sem_wait(&sem);

        for (int i = 0; i < dataSize; i++)
        {
            data[i] = '\0';
        }
        
        for (int i = 0; i < dataSize; i++)
        {
            data[i] = c;
        }

        command = "02";


    sem_post(&sem);
    
}

void readData(){
    sem_wait(&sem);
    command = "01";
    sem_post(&sem);  
}