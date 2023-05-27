#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#define FILENAME_SIZE 1024
#define MAX_LINE 30

const char* ReadLine(int read_line, char nomfile[])
{
  int len;
  FILE *file;
  char buffer[30];
char *buff;
  //Verif si le fichier existe
  file = fopen(nomfile,"r");
if(file ==NULL){
  printf("Erreur\n");
}  
  
bool keep_reading = true;
int current_line =1;
  
  do
    {
      fgets(buffer, MAX_LINE, file);
      if(feof(file)){                //Si on arriv eà la fin du fichier
        keep_reading = false;        // On arrête de lire
      }
      else if(current_line==read_line){    //Si on est sur la ligne voulue, on arrête de lire + on retourne ce qu'il y a sur la ligne
        keep_reading = false;
        len = strlen(buffer);
         if (buffer[len-1] == '\n')    //Lorsque on utilise fgets, il y a un \n qui s'ajoute en + , du coup ici on l'enlève car on aura besoin parfois de comparer (strcpm) 
         buffer[len-1] = 0;
        buff = buffer;
        return buff;
      }
      current_line++;
    }while(keep_reading);

  fclose(file);

}
