#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define cantPersonas 1

struct Persona {
    char* nombre;
    int edad;
    char* cuit;
};

int cuitValido(char *cuit) {
    
    int nums[11];
    int mults[10] = {5,4,3,2,7,6,5,4,3,2};

    for(int i = 0; i < strlen(cuit); i++) {
        nums[i] = (cuit[i] - '0');
    }

    int suma = 0;
    for(int i = 0; i < 10; i++) {
        suma += nums[i] * mults[i];
    }

    int verifyingDigit = ((suma % 11) - 11) * -1;
    if(verifyingDigit == nums[10]) {
        return 1;
    } 
    return 0;
}

int main() {
    
    struct Persona* personas[cantPersonas] = {0};
    char com[20];

    while(1) {
        scanf("%s", com);

        if(!strcmp(com, "infoUsuario")) {
            if(personas[0] == 0) {
                printf("No hay nadie en el sistema\n");
            } else {
                for(int i = 0; i < cantPersonas; i++) {
                    if(personas[i] == 0) {
                        break;
                    } else {
                        printf("Nombre: %s, Edad: %d, CUIT: %s\n", personas[i]->nombre, personas[i]->edad, personas[i]->cuit);
                    }
                }
            }
        } else if(!strcmp(com, "agregarUsuario")) {
            int ix = -1;
            for(int i = 0; i < cantPersonas; i++) {
                if(personas[i] == 0) {
                    ix = i;
                    break;
                }
            }
            if(ix == -1) {
                printf("Sistema lleno\n");
                continue;
            }

            char nombre[50], cuit[11];
            int edad;
            
            printf("Ingrese nombre: ");
            scanf("%s", nombre);
            
            printf("Ingrese edad: ");
            scanf("%d", &edad);

            printf("Ingrese CUIT: ");
            scanf("%s", cuit);

            if(!(edad >= 18 && edad <= 99) || !cuitValido(cuit)) {
                printf("Información errónea. Usuario no agregado\n");
                continue;
            }

            /*
            if(persona != 0) {
                free(persona->nombre);
                free(persona->cuit);
                free(persona);
            }
            */

            struct Persona* persona = malloc(sizeof(struct Persona));
            persona->nombre = strdup(nombre); // malloc + strcpy
            persona->edad = edad;
            persona->cuit = strdup(cuit); // malloc + strcpy

            personas[ix] = persona;

            printf("Usuario agregado correctamente\n");

        }



    }
    return 0;
}