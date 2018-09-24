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

using namespace std;

#ifndef HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H
#define HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H

#endif //HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H

FunctionIdSet *read_the_region_file(char *file_name, unsigned long int *number) {
    if (number == nullptr) {
        printf("the number pointer is null pointer");
        exit(2);
    }

    const unsigned int size_of_function_id_set = sizeof(FunctionIdSet);

    FunctionIdSet *beginning = nullptr;

    FILE *input_stream = nullptr;

    const int buffer_size = 200;
    char buffer[buffer_size];
    char *buffer_string;

    int id = -1;
    char type[10] = "", function_name[50] = "";

    input_stream = fopen(file_name, "r");
    if (input_stream == nullptr) {
        printf("Reading %s failed!", file_name);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, buffer_size, input_stream))) {
        if (sscanf(buffer_string, "%d %s %s", &id, type, function_name) < 3) {
            // there will be no exception even though sscanf cannot extract data as expected
            // and in that case the variables will remain what they are.
            // we have to deal with this special case
            continue;
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


/**
 *
 * @param begin
 * @param length
 * @details sort the (function, id) set
 */

void sort_region(FunctionIdSet *begin, unsigned long int length) {
    // sort out them by function name in alphabet order
    bool select_sort(FunctionIdSet array[], unsigned long int length);

    select_sort(begin, length);
}

// used in sort_region function
bool select_sort(FunctionIdSet array[], unsigned long int length) {
    bool swap_value(FunctionIdSet *left, FunctionIdSet *right);

    for (int i = 0; i < length - 1; i++) {
        for (unsigned long int j = length - 1; j > i; j--) {
            if (strcmp(array[i].function_name, array[j].function_name) > 0) {
                if (!swap_value(&array[i], &array[j])) {
                    exit(3);
                }
            }
        }
    }

    return true;
}

// used in select_sort function
bool swap_value(FunctionIdSet *left, FunctionIdSet *right) {
    bool function_id_set_assign(FunctionIdSet *des, FunctionIdSet *src);

    FunctionIdSet middleman;
    // assign right to the middleman first
    function_id_set_assign(&middleman, right);

    // assign left to right
    function_id_set_assign(right, left);

    // assign middleman(in essence, right value) to left
    function_id_set_assign(left, &middleman);

    return true;
}

// used in swap_value function
bool function_id_set_assign(FunctionIdSet *des, FunctionIdSet *src) {
    strcpy(des->function_name, src->function_name);
    des->id = src->id;
    return true;
}


/**
 *
 * @param beginning
 * @param length
 * @return a map of (function_name, id) pairs
 */
void mergeRegion(FunctionIdSet *beginning, unsigned long int length, function_id_map *region_map) {
    map<string, set<int>>::iterator it;
    unsigned long int index = 0;

    // variable to store properties of a FunctionIdSet instance
    string name;
    int id = 0;


    while (index < length) {
        name = (beginning + index)->function_name;
        id = (beginning + index)->id;
        it = region_map->find(name);
        // at the very first time, the *region_map is empty and the region_end hasn't been initialized
        if (region_map->end() == it) {
            // this function has not been added into the map
            // and we are going to add it
            set<int> id_set;
            id_set.insert(id);
            region_map->insert(pair<string, set<int>>(name, id_set));
        } else {
            // the map has already had the function record
            // and we are going to update its value/ add this id in to the id set
            region_map->find(name)->second.insert(id);
        }
        index++;
    }
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
    char n[50];
    int id = 0;


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
            // the map has already had the function record
            // it shouldn't happen!
            string_to_char_array(name, n);
            printf("%+10d%-50s already exists!\n", id, n);
        }
        index++;
    }
}

void string_to_char_array(const string &s, char ch[]) {
    sprintf(ch, "%s", s.c_str());
}

