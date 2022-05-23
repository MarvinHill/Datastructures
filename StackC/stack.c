#include <stdio.h>
#include "stack.h"

int elements[100];
int size = 100;
int top = -1;

void push(int val){
    
    if(top < (size -1)){
        top++;
        elements[top] = val;
    }
    else{
        fprintf(stderr,"ERROR: Size 100 of stack exeeded when adding value %d\n", val);
    }  
};

int pop(){
    if(top > -1){
        int retTemp = elements[top];
        elements[top] = NULL;
        top--;
        return retTemp;
    }
    else{
        fprintf(stderr, "ERROR: Stack is empty, NULL return instead\n");
        return NULL;
    }  
};

int peek(){
    if(top > -1){
        return elements[top];
    }
    else{
        fprintf(stderr, "ERROR: Stack is empty, NULL return instead\n");
        return NULL;
    } 
};
