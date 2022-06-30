
#include <semaphore.h>
void writeData(char* data);  
char* readData(); // 20 Byte
char* getStatus(); // String
void startDriver();
void stopDriver();
extern sem_t end;