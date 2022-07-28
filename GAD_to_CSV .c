#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1024

int main(int argc, char * argv[]) {
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char line[MAXLINE];

  int i;
  int counter=1;


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

  for(i=0; i<94; i++)
  {
    //ignore the first lines of the GaD file which has labels
    fgets(line, MAXLINE, inputFile);
  }

  fprintf(outputFile,"Track Num, X,Y,Z\n");


  while(fgets(line, MAXLINE, inputFile) != NULL) {
    char* subline = strndup(line, 9);

    if(strcmp (subline, "  <Object") == 0) {
      for(i=0; i<7; i++)
      {
        fgets(line, MAXLINE, inputFile);
      }
    }
    else if(strcmp (subline, "  </Objec") == 0) {
      fgets(line, MAXLINE, inputFile);
        counter++;
    }
    else {
      char *binary = strtok(line, ", ");
      fprintf(outputFile,"%d,",counter);

      //x value
      binary = strtok(NULL, ", ");
      fprintf(outputFile,"%s,",binary);
      //y value
      binary = strtok(NULL, ", ");
      fprintf(outputFile,"%s,",binary);
      //z value
      binary = strtok(NULL, ", ");
      fprintf(outputFile,"%s",binary);
    }
  }
}
