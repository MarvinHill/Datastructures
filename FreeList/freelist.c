#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Author: Marvin Hill, Felix Brodmann
 * **/

// Size of the data
#define dataSize 1000
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


//First Element of free list
Fragment initalFreeFragment = {dataSize,0,NULL};

//Free List where free Fragments are stored
Fragment headFreeList = {-1, -1, &initalFreeFragment};


//Full List where full Fragments are stored - No Element at start
Fragment headFullList = {-1, -1, NULL};



int position(int size)
{
    Fragment *frag = headFreeList.nextFragment;

    while (frag != NULL)
    {
        if (frag->size >= size )
        {
            return frag->startAdress;
        }
        
        frag = frag->nextFragment;
    }
    
    return -1;
    
}

void insert(int position, int size)
{
    
    // returns if position -1 which means that there is no more data space
    if (position == -1)
    {
        return;
    }
    
    Fragment *previousFreeFrag = &headFreeList;
    Fragment *freeFrag = headFreeList.nextFragment;

    Fragment *previousFullFrag = &headFullList;


    while (freeFrag->startAdress != position)
    {
        previousFreeFrag = freeFrag;
        freeFrag= freeFrag->nextFragment;
    }
    while (previousFullFrag->nextFragment != NULL)
    {
        if(previousFullFrag->nextFragment->startAdress > position) break;
        previousFullFrag = previousFullFrag->nextFragment;
    }
    
    if(freeFrag->size == size){
        
        previousFreeFrag->nextFragment = freeFrag->nextFragment;
        

        // Add free Fragment to full list
        freeFrag->nextFragment = previousFullFrag->nextFragment;
        previousFullFrag->nextFragment = freeFrag;
        
        // Change data freeFrag, daten = 1
        updateData(freeFrag, freeFrag->size);

        optimize();
        printAll();
        return;
    }

    if(freeFrag->size > size){
        freeFrag->startAdress += size;
        freeFrag->size -= size;
        // Add to full list new Element
        Fragment *newFullFragment = malloc(sizeof(Fragment));
        newFullFragment->size = size;
        newFullFragment->startAdress = position;
        newFullFragment->nextFragment = previousFullFrag->nextFragment;
        previousFullFrag->nextFragment = newFullFragment;

        // Update Data fullFrag und freeFrag
        updateData(freeFrag, 0);
        updateData(newFullFragment, newFullFragment->size);

        optimize();
        printAll();
        
        return;
    }
    
    fprintf(stderr, "INSERT FAILURE");
}

void remove2(int position)
{
    Fragment *previousFullListFragment = &headFullList;
    Fragment *fullListFragment = headFullList.nextFragment;

    while (fullListFragment->startAdress != position)
    {
        previousFullListFragment = fullListFragment;
        fullListFragment = fullListFragment->nextFragment;
    }
    
    previousFullListFragment->nextFragment = fullListFragment->nextFragment;

    Fragment *previousFreeListFragment = &headFreeList;
    Fragment *freeListFragment = headFreeList.nextFragment;

    if(freeListFragment == NULL){
        headFreeList.nextFragment = fullListFragment;
        fullListFragment->nextFragment = NULL;
        updateData(fullListFragment,0);
        optimize();
        printAll();
        return;
    }

    while (fullListFragment->startAdress > freeListFragment->startAdress)
    {
        previousFreeListFragment = freeListFragment;
        freeListFragment = freeListFragment->nextFragment;

        if(freeListFragment == NULL){
            previousFreeListFragment->nextFragment = fullListFragment;
            fullListFragment->nextFragment = NULL;
            updateData(fullListFragment,0);
            optimize();
            printAll();
            return;
        }
    }

    previousFreeListFragment->nextFragment = fullListFragment;
    fullListFragment->nextFragment = freeListFragment;
    
    updateData(fullListFragment,0);
    optimize();
    printAll();
}

void optimize()
{

    if (headFreeList.nextFragment == NULL)
    {
        return;
    }
    

    Fragment *frag = headFreeList.nextFragment;
    Fragment *nextFrag = frag->nextFragment;
    Fragment *toDelete = NULL;

    while(nextFrag != NULL){

    if ((frag->startAdress + frag->size ) == nextFrag->startAdress)
    {
        frag->nextFragment = nextFrag->nextFragment;
        frag->size += nextFrag->size;
        toDelete = nextFrag;    
        nextFrag = frag->nextFragment;
        free(nextFrag);
        continue;
    }
        frag = nextFrag;
        nextFrag = nextFrag->nextFragment;
    }
}

void updateData(Fragment *frag, int dataToWrite)
{
    for (int i = frag->startAdress; i < (frag->startAdress + frag->size); i++)
    {
        data[i] = dataToWrite;
    } 
}

void printReg(Fragment *frag)
{
    printf("\e[0;31m");
    char *str;
    if (frag->startAdress == -1)
    {
        str = "HEAD";

        printf("[ %s ]",  str);
    }
    else if(frag->size > 0)
    {
        str = "Fragment";
        printf(" -> [ %s | i: %d | s: %d ]", str, frag->startAdress, frag->size);
    }

    if (frag->nextFragment == NULL)
    {
        printf(" -> [NULL]");
    }
    else
    {
        printReg(frag->nextFragment);
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
        else if (d > 0)
        {
            printf("█");
        }
        else{
            printf("%d",d);
        }

        //printf(" %d ",d);

    }

    printf(" |");
}

void printAll()
{
    printf("\nFullList:  ");
    printReg(&headFullList);
    printf("\n");
    printf("FreeList:  ");
    printReg(&headFreeList);
    printData();
}