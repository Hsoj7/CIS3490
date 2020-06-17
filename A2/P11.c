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

char *trim(char *userInput);

int main(){
  FILE *fp;
  struct timeb start, end;
  int milSeconds = 0;
  char *fileName1 = "data_1.txt";
  unsigned long i = 0, j = 0;
  char readChar;
  char *buffer = NULL;
  char *eachNumber = NULL;
  unsigned long integerNum = 0;
  unsigned long arrayOfNums[50001];
  float seconds = 0.0;
  long inversionCounter = 0;

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

  i = 0;
  while( (eachNumber = strsep(&buffer, " ")) != NULL){
    trim(eachNumber);
    integerNum = strtoul(eachNumber, NULL, 10);
    arrayOfNums[i] = integerNum;
    i++;
  }

  printf("Running P11... \n");

  for(i = 0; i < 50000; i++){
    for(j = 0; j < 50000; j++){
      if(arrayOfNums[i] > arrayOfNums[j] && i < j){
        inversionCounter++;
      }
    }
  }

  printf("Inversion counter = %ld\n", inversionCounter);

  fclose(fp);
  free(buffer);

  ftime(&end);

  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;

  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  return 0;
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
