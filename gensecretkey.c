#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100000

char lol[] = "this is not the string you're looking for";
int offsetoffset = 1337;

int main(){
  srand(time(NULL));
  FILE* out = fopen("haystack", "w+");

  //32-126
  for (int i = 0; i < SIZE; i++){
    int ch = (rand()%(126-32))+32;
    fwrite(&ch, 1, 1, out);
  }

  int loloffset = (rand()%(SIZE-1337))+1400;
  fseek(out, offsetoffset, SEEK_SET);
  fwrite(&loloffset, sizeof(int), 1, out);
  fseek(out, loloffset, SEEK_SET);
  fwrite(lol, 11, 1, out);
  
  return 0;
}
