#include "array_helpers.h"
#include <stdio.h> // for fprintf, fscanf and file operations
#include <stdlib.h> //for exit and EXIT_FAILURE
#include <stdbool.h>

unsigned int array_from_file(int array[],
                             unsigned int max_size,
                             const char *filepath) {
    /* Parse the file given by filepath and fill the array with its contents.
     * Returns the actual length of the array. */ 
    unsigned int length = 0;
    FILE *file = fopen(filepath, "r");
    if(file == NULL){
        fprintf(stderr, "Error opening file\n");
        exit(EXIT_FAILURE);
    }
    else{
        fscanf(file, "%u", &length); //read from file the first line and store it in length
        if(length > max_size){
            fprintf(stderr, "Error: array size is bigger than max_size\n");
            exit(EXIT_FAILURE);
        }
        unsigned int actual_length = 0;
        for(unsigned int i = 0; i < length && i < max_size; i++){
        if(fscanf(file, "%d", &array[i]) == 1){ // Verifica si realmente se leyó un elemento
                actual_length++; // Incrementa el contador solo si se leyó un elemento
            } else {
                // Si no se pudo leer el elemento esperado, rompe el bucle
                break;
            }
        }
        if(actual_length != length){
            fprintf(stderr, "Error: The actual number of elements (%u) is different from expected (%u). Array is invalid.\n", actual_length, length);
            fclose(file); // Asegúrate de cerrar el archivo antes de terminar el programa
            exit(EXIT_FAILURE); // Termina el programa indicando un fallo
        }
    }
    fclose(file);
    return length;
}

void array_dump(int a[], unsigned int length) {
    printf("[ ");
    for(unsigned int i = 0; i < length; i++){
        printf("%d", a[i]);
        if(i < length - 1){
            printf(", ");
        }
    }
    printf(" ]");
}

bool array_is_sorted(int a[], unsigned int length) {
    bool band = true;
    unsigned int i = 0;

    if(length == 0) return band;

    while(band == true && i < length - 1){
        if (a[i] <= a[i + 1]) i++;
        else band = false;
    }
    
    return band;
}

void array_swap(int a[], unsigned int i, unsigned int j){
    int aux = a[i];
    a[i] = a[j];
    a[j] = aux;
}

