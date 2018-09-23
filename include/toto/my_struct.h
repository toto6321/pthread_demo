//
// Created by toto on 9/22/18.
//

#ifndef HOMEWORK1_TIANHUAN_TU_MYSTRUCT_H
#define HOMEWORK1_TIANHUAN_TU_MYSTRUCT_H

// data type for storing read records and write records
typedef struct{
    int address;
    int id;
} MyStruct;

// data type for storing region record
typedef struct{
    int id;
    char function_name[50];
} FunctionIdSet;

#endif //HOMEWORK1_TIANHUAN_TU_MYSTRUCT_H