#include <semaphore.h>

extern char* status; //  00 ready, 01 busy, 02 error
extern char* command; // 00 idle, 01 read, 02 write, 04 reset, 08 delete
#define dataSize 20
extern char* data[dataSize];
extern sem_t sem;
extern sem_t printMutex;

extern void startDriver();
extern void stopDriver();
extern void printData();