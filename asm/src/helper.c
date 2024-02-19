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
    *dst = '\0';

    return original_dst;
}

int my_strncmp(char* str_1, char* str_2, int index)
{
    int i = 0;
    int str_to_int_1 = 0;
    int str_to_int_2 = 0;

    while (i < index && str_1[i] != '\0') {
        str_to_int_1 += str_1[i];
        i++;
    } 

    i = 0;
    while (i < index && str_2[i] != '\0') {
        str_to_int_2 += str_2[i];
        i++;
    } 
    
    if (str_to_int_1 == str_to_int_2) {
        return 0;
    } else if (str_to_int_1 > str_to_int_2) {
        return -1;
    } else {
        return 1;
    }

}

void *my_memset(void *s, int c, size_t n) {
    char *p = s;

    while (n--) {
        *p++ = (char)c;
    }

    return s;
}

void my_putstr(char *str) 
{
    write(STDOUT_FILENO, str, my_strlen(str));
}
