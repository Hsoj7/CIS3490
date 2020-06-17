#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/timeb.h>

long numShifts = 0;

int main(){
  FILE *fp;
  struct timeb start, end;
  char *fileName = "data_5.txt";
  char userString[500];
  char readChar;
  char *fileString = NULL;
  long unsigned i = 0;
  int j = 0;
  int length = 0;
  int lengthFile = 0;
  int milSeconds = 0;
  int occurences = 0;
  float seconds = 0.0;

  fp = fopen(fileName, "r");

  //get user input
  printf("Enter a string to find pattern in data_5.txt\n");
  fgets(userString, 1000, stdin);
  printf("\n");

  //turn all new lines into string terminators
  for(i = 0; i < strlen(userString); i++){
    if(userString[i] == '\n'){
      userString[i] = '\0';
    }
  }

  length = strlen(userString);

  ftime(&start);

  fileString = malloc(4000000);

  //read file into array
  i = 0;
  while(!feof(fp)){
    readChar = fgetc(fp);
    fileString[i] = readChar;
    i++;
  }

  //set end of the string to null terminator
  lengthFile = strlen(fileString);
  fileString[lengthFile - 1] = '\0';

  //main brute force body - finds matches in the fileString
  i = 0;
  while(fileString[i] != '\0'){
    j = 0;
    if(fileString[i] < 128 && fileString[i] > 0){
      while(fileString[i + j] == userString[j]){
        j++;
        //if j is equal to length, we know we've found the correct match
        if(j == length){
          occurences++;
        }
      }
    }
    numShifts++;
    i++;
  }

  free(fileString);


  //print findings
  printf("Found: %d occurences\n", occurences);
  printf("Total number of shifts = %ld\n", numShifts);

  ftime(&end);

  /*Find run time*/
  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;
  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  fclose(fp);

  return 0;
}
