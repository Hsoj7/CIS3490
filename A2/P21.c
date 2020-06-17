/*
Name: Joshua Stone
ID: 1013900
Email: jstone04@uoguelph.ca
Date: February 11, 2019
Assign 2
*/

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <sys/timeb.h>

void convexAlgorithm(double xVals[30001], double yVals[30001], int numVerts);
int pointInArr(double x, double y, double xArr[], double yArr[], int size);

int main(){
  FILE *fp;
  struct timeb start, end;
  int milSeconds = 0;
  float seconds = 0.0;
  char *fileName = "data_test.txt";
  char *buffer = NULL;
  char temp[10];
  int i = 0, j = 0, k = 0; //i used for buffer, j used for temp, k used for x/yVals
  double xVals[30001];
  double yVals[30001];
  int xStart = 0;
  double toConvert = 0.0;
  int x = 1;
  int y = 0;

  ftime(&start);

  fp = fopen(fileName, "r");
  buffer = malloc(25);

  while(!feof(fp)){
    xStart = 0;
    fgets(buffer, 25, fp);
    if(feof(fp)) break;

    if(buffer[0] == ' '){
      xStart++;
    }
    if(buffer[1] == ' '){
      xStart++;
    }
    if(buffer[2] == ' '){
      xStart++;
    }
    if(buffer[3] == ' '){
      xStart++;
    }

    for(i = 0 + xStart; i < strlen(buffer); i++){
      if(x == 1){
        if(isdigit(buffer[i]) || buffer[i] == '.'){
          temp[j] = buffer[i];
          j++;
        }
        else if(buffer[i] == ' ' || buffer[i] == '\t'){
          toConvert = atof(temp);
          xVals[k] = toConvert;
          temp[0] = '\0';
          j = 0; //reset temp
          x = 0;
          y = 1;
        }
      }
      else if(y == 1){
        if(buffer[i] == ' '){
          //Do nothing
        }
        else if(isdigit(buffer[i]) || buffer[i] == '.'){
          temp[j] = buffer[i];
          j++;
        }
        else if(buffer[i] == '\n'){
          toConvert = atof(temp);
          yVals[k] = toConvert;
          j = 0;
          x = 1;
          y = 0;
        }
      }
    }
    k++;
  }

  free(buffer);
  fclose(fp);

  convexAlgorithm(xVals, yVals, 10);

  ftime(&end);

  milSeconds = (int) (1000.0 * (end.time - start.time) + (end.millitm - start.millitm));
  seconds = milSeconds / 1000.0;

  printf("Time took to run: %dms, %.2fs\n", milSeconds, seconds);

  return 0;
}

void convexAlgorithm(double xVals[30001], double yVals[30001], int numVerts){

}
