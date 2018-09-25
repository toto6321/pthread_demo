//
// Created by toto on 9/23/18.
//
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <set>
#include <cstring>

#include "my_struct.h"

using namespace std;

#ifndef HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H
#define HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H
typedef map<string, set<unsigned long int>> function_id_map;
#endif //HOMEWORK1_TIANHUAN_TU_READ_THE_REGION_FILE_H


FunctionIdSet *read_the_region_file(char *file_name, unsigned long int *number);

void sort_region(FunctionIdSet *begin, unsigned long int length);

bool select_sort(FunctionIdSet array[], unsigned long int length);

bool swap_value(FunctionIdSet *left, FunctionIdSet *right);

bool function_id_set_assign(FunctionIdSet *des, FunctionIdSet *src);

void mergeRegion(FunctionIdSet *beginning, unsigned long int length, function_id_map *region_map);