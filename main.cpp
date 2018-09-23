#include <cstdlib>
#include <cstdio>
#include <bits/stdc++.h>

#include <string>
#include <map>
#include <set>

// my package
#include "include/toto/my_struct.h"
#include "include/toto/read_the_single_file.h"
#include "include/toto/read_the_region_file.h"

// data type for storing count result during caculation
typedef map<string, int> count_map;

using namespace std;

template<class T>
bool freeMemorySpace(T *p) {
    if (nullptr != p) {
        free(p);
    }
}

/**
 * this method is aimed at converting a string to a given char array
 * @param s
 * @param ch
 * @return
 */
void string_to_char_array(const string &s, char ch[]) {
    sprintf(ch, "%s", s.c_str());
}

int main() {
    string generate_key_of_count_map(int address, const string &name);

    // input files
    // because I use CLion and the executable output directory is the cmake-build-debug.
    // so the relative path should be ../XXX
    char read_single_file[] = "../read_first_100_lines.out";
    char write_single_file[] = "../write_first_100_lines.out";
    // the origin region.out has an unsupported first line. remove it with bash command "sed -i "1,1d" region.out"
    char region_file[] = "../region_first_100_lines.out";

    // pointer to the address where the dynamically allocated memory for our data starts
    MyStruct *beginning_read_single = nullptr;
    MyStruct *beginning_write_single = nullptr;
    FunctionIdSet *beginning_region = nullptr;

    // numbers of our data reading from files
    unsigned long int number_of_read_single = 0;
    unsigned long int number_of_write_single = 0;
    unsigned long int number_of_region = 0;

    // read and extract data from files
    beginning_read_single = read_the_single_file(read_single_file, &number_of_read_single);
//    beginning_write_single = read_the_single_file(write_single_file, &number_of_write_single);
    beginning_region = read_the_region_file(region_file, &number_of_region);

    function_id_map region_map;
    mergeRegion(beginning_region, number_of_region, &region_map);

/*

    for (auto &it : region_map) {
        cout << it.first << "\t";
        for (int j : it.second) {
            cout << j << ",";
        }
        cout << endl;
    }
*/


    // do not forget to release the memory space to avoid memory leak!
    // now the data from region.out in memory become useless
    freeMemorySpace(beginning_region);


    // for each variable/address,
    // to count the total number of read operation and write operation from the same instance call
    // since the read record and write record has same structure.
    // we could count in read record and write record sequentially first,
    // and then go to multi-thread calculation

    // to create an enormous Map to save result during the calculation
    count_map count_result;
    count_map::iterator cursor;
    // temp variables used during counting
    int address, call_id;
    string function_name;


    // for records from read_single file
    for (int i = 0; i < number_of_read_single; i++) {
        address = (beginning_read_single + i)->address;
        call_id = (beginning_read_single + i)->id;
        // first to find out the name of the function which called it
        for (auto &k: region_map) {
            if (k.second.find(call_id) != k.second.end()) {
                // call_id = id
                function_name = k.first;
                break;
            }
        }

        // secondly to make counter ++
        string key = generate_key_of_count_map(address, function_name);
        cursor = count_result.find(key);
        if (cursor != count_result.end()) {
            // if the key/value pair exists, increase it by 1
            cursor->second++;
        } else {
            // if not exist, insert this new record
            count_result.insert(pair<string, int>(key, 1));
        }
    }

    char addr_string[20];
    for (auto &k: count_result) {
        string_to_char_array(k.first, addr_string);
        printf("%-50s%d\n", addr_string, k.second);
    }


    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    return 0;
}

string generate_key_of_count_map(int address, const string &name) {
    char key[60];
    sprintf(key, "%08x_%s", address, name.c_str());
    return (string) key;
};






