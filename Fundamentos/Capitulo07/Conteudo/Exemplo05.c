// String concat - concatenando strings 
#include <stdio.h>
#include <string.h>

char *strcat (char *dest, char *orig){
    int len;
    
    for (int i = 0, len = strlen(dest); orig[i] != '\0'; i++, len++){
        dest[len] = orig[i];
    }
    
    dest[len] = '\0';
    return dest;
}