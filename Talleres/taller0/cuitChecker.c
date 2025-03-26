#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {

    int nums[11];
    int mults[10] = {5,4,3,2,7,6,5,4,3,2};

    char* num = argv[1];
    for(int i = 0; i < strlen(num); i++) {
        nums[i] = (num[i] - '0');
    }

    int suma = 0;
    for(int i = 0; i < 10; i++) {
        suma += nums[i] * mults[i];
    }

    int verifyingDigit = ((suma % 11) - 11) * -1;
    if(verifyingDigit == nums[10]) {
        printf("Todo correcto");
    } else {
        printf("Erróneo. Número correcto: ");
        nums[10] = verifyingDigit;
        for(int i = 0; i < 11; i++) {
            printf("%d", nums[i]);
        }
    }
    printf("\n");
    return 0;
}