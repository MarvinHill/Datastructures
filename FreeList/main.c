#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>



int main(int argc, char const *argv[])
{
    int elemente[10];

    elemente[0] = position(50);
    insert(elemente[0], 50);
    elemente[1] = position(20);
    insert(elemente[1], 20);
    elemente[2] = position(20);
    insert(elemente[2], 20);
    elemente[3] = position(20);
    insert(elemente[3], 20);
    remove2(elemente[2]);
    remove2(elemente[3]);
    remove2(elemente[1]);
    remove2(elemente[0]);
    

    return 0;
    
}
