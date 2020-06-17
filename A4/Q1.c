/*
Name: Joshua Stone
#; 1013900
mail: jstone04@uoguelph.ca
Assignment: 4
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct binSearchTree{
  char key[20];
  int frequency;
  double probability;
  struct binSearchTree *leftSubTree, *rightSubTree;
};

void findOrder(int R[605][605], int left, int right);
void insert(struct binSearchTree *ptr, struct binSearchTree *temp);
void printTree(struct binSearchTree *temp);
void search(char userInput[20]);
//pointer to the root of the tree
struct binSearchTree *root = NULL;

int main(){
  FILE *fp = NULL;
  char fileArray[601][20];
  char fileString[20];
  char fileName[20] = "data_7.txt";
  char tempString[20];
  int frequencyArr[601];
  int i = 0, j = 0, k = 0, d = 0, s = 0, fileArrayTracker = 0, freqTracker = 0;
  int holder = 0;
  int newWord = 1;
  //alrogithm stuff
  double C[605][605];
  int R[605][605];
  double minVal = 0.0, sum = 0.0;
  int minKVal = 0;
  //set all frequency vals to 1
  for(i = 0; i < 600; i++){
    frequencyArr[i] = 1;
  }

  fp = fopen(fileName, "r");
  //read in each word from the data_7.txt file
  fileArrayTracker = 0;
  while( fscanf(fp, "%s", fileString) == 1 ){
    for(i = 0; i < 600; i++){
      //determines if the string is unique
      if(strcmp(fileArray[i], fileString) == 0){
        newWord = 0;
        freqTracker = i;
        break;
      }
    }
    //if its new, throw it into the 2d array of all string
    if(newWord == 1){
      strcpy(fileArray[fileArrayTracker], fileString);
      fileArrayTracker++;
    }
    //otherwise, increase the string's frequency counter
    else{
      frequencyArr[freqTracker]++;
    }
    newWord = 1;
  }
  //sorting the arrays using bubble sort
  for(i = 0; i < 600; i++){
    for(j = 0; j < 599 - i; j++){
      if( strcmp(fileArray[j], fileArray[j+1]) > 0 ){
        strcpy(tempString, fileArray[j+1]);
        strcpy(fileArray[j+1], fileArray[j]);
        strcpy(fileArray[j], tempString);

        holder = frequencyArr[j+1];
        frequencyArr[j+1] = frequencyArr[j];
        frequencyArr[j] = holder;
      }
    }
  }
  //creates and initializes the probability array
  double P[602];
  P[0] = 0.0;
  for(i = 1; i < 601; i++){
    P[i] = (double) frequencyArr[i-1] / 2045;
  }
  P[601] = 0.0;
  //initializes the main table and R table to 0
  for(i = 0; i < 601; i++){
    for(j = 0; j < 601; j++){
      C[i][j] = 0.0;
      R[i][j] = 0;
    }
  }
  //Algorithm from the txtbook:
  for(i = 1; i <= 600; i++){
    C[i][i-1] = 0.0;
    C[i][i] = P[i];
    R[i][i] = i;
  }
  C[601][600] = 0.0;
  j = 0;
  for(d = 1; d <= 599; d++){
    for(i = 1; i <= (600 - d); i++){
      j = (i + d);
      minVal = 1000000.0;
      for(k = i; k <= j; k++){
        if( (C[i][k-1] + C[k+1][j]) < minVal){
          minVal = (double) (C[i][k-1] + C[k+1][j]);
          minKVal = k;
        }
      }
      R[i][j] = minKVal;
      sum = P[i];
      for(s = i + 1; s <= j; s++){
        sum += P[s];
      }
      C[i][j] = (double)minVal + sum;
    }
  }
  //print tables out
  printf("Main Table - Top Left\n");
  for(i = 0; i < 5; i++){
    for(j = 0; j < 5; j++){
      printf("%.4f\t", C[i][j]);
    }
    printf("\n");
  }
  printf("\nMain Table - Top Right\n");
  for(i = 0; i < 5; i++){
    for(j = 596; j < 601; j++){
      printf("%.4f\t", C[i][j]);
    }
    printf("\n");
  }
  printf("\nR Table - Top Left\n");
  for(i = 0; i < 5; i++){
    for(j = 0; j < 5; j++){
      printf("%d\t", R[i][j]);
    }
    printf("\n");
  }
  printf("\nR Table - Top Right\n");
  for(i = 0; i < 5; i++){
    for(j = 596; j < 601; j++){
      printf("%d\t", R[i][j]);
    }
    printf("\n");
  }

  int choice = 0;
  printf("Do you wish to print insert sequence?\nNo = 0, Yes = 1\n");
  scanf("%d", &choice);
  if(choice == 1){
    int left = 1;
    int right = 600;
    findOrder(R, left, right);
  }

  fclose(fp);
  return 0;
}
//function recursively finds the next node to insert
//I could not figure out how to do the insertion :(
void findOrder(int R[605][605], int left, int right){
  int tableVal = 0;

  if(left <= right){
    tableVal = R[left][right];
    printf("%d, ", tableVal);
    findOrder(R, left, tableVal - 1);
    findOrder(R, tableVal + 1, right);
  }
}
