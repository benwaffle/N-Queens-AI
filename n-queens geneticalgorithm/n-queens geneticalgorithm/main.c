//
//  main.c
//  n-queens GeneticAlgorithm
//
//  Created by Ben on 11/29/12.
//  Copyright (c) 2012 benwaffle. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 8
#define POP 8

int answers[SIZE];

int length(int array[]){
    int i=0;
    while(array[i] != -1) i++;
    return i;
}

int getRand(int mod){
    return random() % mod;
}

void printArray(int array[]){
    int i;
    for(i=0; i<SIZE-1; i++) printf("(%i,%i),",i,array[i]);
    printf("(%i,%i)",SIZE-1,array[SIZE-1]);
    printf("\n");
}

int isValid(int array[], int curRow, int curCol){
    int i;
    if(length(array)){
        for(i=0;i<length(array);i++) if(i==curRow || array[i]==curCol || abs(i-curRow)==abs(array[i]-curCol)) return 0;
        return 1;
    } else return 1;
    return 0;
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

void geneticAlgorithm(){
    int population[POP][SIZE];        
    int children[POP][SIZE];          
    float mutProb = 0.05;             
    int done = 0;                     
    for(int i=0;i<POP;i++) for(int j=0;j<SIZE;j++) population[i][j] = getRand(SIZE);
    while(done == 0){
        for(int i=0;i<POP;i+=2){        
            int par1 = getRand(POP);    
            int par2 = getRand(POP);
            int split = getRand(SIZE);
            //crossover
            for(int j=0;j<split;j++){
                children[i][j] = population[par1][j];   
                children[i+1][j] = population[par2][j]; 
            }
            for(int j=split;j<SIZE;j++){     
                children[i][j] = population[par2][j];   
                children[i+1][j] = population[par1][j]; 
            }
            //mutation
            if(getRand(1000000)<=mutProb*1000000){
                int child=getRand(2);
                if(child == 0) children[i][getRand(SIZE)] = getRand(SIZE);
                else children[i+1][getRand(SIZE)] = getRand(SIZE);
            }
        }
        //check if solution
        for(int i=0;i<POP;i++){
            if(getWeight(children[i]) == 0){
                printf("solution: ");
                printArray(children[i]);
                done = 1;
            }
        }
        //children are the new population
        for(int i=0;i<POP;i++) for(int j=0;j<SIZE;j++) population[i][j] = children[i][j];
    }
}

int main(int argc, const char * argv[]){
    srandom((unsigned int)time(NULL));  //seed random
    geneticAlgorithm();
    return 0;
}

