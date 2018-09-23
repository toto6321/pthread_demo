#include <cstdlib>
#include <cstdio>
#include <bits/stdc++.h>
#include <ctime>

#include <string>
#include <map>
#include <set>

// my package
#include "include/toto/my_struct.h"
#include "include/toto/read_the_single_file.cpp"
#include "include/toto/read_the_region_file.cpp"
#include "include/toto/count.cpp"


using namespace std;

template<class T>
bool freeMemorySpace(T *p) {
    if (nullptr != p) {
        free(p);
    }
}

int main() {
    bool save_result(const char output[], count_map *count_result);

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
    beginning_write_single = read_the_single_file(write_single_file, &number_of_write_single);
    beginning_region = read_the_region_file(region_file, &number_of_region);

    function_id_map region_map;
    mergeRegion(beginning_region, number_of_region, &region_map);

    map<int, string> region_map2;
    map_region(beginning_region, number_of_region, &region_map2);


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
    count_map count_result2;

    __time_t count1_begin = time(nullptr);
    // count read operation
    count1(&count_result,
           &region_map,
           beginning_read_single,
           number_of_read_single
    );

    // count write operation
    count1(&count_result,
           &region_map,
           beginning_write_single,
           number_of_write_single
    );

    __time_t count1_end = time(nullptr);
    printf("count1 costs %ld\n", count1_end - count1_begin);

    // write count result into file
    const char result_file1[] = "result1.csv";
    save_result(result_file1, &count_result);

    __time_t count1_end2 = time(nullptr);
    printf("save1 costs %ld\n", count1_end2 - count1_end);

    // count2 again
    // count read operation
    __time_t count2_begin = time(nullptr);
    count2(&count_result2,
           &region_map2,
           beginning_read_single,
           number_of_read_single
    );

    // count write operation
    count2(&count_result2,
           &region_map2,
           beginning_write_single,
           number_of_write_single
    );

    __time_t count2_end = time(nullptr);
    printf("count2 costs %ld\n", count2_end - count2_begin);

    const char result_file2[] = "result2.csv";
    save_result(result_file2, &count_result2);

    __time_t count2_end2 = time(nullptr);
    printf("save2 costs %ld\n", count2_end2 - count2_end);

    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    return 0;
}


bool save_result(const char output[], count_map *count_result) {
    char addr_string[60];
    FILE *write_scream = fopen(output, "w");
    for (auto &k: *count_result) {
        string_to_char_array(k.first, addr_string);
        fprintf(write_scream, "%-50s%d\n", addr_string, k.second);
    }
    fclose(write_scream);
    return true;
}








