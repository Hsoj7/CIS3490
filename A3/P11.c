#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <sys/timeb.h>

void simpleSwitch(char *first, char *second);
void anagram(char *userInt, unsigned long startVal, int l, int r, unsigned long arrayOfNums[30001], unsigned long tempArray[10000]);
void anagram1(char *userInt, int l, int r);
int checkForRepeats(char *userInt, int left, int current);

long counter = 0;
int permCount = 0;

/*
the 10 digit run takes around 310 seconds
9 digits take around 30 seconds
*/

int main(){
  FILE *fp;
  struct timeb start, end;
  char *fileName = "data_4.txt";
  char convertInt[20];
  unsigned long arrayOfNums[30001];
  unsigned long tempArray[10000];
  unsigned long tempInt = 0;
  unsigned long userInt = 0;
  int i = 0;
  int length = 0;
  int milSeconds = 0;
  float seconds = 0.0;

  fp = fopen(fileName, "r");

  fscanf(fp, "%lu", &tempInt);
  while(!feof(fp)){
    if(feof(fp)) break;
    arrayOfNums[i] = tempInt;
    fscanf(fp, "%lu", &tempInt);
    i++;
  }

  for(i = 0; i < 10000; i++){
    tempArray[i] = 0;
  }

  printf("Enter integer to find all permutations\n");
  scanf("%lu", &userInt);


  length = floor(log10(abs(userInt))) + 1;
  sprintf(convertInt, "%lu", userInt);
  anagram1(convertInt, 0, length - 1);
  printf("\nFound %d anagrams of %s, now finding matches in data_4.txt\n\n", permCount - 1, convertInt);
  ftime(&start);
  sprintf(convertInt, "%lu", userInt);
  anagram(convertInt, userInt, 0, length - 1, arrayOfNums, tempArray);

  ftime(&end);

  printf("Found %ld matches in data_4.txt\n", counter);

  /*Find run time*/
  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;
  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  fclose(fp);

  return 0;
}

void anagram1(char *userInt, int l, int r){
  int i = 0;
  int repeats = 0;

  if(l == r){
    if(permCount == 0){

    }
    else{
      //printf("Anagram #%d = %s\n", permCount, userInt);
    }
    permCount++;
  }
  else{
    for(i = l; i <= r; i++){
      repeats = checkForRepeats(userInt, l, i);
      if(repeats == 1){
        simpleSwitch((userInt+l), (userInt+i));
        anagram1(userInt, l+1, r);
        simpleSwitch((userInt+l), (userInt+i)); //backtrack
      }
    }
  }
}

int checkForRepeats(char *userInt, int left, int current){
  for(int i = left; i < current; i++){
    if(userInt[i] == userInt[current]){
      return 0;
    }
  }
  return 1;
}

void anagram(char *userInt, unsigned long startVal, int l, int r, unsigned long arrayOfNums[30001], unsigned long tempArray[10000]){
  int i, j, good = 0;
  unsigned long temp = 0;
  char *ptr = NULL;
  int tempLength = 0;

  if(l == r){
    //counter++
    temp = strtoul(userInt, &ptr, 10);
    for(i = 0; i < 30000; i++){
      if(temp == arrayOfNums[i] && temp != startVal){
        for(j = 0; j < 10000; j++){
          if(temp != tempArray[j]){
            good = 1;
          }
        }
      }
    }

    if(good == 1){
      for(j = 0; j < 10000; j++){
        if(temp == tempArray[j]){
          good = 0;
          break;
        }

        if(tempArray[j] == 0){
          tempArray[j] = temp;
          break;
        }
      }
      if(good == 1){
        tempLength = floor(log10(abs(temp))) + 1;
        if(tempLength != strlen(userInt)){
          good = 0;
        }
      }
      if(good == 1){
        counter++;
        printf("%lu\n", temp);
        good = 0;
      }
    }
    else{
      good = 0;
    }
  }
  else{
    for(i = l; i <= r; i++){
      simpleSwitch((userInt+l), (userInt+i));
      anagram(userInt, startVal, l+1, r, arrayOfNums, tempArray);
      simpleSwitch((userInt+l), (userInt+i)); //backtrack
    }
  }
}

void simpleSwitch(char *first, char *second){
  char holderString;

  holderString = *first;
  *first = *second;
  *second = holderString;
}
