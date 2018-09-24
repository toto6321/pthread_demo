//
// Created by toto on 9/23/18.
//
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>

using namespace std;

#include "count.h"
#include "my_struct.h"
#include "read_the_region_file.h"


// data type for storing count result during caculation
typedef map<string, int> count_map;

void count1(map<string, int> *count_result,
            map<string, set<int>> *region_map,
            MyStruct *begin,
            unsigned long int number
) {
    string generate_key_of_count_map(int address, const string &name);

    // temp variables used during counting
    int address, call_id;
    string function_name;
    count_map::iterator cursor;

    // const default string to evaluate if the function is found
    const string d = "It cannot be coincident!";

    // for records from read_single file
    for (int i = 0; i < number; i++) {
        // make it a default string so that we can know if the function matched to the id is found
        function_name = d;

        address = (begin + i)->address;
        call_id = (begin + i)->id;
        // first to find out the name of the function which called it
        for (auto &k: *region_map) {
            if (k.second.find(call_id) != k.second.end()) {
                // call_id = id
                function_name = k.first;
                break;
            }
        }

        if (function_name == d) {
            // generally speaking, it won't happen
            printf("call id of 0x%08x doesn't exist in the region file!\n", call_id);
            continue;
        }

        // secondly to make counter ++
        string key = generate_key_of_count_map(address, function_name);
        cursor = count_result->find(key);
        if (cursor != count_result->end()) {
            // if the key/value pair exists, increase it by 1
            cursor->second++;
        } else {
            // if not exist, insert this new record
            count_result->insert(pair<string, int>(key, 1));
        }
    }
}


void count2(map<string, int> *count_result,
            map<int, string> *region_map2,
            MyStruct *begin,
            unsigned long int number
) {
    string generate_key_of_count_map(int address, const string &name);

    map<int, string>::iterator it;

    // temp variables used during counting
    int address, call_id;
    string function_name;
    count_map::iterator cursor;

    // for records from read_single file
    for (int i = 0; i < number; i++) {
        address = (begin + i)->address;
        call_id = (begin + i)->id;
        // first to find out the name of the function which called it
        it = region_map2->find(call_id);
        if (it == region_map2->end()) {
            // generally speaking, it won't happen
            printf("call id of 0x%08x doesn't exist in the region file!\n", call_id);
            continue;
        } else {
            // the function name is found
            function_name = it->second;
        }

        // secondly to make counter ++
        string key = generate_key_of_count_map(address, function_name);
        cursor = count_result->find(key);
        if (cursor != count_result->end()) {
            // if the key/value pair exists, increase it by 1
            cursor->second++;
        } else {
            // if not exist, insert this new record
            count_result->insert(pair<string, int>(key, 1));
        }
    }
}

string generate_key_of_count_map(int address, const string &name) {
    char key[60];
    sprintf(key, "0x%08x,%s", address, name.c_str());
    return (string) key;
}