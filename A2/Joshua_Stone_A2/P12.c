/*
Name: Joshua Stone
ID: 1013900
Email: jstone04@uoguelph.ca
Date: February 11, 2019
Assign 2
*/

#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>
#include <sys/timeb.h>

//prototypes
unsigned long mergeArrays(unsigned long mergeArray[], unsigned long arrayOfNums[50001], long center, long leftIndex, long totalNums);
unsigned long mergesortAlgorithm(unsigned long mergeArray[], unsigned long arrayOfNums[50001], long leftIndex, long totalNums);
char *trim(char *userInput);

int main(){
    char *buffer;
    char *fileName1 = "data_1.txt";
    char *eachNumber;
    char readChar;
    FILE *fp;
    unsigned long i = 0;
    unsigned long integerNum = 0;
    unsigned long arrayOfNums[50001];
    unsigned long *mergeArray = NULL;
    struct timeb start, end;
    int milSeconds = 0;
    float seconds = 0.0;
    unsigned long mainInversionCounter = 0;
    long totalNums = 50000;

    ftime(&start);

    buffer = malloc(550000);

    fp = fopen(fileName1, "r");

    while(!feof(fp)){
      readChar = fgetc(fp);
      if(feof(fp)) break;
      if(readChar == '\n'){
        readChar = ' ';
      }
      buffer[i] = readChar;
      i++;
    }

    /*String separate based on whitespace*/
    i = 0;
    while( (eachNumber = strsep(&buffer, " ")) != NULL){
      trim(eachNumber);
      integerNum = strtoul(eachNumber, NULL, 10);
      arrayOfNums[i] = integerNum;
      i++;
    }

    fclose(fp);
    free(buffer);

    /*Starts the mergeSort*/
    mergeArray = malloc(sizeof(unsigned long) * totalNums);
    mainInversionCounter = mergesortAlgorithm(mergeArray, arrayOfNums, 0, totalNums - 1);

    printf("Running P12...\n");
    printf("Inversion Counter = %lu\n", mainInversionCounter);

    ftime(&end);

    /*Find run time*/
    milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
    seconds = milSeconds / 1000.0;

    printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

    return 0;
}

/*Recursively splits arrayOfNums*/
unsigned long mergesortAlgorithm(unsigned long mergeArray[], unsigned long arrayOfNums[50001], long leftIndex, long totalNums){
  long center = 0;
  unsigned long inversionCounter = 0;

  /*totalNums, or rightindex is greater than left index*/
  if (totalNums > leftIndex){
    center = (totalNums + leftIndex)/2;
    inversionCounter = mergesortAlgorithm(mergeArray, arrayOfNums, leftIndex, center);
    inversionCounter += mergesortAlgorithm(mergeArray, arrayOfNums, center + 1, totalNums);
    inversionCounter += mergeArrays(mergeArray, arrayOfNums, center + 1, leftIndex, totalNums);
  }

  return inversionCounter;
}

/*Brings arrays back together*/
unsigned long mergeArrays(unsigned long mergeArray[], unsigned long arrayOfNums[50001], long center, long leftIndex, long totalNums){
  unsigned long inversionCounter = 0;
  long i = leftIndex, j = center, k = leftIndex;

  /*Merge back arrays*/
  while (i < center && j < totalNums + 1){
    if(arrayOfNums[i] <= arrayOfNums[j]){
      mergeArray[k] = arrayOfNums[i];
      i++;
      k++;
    }
    else{
      mergeArray[k] = arrayOfNums[j];
      j++;
      k++;
      inversionCounter += center - i;
    }
  }

  //thows in any extra elemnts from left side of broken array
  while (i < center){
    mergeArray[k] = arrayOfNums[i];
    i++;
    k++;
  }

  //throws in any extra elements from right side of broken array
  while (j < totalNums + 1){
    mergeArray[k] = arrayOfNums[j];
    j++;
    k++;
  }

  //Throws all elemnts in mergearray back into arrayOfNums
  i = leftIndex;
  while(i < totalNums + 1){
    arrayOfNums[i] = mergeArray[i];
    i++;
  }

  return inversionCounter;
}

/*Just a helper function to take off trailing whitespace*/
char *trim(char *userInput){
  char *endOfString;
  int length = strlen(userInput) - 1;

  endOfString = userInput + length;

  while(endOfString > userInput && isspace(*endOfString)){
    endOfString = endOfString - 1;
  }

  *(endOfString+1) = '\0';

  return userInput;
}
