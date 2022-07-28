/*
* This program is to take out the diameters of the hair segment and
* to double check the units of measurements

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXLINE 1024



int main(int argc, char * argv[]) {
  FILE *inputFile = NULL;
  FILE *outputFile = NULL;
  char line[MAXLINE];
  int i, num;
  float diameter;

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

  fprintf(outputFile,"TrackNum,Diameter\n");
  num=1;
  while(fgets(line, MAXLINE, inputFile) != NULL) {
    char* subline = strndup(line, 9);

    if(strcmp (subline, "  <Object") == 0) {
      //reached a new object and need to get the diameter
      for(i=0; i<7; i++)
      {
        fgets(line, MAXLINE, inputFile);
      }
      char *binary = strtok(line, " ");
      binary = strtok(NULL, " ");
      fprintf(outputFile,"%d,%s",num,binary);
      num++;
    }
  }

}




//Addditional notes
// Note that 1 mm == 1x10^-3 m so it makes since that most of the hair strands
// have a diameter of 10^-5... so I think that is makes sense the unit it meters
