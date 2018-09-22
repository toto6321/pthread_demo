//
// Created by toto on 9/22/18.
//
#include <cstdlib>
#include <cstdio>

#include "MyStruct.h"

#ifndef HOMEWORK1_TIANHUAN_TU_READ_FILE_H
#define HOMEWORK1_TIANHUAN_TU_READ_FILE_H

#endif //HOMEWORK1_TIANHUAN_TU_READ_FILE_H

MyStruct *read_the_single_file(char *file_name, unsigned long int *number) {
    // save the frequently-used value to make performance better
    const unsigned int size_of_my_struct = sizeof(MyStruct);

    // pointer to the address where the dynamically allocated memory begins
    MyStruct *beginning = nullptr;

    // file pointer
    FILE *input_scream;

    // char buffer to hold data within fgets()
    char buffer[50];

    // variables to pass data to tuple property
    int operation_id, address, call_id, times;
    float read_timestamp;

    // char pointer to the address where the returned buffer of fgets() starts to be stored.
    char *buffer_string;


    // read the input_scream.out
    input_scream = fopen(file_name, "r");
    if (input_scream == nullptr) {
        printf("Reading %s failed!", file_name);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, 50, input_scream))) {
        // extract data from the buffer_string
        sscanf(buffer_string, "%d %f %x %d", &operation_id, &read_timestamp, &address, &call_id);
        times = 1;
        if(number== nullptr){
            printf("the number pointer is null pointer");
            exit(2);
        }
        // dynamically allocate memory to store our data
        if (*number == 0 ) {
            // number_of_read_singe = 0 means current data is the first, and we need to newly allocate memory space.
            beginning = (MyStruct *) calloc(*number + 1, size_of_my_struct);
        } else {
            // *number > 0 means there exist data and we need to resize the memory space by 1 to store current data
            beginning = (MyStruct *) realloc(beginning, size_of_my_struct * (*number + 1));
        }
        (beginning + *number)->address = address;
        (beginning + *number)->id = call_id;
        (beginning + *number)->times = times;

        // count + 1
        (*number)++;

//        printf("%d\t%.1f\t0x%08x\t%d\n", operation_id, read_timestamp, address, call_id);
    }

    // do not forget to close the scream
    fclose(input_scream);
    return beginning;

}