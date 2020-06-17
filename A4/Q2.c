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
  struct binSearchTree *leftSubTree, *rightSubTree;
};

void insert(struct binSearchTree *ptr, struct binSearchTree *temp);
void printTree(struct binSearchTree *temp);
void search(char userInput[20]);
//global pointer to the tree's root
struct binSearchTree *root = NULL;

int main(){
  FILE *fp = NULL;
  struct binSearchTree *temp = NULL;
  char fileArray[601][20];
  char fileString[20];
  char fileName[20] = "data_7.txt";
  char userInput[50];
  char tempString[20];
  int frequencyArr[601];
  int i = 0, j = 0, fileArrayTracker = 0, freqTracker = 0;
  int maxFrequency = 0, maxFreqPrev = 500, holder = 0, position = 0;;
  int newWord = 1;
  //initialize all values in frequency to 1
  for(i = 0; i < 600; i++){
    frequencyArr[i] = 1;
  }
  fp = fopen(fileName, "r");
  //Puts every word from the data_7.txt file into a fileString
  fileArrayTracker = 0;
  while( fscanf(fp, "%s", fileString) == 1 ){
    for(i = 0; i < 600; i++){
      //determines if the word is unique or not
      if(strcmp(fileArray[i], fileString) == 0){
        newWord = 0;
        freqTracker = i;
        break;
      }
    }
    //if its unique, put it into the 2d array, fileArray
    if(newWord == 1){
      strcpy(fileArray[fileArrayTracker], fileString);
      fileArrayTracker++;
    }
    //otherwise increase frequency
    else{
      frequencyArr[freqTracker]++;
    }
    newWord = 1;
  }
  //perform bubble sort on the 2d array and its corresponding frequency array
  //to sort alphabetically
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
  //This loop creates the tree
  i = 0;
  while(i < 600){
    maxFrequency = 0;
    temp = root;
    //determines the next highest frequency in the array
    for(j = 0; j < 600; j++){
      if(frequencyArr[j] >= maxFrequency && frequencyArr[j] <= maxFreqPrev && frequencyArr[j] > 0){
        maxFrequency = frequencyArr[j];
        position = j;
      }
    }
    //determines if the node to insert is the root, or a leaf
    if(root == NULL){
      root = malloc(sizeof(struct binSearchTree));
      strcpy(root->key, fileArray[position]);
      root->frequency = frequencyArr[position];
    }
    //if its a leaf, we pass 'insert' the ptr to insert, and 'temp', which is
    //a pointer to the root
    else{
      struct binSearchTree *ptr = malloc(sizeof(struct binSearchTree));
      strcpy(ptr->key, fileArray[position]);
      ptr->frequency = frequencyArr[position];
      insert(ptr, temp);
    }
    //maxFreqPrev keeps track of the last frequency we worked with
    maxFreqPrev = maxFrequency;
    frequencyArr[position] = 0;
    i++;
  }
  //gets user input to find a word
  temp = root;
  printf("Enter a word (key)\n");
  fgets(userInput, 50, stdin);
  //removes the '\n' from user input
  for(i = 0; i < strlen(userInput); i++){
    if(userInput[i] == '\n') userInput[i] = '\0';
  }

  if(strlen(userInput) == 0){
    printf("Error, must enter something\n");
  }
  else{
    //calls the search function
    search(userInput);
  }

  fclose(fp);
  return 0;
}

/*insert function to insert a node into the binary tree*/
void insert(struct binSearchTree *ptr, struct binSearchTree *temp){
  if(strcmp(ptr->key, temp->key) < 0){
    if(temp->leftSubTree == NULL){
      temp->leftSubTree = ptr;
    }
    else insert(ptr, temp->leftSubTree);
  }
  else if(strcmp(ptr->key, temp->key) > 0){
    if(temp->rightSubTree == NULL){
      temp->rightSubTree = ptr;
    }
    else insert(ptr, temp->rightSubTree);
  }
}
/*helper function to print out the tree, used for debugging*/
void printTree(struct binSearchTree *temp){
  if(temp != NULL){
    printTree(temp->leftSubTree);
    printf("Key = %s, frequency = %d\n", temp->key, temp->frequency);
    printTree(temp->rightSubTree);
  }
}
/*searches the tree for the user's string and computes the probability at each step*/
void search(char userInput[20]){
  struct binSearchTree *temp = root;
  double probability = 0.0;

  while(1){
    if(temp == NULL){
      printf("Error, tree is empty\n");
      exit(-1);
    }
    else if(strcmp(temp->key, userInput) == 0){
      printf("Found\n");
      break;
    }
    else if(temp->leftSubTree != NULL && strcmp(temp->key, userInput) > 0){
      //search left subtree
      probability = (double)temp->frequency / 2045;
      printf("Compared with %s (%.4f), go left subtree\n", temp->key, probability);
      temp = temp->leftSubTree;
    }
    else if(temp->rightSubTree != NULL && strcmp(temp->key, userInput) < 0){
      //search right subtree
      probability = (double)temp->frequency / 2045;
      printf("Compared with %s (%.4f), go right subtree\n", temp->key, probability);
      temp = temp->rightSubTree;
    }
    else{
      printf("Not found\n");
      break;
    }
  }
}
