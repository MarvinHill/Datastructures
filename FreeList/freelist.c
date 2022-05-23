#include "freelist.h"
#include <stdio.h>
#include <stdlib.h>
//Size of the data
#define dataSize 1000 
//Debug mode for application shows visual representation of data
#define printMode 2

//void printData();
void printReg();
//Optimize free Spaces in List
void optimize();

/** 
 * Author: Marvin Hill, Felix Brodmann
 * **/

typedef struct Fragment Fragment;
typedef struct Fragment { 
   int size;
   int startAdress;
   Fragment *nextFragment;
   int hasData;
} Fragment;




// Virtual Harddrive
//int data[dataSize];
Fragment head = {-1,-1,NULL,0};

int position(int size){
    //Find next free Fragment that is big enought
    //Optimize remaining Fragments, function optimize()

    Fragment *frag = &head;

    if(size > dataSize){
            return -1;
        }

    if(head.nextFragment == NULL){
        Fragment *nextValue = malloc(sizeof(Fragment));

        nextValue->hasData = 0;
        nextValue->nextFragment = NULL;
        nextValue->size = dataSize;
        nextValue->startAdress = 0;

        head.nextFragment = nextValue;
        
        return 0;
    }

    while(frag->nextFragment != NULL){
        frag = frag->nextFragment;
        if(frag->hasData == 0 && frag->size >= size){
            return frag->startAdress;
        }
    }
    return -1;

    }
 

void insert(int position, int size){
    //if Fragment matching the position not hasData then insert it
    //if free space is big enought
        //if Fragment not at start of free Fragment then add a Fragment in front
        //if Fragment not completely fills the free Fragment add a Fragment behind the data

    //Optimize remaining Fragments, function optimize()

    if(position != -1){

        Fragment *frag = &head;
        while(frag->startAdress != position){
            frag = frag->nextFragment;
        }

        printf("\nInsert Position: %d ",position);

        Fragment *nextFrag = frag->nextFragment;
        
        if(frag->size == size){
            frag->hasData = 1;
        }
        else if (frag->size > size){
            frag->hasData = 1;

            Fragment *newElement = malloc(sizeof(Fragment));
            newElement->hasData=0;
            newElement->nextFragment = nextFrag;
            newElement->size = frag->size - size;
            newElement->startAdress = frag->startAdress + size;

            frag->size = size;
            frag->nextFragment = newElement;
            
        }
        else{
            printf("\nDATAFAILURE");
        }

        printf("    ");
        printReg(&head);
        optimize();



    }
    else{
            printf("\nDATAFAILURE-----------------------------------------------------------------------------------------------------------------");
        }
    

    //Found Fragment
}
void freee(int position){

    if(position != -1){
        Fragment *frag = head.nextFragment;
        Fragment *prev = &head;

        while(frag->startAdress != position){
            prev = frag;
            frag = frag->nextFragment;
        }

        frag->hasData = 0;

        printf("\nFree Position: %d", position);
        printf("    ");
        printReg(&head);

        optimize();


    }
    
    
    //Print data
    //printData();
    //Print registry
    
    
}

void optimize(){
    
    Fragment *frag = head.nextFragment;

    while(frag->nextFragment != NULL){

        
        if(frag->hasData == 0 && frag->nextFragment->hasData == 0){
            Fragment *toDelete = frag->nextFragment;
            frag->nextFragment = toDelete->nextFragment;
            frag->size = frag->size + toDelete->size;
            free(toDelete);
            
            
            printf("\nOptimized: %d",frag->startAdress);
            printf("    ");
            printReg(&head);
            continue;

        }
        //printf("\nround");
        frag = frag->nextFragment;
    }

    
    

}

void printReg(Fragment *frag){

    if(printMode == 1){
         char *str;
    if(frag->hasData == 1){
        str = "has data";
        printf("[i: %d s: %d st: %s]",frag->startAdress,frag->size,str);
    }
    else if(frag -> startAdress == -1){
        str = "is head";
        printf("[i: %d s: %d st: %s]",frag->startAdress,frag->size,str);
    }
    else{
        str = "is free";
        printf("[i: %d s: %d st: %s]",frag->startAdress,frag->size,str);
    }
    
    
    if(frag->nextFragment != NULL){
        printf(" -> ");
        printReg(frag->nextFragment);
    }
    else{
        printf(" -> [end]");
    }
    }
    else if(printMode == 2){
        char *str;
        if(frag->hasData == 1){
            printf("[");
            for (int i = 0; i < frag->size; i++)
            {
                if(i%10 == 0) printf("|");
            }
         
            printf("]");
        }
        else if(frag -> startAdress == -1){
            printf("[head]");
        }
        else{
            printf("[");
            for (int i = 0; i < frag->size; i++)
            {
                if(i%10 == 0) printf(".");
            }
         
            printf("]");
        }
    
    
        if(frag->nextFragment != NULL){
            printf(" -> ");
            printReg(frag->nextFragment);
        }
        else{
            printf(" -> [end]");
        }
    }
   
}

/*void printData(){
    if(printMode){
            for (int i = 0; i < dataSize; i++)
            {
                if (data[i] == 0)
                {
                    printf(".");
                }
                else if  (data[i] > 0) {
                    printf("|");
                }
                else{
                    fprintf(stderr,"DataFailure");
                }
                
            }
            printf("\n");
    } 
}*/