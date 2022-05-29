#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char const *argv[])
{
    /*
    int zahl = 0;
    int posL[1000];
    int index = 0;
    do
    {
        srand(time(NULL)%100);
        zahl = (rand() % 1000) + 1;

        int pos = position(zahl);
        if (pos == -1) break;

        posL[index] = pos;
        index ++;
        insert(pos,zahl);
        
    } while (zahl != -1);
    
    */

    
    //printf("%d",position(50));
    insert(position(50), 50);
    insert(position(20), 20);
    insert(position(20), 20);
    insert(position(20), 20);
    freee(0);
    //freee(50);
    freee(70);
    //printf("\n%d",position(20));
    //insert(position(20), 20);
    return 0;
    
}
