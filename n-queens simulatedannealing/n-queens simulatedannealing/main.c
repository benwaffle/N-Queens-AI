//
//  main.c
//  n-queens simulatedannealing
//
//  Created by Ben on 11/28/12.
//  Copyright (c) 2012 benwaffle. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define e 2.718281828459045 //double
#define SIZE 8

int answers[SIZE] = {};
//answers[row] = column;

int getRandOne(){
    return (random()%1000)/1000;
}

void printArray(int array[]){
    int i;
    for(i=0; i<SIZE-1; i++) printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",SIZE-1,array[SIZE-1]);
    printf("\n");
}

int getWeight(int array[]){
    int weight = 0;
    int queen;
    for(queen=0;queen<SIZE;queen++){    //for each queen
        int nextqueen;
        for(nextqueen=queen+1;nextqueen<SIZE;nextqueen++){        //for each of the other queens (nextqueen = queen to avoid counting pairs twice)
            if(array[queen] == array[nextqueen] || abs(queen-nextqueen)==abs(array[queen]-array[nextqueen])){   //if conflict
                weight++;
            }
        }
    }
    return weight;
}

void simulatedAnnealing(){
    int temp = 4000;
    int sch = .99;
    int k;
    int dw;
    int successor[SIZE];
    for(k=0;k<170000;k++){  //roughly even distribution of "took to long" and solution with this k value
        temp *= sch;
        int i;
        for(i=0;i<SIZE;i++) successor[i] = answers[i];
        successor[random()%SIZE] = random()%SIZE;
        dw = getWeight(successor) - getWeight(answers);
        if(dw > 0 || getRandOne() < pow(e,-dw*temp)){
            for(i=0;i<SIZE;i++) answers[i] = successor[i];
        }
        if(getWeight(answers) == 0){
            printf("solution: ");
            printArray(answers);
            exit(0);
        }
    }
    printf("took too long");
}

int main(int argc, const char * argv[])
{
    srandom((unsigned int)time(NULL));
    int i;
    for(i=0;i<SIZE;i++) answers[i] = random()%SIZE;
    simulatedAnnealing();
    return 0;
}