/*
 * Jazmin Gil
 * Yale SURF Program
 * July 2022
 *
 * This program will read in the data from the .gad file and write out
 * an OBJ file
 *
 */



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAXLINE 1024

struct Track {
  int start;
  int end;
  struct Track * next;
};
typedef struct Track Track;

int main(int argc, char * argv[]) {
  FILE *inputFile = NULL;
  FILE *outNorm = NULL;
  //FILE *outScale = NULL;
  char line[MAXLINE];
  Track * tracks = NULL;
  Track * current = NULL;
  Track * temp = NULL;

  int i;
  int counter=1;


  inputFile = fopen(argv[1], "r");
  if(inputFile == NULL) {
    fprintf(stdout, "Unable to open source file \n");
    return 0;
  }

  outNorm = fopen(argv[2], "w");
  if(outNorm == NULL) {
    fprintf(stdout, "Unable to open listing file");
    return 0;
  }
  //
  // outScale = fopen(argv[3], "w");
  // if(outScale == NULL) {
  //   fprintf(stdout, "Unable to open listing file");
  //   return 0;
  // }

  for(i=0; i<94; i++)
  {
    //ignore the first lines of the GaD file which has labels
    fgets(line, MAXLINE, inputFile);
  }

  printf("Printing vertices...\n\n");



  while(fgets(line, MAXLINE, inputFile) != NULL) {
    char* subline = strndup(line, 9);

    if(strcmp (subline, "  <Object") == 0) {

      for(i=0; i<7; i++)
      {
        fgets(line, MAXLINE, inputFile);
      }

      if(tracks == NULL) {
        tracks = (Track *)malloc(sizeof(Track));
        tracks->start=counter;
        current = tracks;
      }
      else {

        current->end = counter-1;

        temp = (Track *)malloc(sizeof(Track));
        temp->start = counter;
        current->next = temp;
        current = current->next;
      }

    }
    else if(strcmp (subline, "  </Objec") == 0) {
      fgets(line, MAXLINE, inputFile);
    }
    else {
      char *binary = strtok(line, ", ");
      //printf("%s ",binary);

      binary = strtok(NULL, ", ");
      double x = strtod(binary, NULL);
      binary = strtok(NULL, ", ");
      double y = strtod(binary, NULL);
      binary = strtok(NULL, ", ");
      double z = strtod(binary, NULL);

      fprintf(outNorm,"v %lf %lf %lf\n",x,y,z);
      counter++;
    }

  }

  current->end = counter-1;

  fprintf(outNorm, "\n");
  temp = tracks;
  printf("Printing faces...\n");
  while(temp != NULL){
    //fprintf(outputFile, "l ");
    fprintf(outNorm,"curv ");
    for(i=temp->start; i<temp->end+1; i++) {
      fprintf(outNorm, "%d ", i);
    }
    fprintf(outNorm, "\n");
    tracks = temp;
    temp = temp->next;
    free(tracks);
  }

  printf("All done!\n");
}
