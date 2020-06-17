#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/timeb.h>

void shiftTable(char userString[500]);
void horspool(int m, char userString[500], int n, char mainString[500]);
void removeBadChars(char mainString[500]);

int table[500];
int counter = 0;
long numShifts = 0;

int main(){
  FILE *fp;
  struct timeb start, end;
  char *fileName = "data_5.txt";
  int i = 0;
  int lengthMain = 0;
  int lengthUser = 0;
  int milSeconds = 0;
  float seconds = 0.0;
  char mainString[500], userString[500];

  fp = fopen(fileName, "r");

  printf("Enter a string to find pattern in data_5.txt\n");
  fgets(userString, 500, stdin);
  printf("\n");

  for(i = 0; i < strlen(userString); i++){
    if(userString[i] == '\n'){
      userString[i] = '\0';
    }
  }

  ftime(&start);

  shiftTable(userString);

  while(!feof(fp)){
    if(feof(fp)) break;
    else{
      if( fgets(mainString, 500, fp) != NULL ){
        //removes tabs and new lines and any bad characters in the file
        for(i = 0; i < strlen(mainString); i++){
          if(mainString[i] == '\t' || mainString[i] == '\n'){
            mainString[i] = ' ';
          }
          if(mainString[i] < 0 || mainString[i] > 127) mainString[i] = ' ';
        }

        //get lengrhs of the string and call horspool to find matches
        lengthMain = strlen(mainString);
        lengthUser = strlen(userString);
        horspool(lengthUser, userString, lengthMain, mainString);
      }
    }
  }

  //print out the program's findings
  if(counter > 0){
    printf("Found %d occurences of %s\n", counter, userString);
  }
  else{
    printf("Could not find %s in the file\n", userString);
  }

  printf("Total number of shifts = %ld\n", numShifts);

  ftime(&end);

  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;
  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  fclose(fp);

  return 0;
}

//horspool function to find string matches in a given array
//Modified version of the sudo code on page 262 of the textbook
void horspool(int lengthUser, char userString[500], int lengthMain, char mainString[500]){
  int i = 0;
  int charConvert = 0;
  char charHolder = '\0';
  //length user = m, lengthMain = n

  while(i < lengthMain - lengthUser + 1){
    //gets right char and moves left if match
    charHolder = mainString[i + lengthUser - 1];
    //if the userString character at n - 1 equals the position in mainString,
    //we string compare the mainString's position and see if they match
    if(userString[lengthUser - 1] == charHolder && strncmp(userString, mainString + i, lengthUser) == 0){
      //we know there is a match so increase counter
      counter++;
    }
    //memcmp(userString, mainString + i, lengthUser - 1) == 0
    //increases i by appropriate
    charConvert = charHolder;
    i += table[charConvert];
    //we shifted, so increase shift counter
    numShifts++;
  }
}

//function to initailze the shift table with appropriate values
void shiftTable(char userString[500]){
  int i = 0, j = 0;
  int lengthUser = 0;
  int convertval = 0;
  lengthUser = strlen(userString);

  for(i = 0; i < 500; i++){
    //alls vals initially get set to size of userString
    table[i] = lengthUser;
  }
  //assigns shift values for letters in userString to the table
  for(j = 0; j < lengthUser - 1; j++){
    convertval = userString[j];
    table[convertval] = lengthUser - 1 - j;
  }
}

/*
void removeBadChars(char mainString[500]){
  int i = 0;

  for(i = 0; i < strlen(mainString); i++){
    if(mainString[i] >= 0 && mainString[i] <= 127){

    }
    else{
      mainString[i] = mainString[i + 1];
      i++;
    }
  }
}
*/
/*
while(!feof(fp)){
  if(feof(fp)) break;
  else{
    if( fgets(mainStr, 500, fp) != NULL ){
      //removes tabs and new lines
      for(i = 0; i < strlen(mainStr); i++){
        if(mainStr[i] == '\t' || mainStr[i] == '\n'){
          mainStr[i] = ' ';
        }
      }
      position = 0;
      line++;
      lengthMain = strlen(mainStr);
      lengthUser = strlen(userString);
      result = horspool();
      if(result > 0){
        counter++;
        if( (lengthUser + position) < lengthMain){
          result = horspool();
          if(result > 0){
            counter++;
          }
        }
      }
      else if(result == -1){

      }
    }
  }
}

if(counter > 0){
  printf("Found %d occurences of %s\n", counter, userString);
}
else{
  printf("Could not find %s in the file\n", userString);
}

ftime(&end);

milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
seconds = milSeconds / 1000.0;
printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

fclose(fp);

return 0;
}

//I think its not working becuase i is not at the end of the string, its in the middle
int horspool(){
int i = 0, k = 0, m = 0, n = 0;
int convertval = 0;
int repeat = 0;

m = strlen(mainStr); //length of the fgets
n = strlen(userString); //length of user string

//printf("position = %d\n", position);
if(position == 0){
  i = n - 1;
}
else if(position > 0){
  i = position + 1; // position + strlen(userString)
  printf("i = %d\n", i);
  //convertval = userString[n - 2];
  //i += table[convertval];
}

while( i < m ){
  //printf("i = %d, m = %d, k = %d, n = %d\n", i, m, k, n);
  k = 0;
  //while they match goes from right side to left
  while((k < n) && userString[n-1-k] == mainStr[i-k]){
    k++;
  }
  if(k == n){
    printf("Found at %d, on line %d\n", i, line);
    position = i; //weird why i + 1 works better
    return 1;
    //position = i - n + 1;
  }
  else{
    repeat++;
    convertval = mainStr[i];
    i += table[convertval];
    //printf("At i = %d, line = %d\n", i, line);
  }

  if(repeat > 1){
    i++;
    //convertval = userString[n - 2];
    //i += table[convertval];
    repeat = 0;
  }
}

return -1;
}

//works great
void shiftTable(){
int i, j, m;
int convertval = 0;
m = strlen(userString);

for(i = 0; i < 500; i++){
  //alls vals initially get set to size of userString
  table[i] = m;
  for(j = 0; j <= m - 1; j++){
    convertval = userString[j];
    table[convertval] = m - 1 - j;
  }
}
}
 */
