#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include <math.h>

void mergeArrays(unsigned long mergeArray[], unsigned long arrayOfNums[30001], long center, long leftIndex, long totalNums);
void mergesortAlgorithm(unsigned long mergeArray[], unsigned long arrayOfNums[30001], long leftIndex, long totalNums);
void anagram1(char *userInt, int l, int r);
void anagram(char *userInt, int l, int r, unsigned long arrayOfNums[30001], unsigned long tempArray[10000], unsigned long startVal);
void simpleSwitch(char *first, char *second);
unsigned long binSearch(unsigned long key, unsigned long arrayOfNums[30001], int left, int right);
int checkForRepeats(char *userInt, int left, int current);

/*

*/

int counter = 0;
int wack = 0;
int permCount = 0;

int main(){
  FILE *fp;
  struct timeb start, end;
  char *fileName = "data_4.txt";
  char convertInt[20];
  unsigned long tempArray[10000];
  unsigned long arrayOfNums[30001];
  unsigned long *mergeArray = NULL;
  unsigned long tempInt = 0;
  unsigned long userInt = 0;
  int milSeconds = 0;
  int i = 0;
  int totalNums = 30000;
  int length = 0;
  float seconds = 0.0;

  fp = fopen(fileName, "r");

  fscanf(fp, "%lu", &tempInt);
  while(!feof(fp)){
    if(feof(fp)) break;
    arrayOfNums[i] = tempInt;
    fscanf(fp, "%lu", &tempInt);
    i++;
  }

  printf("Enter integer to find all permutations\n");
  scanf("%lu", &userInt);

  mergeArray = malloc(sizeof(unsigned long) * totalNums);
  mergesortAlgorithm(mergeArray, arrayOfNums, 0, totalNums - 1);

  length = floor(log10(abs(userInt))) + 1;
  sprintf(convertInt, "%lu", userInt);
  anagram1(convertInt, 0, length - 1);

  printf("\nFound %d anagrams of %s, now checking for matches in data_4.txt\n\n", permCount - 1, convertInt);
  ftime(&start);
  for(i = 0; i < 10000; i++){
    tempArray[i] = 0;
  }
  sprintf(convertInt, "%lu", userInt);
  anagram(convertInt, 0, length - 1, arrayOfNums, tempArray, userInt);

  printf("Found %d matches in data_4.txt\n", counter);
  ftime(&end);

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

void anagram(char *userInt, int l, int r, unsigned long arrayOfNums[30001], unsigned long tempArray[10000], unsigned long startVal){
  int i = 0, j = 0, good = 0;
  char *ptr = NULL;
  unsigned long result = 0;
  unsigned long key = 0;
  int tempLength = 0;

  if(l == r){
    key = strtoul(userInt, &ptr, 10);
    result = binSearch(key, arrayOfNums, 0, 30000 - 1);
    if( result == 0 ){
      //break;
    }
    else{
      for(j = 0; j < 10000; j++){
        if( (result != tempArray[j] && result != startVal) || tempArray[j] == 0){
          good = 1;
          break;
        }
        else if(result == tempArray[j]){
          good = 0;
          break;
        }
      }

      if(good == 1){
        for(i = 0; i < 10000; i++){
          if(result == tempArray[i]){
            good = 0;
            break;
          }
          if(tempArray[i] == 0){
            tempArray[i] = result;
            break;
          }
        }
        if(good == 1){
          tempLength = floor(log10(abs(result))) + 1;
          if(tempLength != strlen(userInt)){
            good = 0;
          }
        }
        if(good == 1){
          counter++;
          printf("%lu\n", result);
          good = 0;
        }
      }
    }
  }
  else{
    for(i = l; i <= r; i++){
      simpleSwitch((userInt+l), (userInt+i));
      anagram(userInt, l+1, r, arrayOfNums, tempArray, startVal);
      simpleSwitch((userInt+l), (userInt+i)); //backtrack
    }
  }
}

unsigned long binSearch(unsigned long key, unsigned long arrayOfNums[30001], int left, int right){
  int center = (left + right) / 2;
  while(left <= right){
    //right
    if(arrayOfNums[center] < key){
      left = center + 1;
      center = (left + right) / 2;
    }
    //equal
    else if(arrayOfNums[center] == key){
      return key;
    }
    //left
    else if(arrayOfNums[center] > key){
      right = center - 1;
      center = (left + right) / 2;
    }
    else{
      return 0;
    }
  }
  return 0;
}

void simpleSwitch(char *first, char *second){
  char holderString;

  holderString = *first;
  *first = *second;
  *second = holderString;
}

void mergesortAlgorithm(unsigned long mergeArray[], unsigned long arrayOfNums[30001], long leftIndex, long totalNums){
  long center = 0;

  /*totalNums, or rightindex is greater than left index*/
  if (totalNums > leftIndex){
    center = (totalNums + leftIndex)/2;
    mergesortAlgorithm(mergeArray, arrayOfNums, leftIndex, center);
    mergesortAlgorithm(mergeArray, arrayOfNums, center + 1, totalNums);
    mergeArrays(mergeArray, arrayOfNums, center + 1, leftIndex, totalNums);
  }

}

/*Brings arrays back together*/
void mergeArrays(unsigned long mergeArray[], unsigned long arrayOfNums[30001], long center, long leftIndex, long totalNums){
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
}
