#include "driver.h"
#include <stdio.h>
#include <string.h>

void writeData(char* c);
char* readData();

char* data1 = "data1";
char* data2 = "data2";

int main(int argc, char const *argv[])
{
    startDriver();
    writeData(data1);
    writeData(data2);
    writeData(data1);
    writeData(data2);
    readData();
    //stopDriver();
    
    return 0;
}

void writeData(char* c){
    int done = 0;

    while (!done)
    {
        
    
        if(strcmp(command, "00") == 0){
        sem_wait(&sem);
        command = "02";

        for (int i = 0; i < dataSize; i++)
        {
            data[i] = &c[i];
        }
        }

        sem_post(&sem);
        done = 1;
    }
}
char* readData(){
    sem_wait(&sem);
    command = "01";
    sem_post(&sem);  
}