//
// Created by toto on 9/22/18.
//
#include <cstdlib>
#include <cstdio>
#include <cstring>

// c++ libraries
#include <string>
#include <iostream>
#include <map>
#include <set>


// my package
#include "my_struct.h"
#include "read_the_region_file.h"

const int FUNCTION_NAME_MAX_SIZE = 50;
const int REGION_ROW_MAX_SIZE = 300;

using namespace std;

#ifndef HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H
#define HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H

#endif //HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H


FunctionIdSet *read_the_region_file(char *file_name, unsigned long int *number) {
    if (number == nullptr) {
        printf("the number pointer is null pointer");
        exit(2);
    }

    const unsigned int SIZE_OF_FUNCTION_ID_SET = sizeof(FunctionIdSet);

    FunctionIdSet *beginning = nullptr;

    FILE *input_stream = nullptr;

    const int BUFFER_SIZE = REGION_ROW_MAX_SIZE;
    char buffer[REGION_ROW_MAX_SIZE];
    char *buffer_string;

    unsigned long int id = 0;
    char type[10] = "", function_name[FUNCTION_NAME_MAX_SIZE] = "";

    input_stream = fopen(file_name, "r");
    if (input_stream == nullptr) {
        printf("Reading %s failed!", file_name);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, BUFFER_SIZE, input_stream))) {
        if (sscanf(buffer_string, "%ld %s %s", &id, type, function_name) < 3) {
            // there will be no exception even though sscanf cannot extract data as expected
            // and in that case the variables will remain what they are.
            // we have to deal with this special case
            continue;
        }

        if (*number == 0) {
            // number_of_read_singe = 0 means current data is the first, and we need to newly allocate memory space.
            beginning = (FunctionIdSet *) calloc(*number + 1, SIZE_OF_FUNCTION_ID_SET);
        } else {
            // *number > 0 means there exist data and we need to resize the memory space by 1 to store current data
            beginning = (FunctionIdSet *) realloc(beginning, SIZE_OF_FUNCTION_ID_SET * (*number + 1));
        }
        strcpy((beginning + *number)->function_name, function_name);
        (beginning + *number)->id = id;

        (*number)++;

//        printf("%-50s %ld\n", function_name, id);
    }

    // do not forget to close the scream
    fclose(input_stream);
    return beginning;
}


/**
 *
 * @param beginning
 * @param length
 * @return a map of all (id, name) pairs
 */
void map_region(FunctionIdSet *beginning, unsigned long int length, map<int, string> *region_map) {
    void string_to_char_array(const string &s, char ch[]);

    map<int, string>::iterator it;
    unsigned long int index = 0;

    // variable to store properties of a FunctionIdSet instance
    string name;
    char n[FUNCTION_NAME_MAX_SIZE];
    unsigned long int id = 0;

    // loop to generate a (id->function_name) map
    while (index < length) {
        name = (beginning + index)->function_name;
        id = (beginning + index)->id;
        it = region_map->find(id);
        // at the very first time, the *region_map is empty and the region_end hasn't been initialized
        if (region_map->end() == it) {
            // this function has not been added into the map
            // and we are going to add it
            region_map->insert(pair<int, string>(id, name));
        } else {
            // the map has already had a key/value pair in which the key is current id
            // we need to compare the function name to which the id map with current function name
            string_to_char_array(name, n);
            if (name == n) {
                // it should never happen!
                printf("%ld,%-50s already exists!\n", id, n);
            } else {
                // duplicate record, just skip and save time
                continue;
            }
        }
        index++;
    }
}

void string_to_char_array(const string &s, char ch[]) {
    sprintf(ch, "%s", s.c_str());
}



/*
 the following function is reserved just in case you want to know, how many id there are,for each function(name).
 It is not useful to count any longer though.
*/

/**
 * @param beginning
 * @param length
 * @return a map of (function_name, set(id)) pairs
 */
void mergeRegion(FunctionIdSet *beginning, unsigned long int length, function_id_map *region_map) {
    map<string, set<unsigned long int>>::iterator it;
    unsigned long int index = 0;

    // variable to store properties of a FunctionIdSet instance
    string name;
    unsigned long int id = 0;


    while (index < length) {
        name = (beginning + index)->function_name;
        id = (beginning + index)->id;
        it = region_map->find(name);
        // at the very first time, the *region_map is empty and the region_end hasn't been initialized
        if (region_map->end() == it) {
            // this function has not been added into the map
            // and we are going to add it
            set<unsigned long int> id_set;
            id_set.insert(id);
            region_map->insert(pair<string, set<unsigned long int>>(name, id_set));
        } else {
            // the map has already had the function record
            // and we are going to update its value/ add this id in to the id set
            region_map->find(name)->second.insert(id);
        }
        index++;
    }
}