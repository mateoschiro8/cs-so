#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

void invertWord(char* str, char* out, int init, int size) {
    for(int i = 0; i < size; i++) {
        out[init + i] = str[init + size - 1 - i]; 
    }
}

void copyWord(char* str, char* out, int init, int size) {
    for(int i = init; i < init + size; i++) {
        out[i] = str[i]; 
    }
}

void checkSize(int n, char* str, char* out, int init, int size) {
    if(size > n) {
        invertWord(str, out, init, size);
    } else {
        copyWord(str, out, init, size);
    }
}

// No tiene en cuenta signos de puntuación y no pasa a mayúsculas
int main(int argc, char *argv[]) {
    
    int n = atoi(argv[1]);
    char *str = argv[2];

    size_t l = strlen(str);
    char *out = calloc(l + 1, sizeof(char));
    out[l] = '\0';

    int size = 0;
    int init = 0;

    for(size_t i = 0; i < l; i++) {
        if(str[i] != ' ' && str[i] != '\0') {
            size++;
        } else {
            checkSize(n, str, out, init, size);
            
            if (str[i] == ' ') {
                out[i] = ' '; 
            }
            size = 0;
            init = i + 1;
        }
        
    }
    checkSize(n, str, out, init, size);
    printf("%s\n", out);
    free(out);
    return 0;   
}
