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

int my_strlen(char* str) 
{
    int i = 0;

    do {
        i += 1;
    } while (str[i] != '\0');

    return i;
}

char* my_strcpy(char* dst, char* src)
{
    int i;
    int length = my_strlen(src);

    for (i = 0; i < length; i++) {
        dst[i] = src[i]; 
    }

    dst[i] = '\0';

    return dst;
}

char* my_strncpy(char* dst, char* src, int n)
{
    char* original_dst = dst;
    int i;

    for (i = 0; i < n; i++) {
        *dst++ = *src++;
    }

    *--dst = '\0';

    return original_dst;
}

char* my_strcat(char *dst, char *src) 
{ 
    // Save original destination pointer
    char *original_dst = dst; 
    
    // Move destination pointer to the end of the first string
    while (*dst != '\0') {
        dst += 1;
    }

    // Copy characters from src to dst
    while (*src != '\0') {
        *dst = *src;
        dst += 1;
        src += 1;
    }

    // Null-terminate 
    *dst = '\0';

    return original_dst;
}
