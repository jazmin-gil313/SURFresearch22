#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1024

int main(int argc, char * argv[]) {
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char line[MAXLINE];


  inputFile = fopen(argv[1], "r");
  if(inputFile == NULL) {
    fprintf(stdout, "Unable to open source file \n");
    return 0;
  }
  outputFile = fopen(argv[2], "w");
  if(outputFile == NULL) {
    fprintf(stdout, "Unable to open source file \n");
    return 0;
  }


  while(fgets(line, MAXLINE, inputFile) != NULL) {
    fprintf(outputFile,"%s",line);
    }
  }
}


//.02358 && 3.129
