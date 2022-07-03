
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void writeData(char* data, int size);  
void readData(); // 20 Byte
void delete();
void reset();
void startDriver();
void stopDriver();
void setStatus(char ns);
void setCommand(char nc);
void printData();

extern sem_t end;
extern sem_t sem;


// Constants
#define dataSize 20
#define internalDataSize 1024

//Variables
static char internalData[internalDataSize];
static int ind = 0;

//Registries
extern char data[dataSize];
extern char status;
extern char command;

 

