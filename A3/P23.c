# include <limits.h>
# include <string.h>
# include <stdio.h>
#include <sys/timeb.h>

void badShiftTable(char userString[500]);
void boyerMoore( char readLine[500], char userString[500]);

int counter = 0;
long numShifts = 0;
int badTable[500];

int main(){
  FILE *fp = NULL;
  struct timeb start, end;
  char *fileName = "data_5.txt";
  char readLine[500];
  char userString[500];
  int i = 0;
  int milSeconds = 0;
  float seconds = 0.0;

  fp = fopen(fileName, "r");

  printf("Enter a string to find matches in %s\n", fileName);
  fgets(userString, 500, stdin);

  //set new line from fgets to null terminator
  for(i = 0; i < strlen(userString); i++){
    if(userString[i] == '\n'){
      userString[i] = '\0';
    }
  }

  ftime(&start);

  //create the bad Shift Table for mismatches with the file line
  badShiftTable(userString);

  //Main boyer-moore body
  while(fgets(readLine, 500, fp) != NULL){
    //parse for bad input
    for(i = 0; i < strlen(readLine); i++){
      if(readLine[i] == '\t' || readLine[i] == '\n'){
        readLine[i] = ' ';
      }
      if(readLine[i] < 0 || readLine[i] > 127) readLine[i] = ' ';
    }

    //findMatches
    boyerMoore(readLine, userString);
  }

  ftime(&end);

  //printFindings
  if(counter > 0){
    printf("\nFound %d occurences\n", counter);
  }
  else{
    printf("\nNo occurences found\n");
  }

  printf("Total shifts = %ld\n", numShifts);

  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;
  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  fclose(fp);
  return 0;
}

//Boyer-moore algorithm to find matches given two strings
//based on basic boyer-moore pattern matching from geeksforgeeks.com
void boyerMoore( char readLine[500], char userString[500]){
  int lengthUser = strlen(userString);
  int lengthLine = strlen(readLine);
  int matchChar = '\0';
  int i = 0; //used for keeping tack of the position of the file line
  int j = 0; //used to find matching characters in userString and file line

  //while is not pointing to the end of the of the line (well, userString length from the end)
  while(i < (lengthLine - lengthUser) + 1){
    j = lengthUser - 1;
    //if characters keep matching, decrease j until it hits -1
    while(j > -1 && userString[j] == readLine[i+j]){
      j--;
    }
    //if j reaches -1, we know there is a match
    if(j == -1){
      counter++;
      //If we aren't at the end of the line, shift to next char after the found word
      if(i + lengthUser < lengthLine){
        matchChar = readLine[i + lengthUser];
        i += lengthUser - badTable[matchChar];
        numShifts++;
      }
    }
    //otherwise, if j is not a match (most cases)
    else{
      //find character bad match value to shift by
      matchChar = readLine[i + j];
      //if the return value is positive, look up amount in bad shift table to move by
      if(j - badTable[matchChar] > 0){
        i += j - badTable[matchChar];
        numShifts++;
      }
      //else if the value is negative just increase by 1
      else{
        i += 1;
        numShifts++;
      }
    }
  }
}

//function to create bad shift table for boyer-moore
void badShiftTable(char userString[500]){
  int i;
  int convertChar = 0;
  int lengthUser = strlen(userString);
  // Initialize all occurrences as -1
  for(i = 0; i < 500; i++){
    badTable[i] = -1;
  }

  //fill badTable with values for userString
  for(i = 0; i < lengthUser; i++){
    convertChar = userString[i];
    badTable[convertChar] = i;
  }
}
