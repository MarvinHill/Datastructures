#include "driver.h"

char* data1 = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"; // 42 Bytes
char* data2 = "BBBBBBBBBBBBBBBBBBBB";


int main(int argc, char const *argv[])
{
    startDriver();
    writeData(data2,20);
    reset();
    for (int i = 0; i < 3; i++)
    {
        writeData(data1,42);
        writeData(data2,20);
    }

    delete();

    stopDriver();
    return 0;
}

void setStatus(char ns){
   if(status != 2){
   status = ns; 
   }
}
void setCommand(char nc){
    command = nc;
}

void writeData(char* inData, int size){
    usleep(100); // Remove printing artifacts
    printf("\nWRITE DATA: [");
    
    for (int i = 0; i < dataSize; i++)
        {
            data[i] = *inData;
            printf("%c",data[i]);
            inData++;
        }
     printf("]");
   
    setCommand(2);
    setStatus(1);
    sem_post(&sem);
    while(status != 0){
        usleep(10);
    }
}

void readData(){
    usleep(100); // Remove printing artifacts

    setStatus(1);
    setCommand(1);
    
    sem_post(&sem);

    while(status != 0){
        usleep(10);
    }
    
    printf("\nREAD DATA: [");
    for (int i = 0; i < dataSize; i++)
    {
        printf("%c",data[i]);
        data[i] = 0;
    }
    printf("]");
    
} 

void delete(){
    printf("\nDELETE");
    setStatus(1);
    setCommand(8);
    sem_post(&sem);
    while( status != 0){
        usleep(10);
    }
}
void reset(){
    printf("\nRESET");
    setStatus(1);
    setCommand(4);
    sem_post(&sem);
    while(status != 0){
        usleep(10);
    }
}