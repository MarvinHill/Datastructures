#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Author: Marvin Hill, Felix Brodmann
 * **/

// Size of the data
#define dataSize 100
// Debug mode for application shows visual representation of data
#define printMode 1
// Data Array
int data[dataSize];
// void printAll();
void printReg();
// Optimize free Spaces in List
void optimize();
// Update Data Array
void updateData();
void printData();
void printAll();

typedef struct Fragment Fragment;
typedef struct Fragment
{
    int size;
    int startAdress;
    Fragment *nextFragment;
} Fragment;

// Virtual Harddrive
// int data[dataSize];
Fragment head = {-1, -1, NULL};

int position(int size)
{
    // Find next free Fragment that is big enought
    // Optimize remaining Fragments, function optimize()

    Fragment *frag = &head;

    if (size > dataSize)
    {
        return -1;
    }

    if (head.nextFragment == NULL)
    {
        Fragment *nextValue = malloc(sizeof(Fragment));

        nextValue->nextFragment = NULL;
        nextValue->size = dataSize;
        nextValue->startAdress = 0;

        head.nextFragment = nextValue;

        return 0;
    }

    while (frag->nextFragment != NULL)
    {
        frag = frag->nextFragment;
        if (frag->size >= size)
        {
            return frag->startAdress;
        }
    }
    printf("\nKein Platz mehr!\n");
    return -1;
}

void insert(int position, int size)
{
    // if Fragment matching the position not hasData then insert it
    // if free space is big enought
    // if Fragment not at start of free Fragment then add a Fragment in front
    // if Fragment not completely fills the free Fragment add a Fragment behind the data

    // Optimize remaining Fragments, function optimize()

    if (position != -1 == size > 0)
    {

        Fragment *frag = &head;
        while (frag->startAdress != position)
        {
            frag = frag->nextFragment;
        }

        printf("\nInsert Position: %d Size: %d", position, size);

        Fragment *nextFrag = frag->nextFragment;

        if (frag->size == size)
        {
            frag->size = 0;
            updateData(frag);
        }
        else if (frag->size > size)
        {

            Fragment *newElement = malloc(sizeof(Fragment));
            newElement->nextFragment = nextFrag;
            newElement->size = frag->size - size;
            newElement->startAdress = frag->startAdress + size;

            frag->size = 0;
            updateData(frag);
            frag->nextFragment = newElement;
            updateData(frag->nextFragment);
        }

        printAll();
        printf("\n");
    }
    else
    {
        return;
    }

    // Found Fragment
}
void freee(int position)
{

    if (position != -1 && position < dataSize)
    {
        Fragment *frag = head.nextFragment;

        while (frag->startAdress != position)
        {
            frag = frag->nextFragment;
        }

        frag->size = frag->nextFragment->startAdress - frag->startAdress;

        printf("\nFree from position: %d to %d", frag->startAdress, frag->startAdress + frag->size);
        updateData(frag);
        optimize();
        printAll();
    }
    else
    {
        printf("\nFree failed");
    }
    // Print data
    // printAll();
    // Print registry
    printf("\n");
}

void optimize()
{
    Fragment *frag = head.nextFragment;
    Fragment *nextFrag = frag->nextFragment;

    while (frag->nextFragment != NULL)
    {
        if(frag->size > 0 && nextFrag->size > 0)
        {
            frag->size = frag->size + frag->nextFragment->size;
            frag->nextFragment = nextFrag->nextFragment;
            nextFrag->nextFragment = NULL;

            free(nextFrag);

            continue;

        }

        frag = nextFrag;
        nextFrag = frag->nextFragment;
    }
    

}

void updateData(Fragment *frag)
{
    if (frag->size == 0)
    {
        if (frag->nextFragment != NULL)
        {
            for (int i = frag->startAdress; i < frag->nextFragment->startAdress; i++)
            {
                data[i] = (frag->nextFragment->size - frag->startAdress);
            }
        }

        else
        {
            for (int i = frag->startAdress; i < dataSize; i++)
            {
                data[i] = ((dataSize - 1) - frag->startAdress);
            }
        }
    }
    else
    {
        for (int i = frag->startAdress; i < frag->startAdress + frag->size; i++)
        {
            data[i] = 0;
        }
    }
}

void printReg(Fragment *frag)
{
    printf("\n\e[0;31m");
    char *str;
    if (frag->startAdress == -1)
    {
        str = "head";

        printf("[ad: %p st: %s n: %p]", frag, str, &*frag->nextFragment);
    }
    else if(frag->size == 0)
    {
        str = "data";

        printf("[ad: %p ind: %d s: %d st: %s n: %p]", frag, frag->startAdress, frag->size, str, &*frag->nextFragment);
    }
    else
    {
        str = "free";
        printf("[ad: %p ind: %d s: %d st: %s n: %p]", frag, frag->startAdress, frag->size, str, &*frag->nextFragment);
    }

    if (frag->nextFragment != NULL)
    {
        printf(" -> ");
        printReg(frag->nextFragment);
    }
    else
    {
        printf(" -> [NULL]");
    }

    printf("\e[0m");
}

void printData()
{
    printf("\nStorage: | ");

    for (int i = 0; i < dataSize; i++)
    {
        int d = data[i];

        if (d == 0)
        {
            printf("▂");
        }
        if (d > 0)
        {
            printf("█");
        }
    }

    printf(" |");
}

void printAll()
{
    printReg(&head);
    printData();
}