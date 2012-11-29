#include <stdio.h>
#include <stdlib.h>
#define SIZE 8

int answers[SIZE] = {-1,-1,-1,-1,-1,-1,-1,-1};
//answers[row] = column;

int length(int array[]){
    int i=0;
    while(array[i] != -1) i++;
    return i;
}

void printArray(int array[]){
    static int num = 0;
    num++;
    printf("#%i: ",num);
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

void bruteForce(int array[], int nextrow, int startval){
    if(nextrow == SIZE){                                        //if we're past the last row
        //this can probably be cleaned up
        printArray(array);                                      //print the array
        array[nextrow-1] = -1;                                  //reset the queen in last row
        int nextstartval = array[nextrow-2]+1;                  //save the next column in second to last row
        array[nextrow-2] = -1;                                  //reset the queen in 2nd to last row
        if(nextstartval == SIZE){                               //if the queen is in (n-3,n-1)
            nextstartval = array[nextrow-3]+1;                      //save the queen in 3rd to last row
            array[nextrow-3] = -1;                                  //reset the 3rd to last row
            bruteForce(array,nextrow-3, nextstartval);              //recurse starting with the queen in 3rd to last row
        } else {
            bruteForce(array,nextrow-2, nextstartval);          //else recurse starting with the queen in the 2nd to last row
        }
    } else {                                                    //still can place pieces
        int i;
        for(i=startval;i<SIZE;i++){                             //for each of the remaining columns
            if(isValid(array, nextrow, i) == 1){                //if a queen in the current column i is valid
                array[nextrow] = i;                             //place it
                bruteForce(array,nextrow+1,0);                  //recurse with the new board
            } else if (i==SIZE-1) {
                int nextstartval = array[nextrow-1]+1;
                if(nextstartval >= SIZE){
                    nextstartval = array[nextrow-2]+1;
                    array[nextrow-1] = -1;
                    array[nextrow-2] = -1;
                    bruteForce(array, nextrow-2, nextstartval);
                } else {
                    array[nextrow-1] = -1;
                    bruteForce(array, nextrow-1, nextstartval);
                }
            }
        }
    }
}

int main(){
    bruteForce(answers, 0, 0);
    return 0;
}