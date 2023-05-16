#include <stdio.h>
#include <stdbool.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 30


const char* ReadLine(int read_line, char nomfile[])
{
  FILE *file;
  char buffer[100];
char *buff;
  file = fopen(nomfile,"r");
if(file ==NULL){
  printf("Erreur\n");
}  
bool keep_reading = true;
int current_line =1;
  do
    {
      fgets(buffer, MAX_LINE, file);
      if(feof(file)){
        keep_reading = false;
      }
      else if(current_line==read_line){
        keep_reading = false;
        buff= buffer;
        return buff;
      }
      current_line++;
    }while(keep_reading);

  fclose(file);

}
