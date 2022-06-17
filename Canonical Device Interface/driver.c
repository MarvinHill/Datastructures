#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include "driver.h";
#include <pthread.h>;


// Registries, char size = 1 Byte 
char status; // 01 busy, 00 ready, 02 error
char command; // 00 idle, 01 read, 02 write, 04 reset, 08 delete
char data[20];

//Driver
char internalData[1024];

void startDriver(){

}

char[] readData()

void writeData(char[])

void reset()

void delete()