
#include <semaphore.h>
void writeData(char* data);  
char* readData(); // 20 Byte
char* getStatus(); // String
void startDriver();
void stopDriver();
extern sem_t end;

// Constants
#define dataSize 20
#define internalDataSize 1024

//Variables
static char data[dataSize];
static char internalData[internalDataSize];
static int ind = 0;

//Registries
char* status = "00";
char* command = "00";