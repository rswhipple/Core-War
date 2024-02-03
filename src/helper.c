#include "../include/helper.h"


int my_atoi(char *num) {
  int output = 0;
  int i;
  int temp;

  for (i = 0; i < strlen(num); i++) {
    output *= 10;
    output += num[i] - '0';
  }

  return output;
}


char* init_str(int size)  
{
    char* str = malloc(sizeof(char) * size + 1);

    for (int i = 0; i < size + 1; i++) { str[i] = '\0'; }

    return str;
}
