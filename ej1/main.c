/* First, the standard lib includes, alphabetically ordered */
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

/* Maximum allowed length of the array */
#define MAX_SIZE 100000

void print_help(char *program_name) {
    /* Print the usage help of this program. */
    printf("Usage: %s <input file path>\n\n"
           "Loads an array given in a file in disk and prints it on the screen."
           "\n\n"
           "The input file must have the following format:\n"
           " * The first line must contain only a positive integer,"
           " which is the length of the array.\n"
           " * The second line must contain the members of the array"
           " separated by one or more spaces. Each member must be an integer."
           "\n\n"
           "In other words, the file format is:\n"
           "<amount of array elements>\n"
           "<array elem 1> <array elem 2> ... <array elem N>\n\n",
           program_name);
}

char *parse_filepath(int argc, char *argv[]) {
    /* Parse the filepath given by command line argument. */
    char *result = NULL;
    // Program takes exactly two arguments
    // (the program's name itself and the input-filepath)
    bool valid_args_count = (argc == 2);

    if (!valid_args_count) {
        print_help(argv[0]);
        exit(EXIT_FAILURE);
    }

    result = argv[1];

    return result;
}

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


int main(int argc, char *argv[]) {
    char *filepath = NULL;

    /* parse the filepath given in command line arguments */
    filepath = parse_filepath(argc, argv);
    
    /* create an array of MAX_SIZE elements */
    int array[MAX_SIZE];
    
    /* parse the file to fill the array and obtain the actual length */
    unsigned int length = array_from_file(array, MAX_SIZE, filepath);
    
    /*dumping the array*/
    array_dump(array, length);
    
    return EXIT_SUCCESS;
}
