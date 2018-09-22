//
// Created by toto on 9/22/18.
//
#include <cstdlib>
#include <cstdio>

#include "MyStruct.h"

#ifndef HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H
#define HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H

#endif //HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H

FunctionIdSet *read_the_region_file(char *file_name, unsigned long int *number) {

    const unsigned int size_of_function_id_set = sizeof(FunctionIdSet);

    FunctionIdSet *beginning = nullptr;

    FILE *input_stream = nullptr;

    char buffer[200];
    char *buffer_string;

    int id = 0;
    char type[10], function_name[25];

    input_stream = fopen(file_name, "r");
    if (input_stream == nullptr) {
        printf("Reading %s failed!", file_name);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, 100, input_stream))) {
        sscanf(buffer_string, "%d %s %s", &id, type, function_name);
        if (number == nullptr) {
            printf("the number pointer is null pointer");
            exit(2);
        }

        if (*number == 0) {
            // number_of_read_singe = 0 means current data is the first, and we need to newly allocate memory space.
            beginning = (FunctionIdSet *) calloc(*number + 1, size_of_function_id_set);
        } else {
            // *number > 0 means there exist data and we need to resize the memory space by 1 to store current data
            beginning = (FunctionIdSet *) realloc(beginning, size_of_function_id_set * (*number + 1));
        }
        strcpy((beginning + *number)->function_name, function_name);
        (beginning + *number)->id = id;

        (*number)++;

//        printf("%-50s %d\n", function_name, id);
    }

    // do not forget to close the scream
    fclose(input_stream);
    return beginning;
}