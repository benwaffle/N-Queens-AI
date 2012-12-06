//
//  main.c
//  n-queens StochasticBeamSearch
//
//  Created by Ben on 12/6/12.
//  Copyright (c) 2012 benwaffle. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 8
#define k 5

//we have K states
//look at all successors of each state (k * SIZE * SIZE-1) = k * 56
//implement a weighted probability distribution, so that the probability of choosing a state is proportional to fitness 28*numSuccessors

int answers[k][SIZE] = {};
//answers[row] = column;

int getRand(int mod){
    return random() % mod;
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
    return weight; //0 is best, 28 is worst
}

void stochBeamSearch(){
    int state,i,j;
    for(i=0;i<k;i++){
        if(getWeight(answers[i]) == 28){
            printf("solution: ");
            printArray(answers[i]);
            exit(0);
        }
    }
    for(i=0;i<k;i++) for(j=0;j<SIZE;j++) answers[i][j] = getRand(SIZE);     //fill K boards randomly
    //weighted prob arrays
    int weightProb[3][56*28*k]; //{kstate,row,column}
    /* kstate - which k is it from
     row - which row are we dealing with
     col - which col to switch to */
    int wpl = 0;
    for(state=0;state<k;state++){   //for each state
        int row;
        for(row=0;row<SIZE;row++){  //for each row
            int col;
            for(col=0;col<SIZE;col++){  //for each col
                if (answers[state][row] != col){   //not including current state
                    int origcol = answers[state][row];
                    answers[state][row] = col;  //change state
                    int w = getWeight(answers[state]);
                    for(i=0;i<w;i++){
                        weightProb[0][wpl] = state;
                        weightProb[1][wpl] = row;
                        weightProb[2][wpl] = col;
                        wpl++;
                    }
                    answers[state][row] = origcol;
                }
            }
        }
    }
    for(i=0;i<k;i++){
        int n = getRand(wpl);
        //          state k             row             col
        answers[weightProb[0][n]][weightProb[1][n]] = weightProb[2][n];
        printf("recursing\n");
        stochBeamSearch();
    }
}

int main(int argc, const char * argv[]){
    srandom((unsigned int)time(NULL));
    for(int i=0;i<k;i++) for(int j=0;j<SIZE;j++) answers[i][j] = getRand(SIZE);
    stochBeamSearch();
    return 0;
}