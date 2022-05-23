#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    //printf("%d",position(50));
    insert(position(50), 50);
    insert(position(20), 20);
    insert(position(20), 20);
    insert(position(20), 20);
    freee(0);
    freee(70);
    freee(90);
    freee(50);
    //printf("\n%d",position(20));
    insert(position(20), 20);
    return 0;
}
