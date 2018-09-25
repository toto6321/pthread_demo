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


void count(map<string, int> *count_result,
           map<unsigned long int, string> *region_map,
           MyStruct *begin,
           unsigned long int index_start,
           unsigned long int index_end,
           pthread_rwlock_t *rwlock
) {
    string generate_key_of_count_map(int address, const string &name);

    map<unsigned long int, string>::iterator it;

    // temp variables used during counting
    int address;
    unsigned long int call_id;
    string function_name;
    map<string, int>::iterator cursor;

    // for records from read_single file
    for (unsigned long int i = index_start; i <= index_end; i++) {
        address = (begin + i)->address;
        call_id = (begin + i)->id;

        /* first to find out the name of the function which called it */
        // when you are searching in the region_map, you don't have to lock it because all threads just read from it.

        it = region_map->find(call_id);

        if (it == region_map->end()) {
            // generally speaking, it won't happen
            printf("call id of %ld doesn't exist in the region file!\n", call_id);
            continue;
        } else {
            // the function name is found
            function_name = it->second;
        }

        /* secondly to make counter ++ */

        string key = generate_key_of_count_map(address, function_name);
        // When you are searching in the map of count_result, you have to lock it because other threads might be updating it.
        pthread_rwlock_rdlock(rwlock);
        cursor = count_result->find(key);
        pthread_rwlock_unlock(rwlock);

        // Definitely, it is not allowed to either read or write the map.
        pthread_rwlock_wrlock(rwlock);
        if (cursor != count_result->end()) {
            // if the key/value pair exists, increase it by 1
            cursor->second++;
        } else {
            // if not exist, insert this new record
            count_result->insert(pair<string, int>(key, 1));
        }
        pthread_rwlock_unlock(rwlock);
    }
}

string generate_key_of_count_map(int address, const string &name) {
    char key[60];
    sprintf(key, "%#x,%s", address, name.c_str());
    return (string) key;
}