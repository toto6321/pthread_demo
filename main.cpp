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
    char region_file[] = "../region_exception.out";

    // pointer to the address where the dynamically allocated memory for our data starts
    MyStruct *beginning_read_single = nullptr;
    MyStruct *beginning_write_single = nullptr;
    FunctionIdSet *beginning_region = nullptr;

    // numbers of our data reading from files
    unsigned long int number_of_read_single = 0;
    unsigned long int number_of_write_single = 0;
    unsigned long int number_of_region = 0;

    // read and extract data from files
    __time_t read_read_file_start = time(nullptr);
    __time_t read_read_file_end = time(nullptr);
    printf("%-50s%lds\n", "reading read_single file costs", read_read_file_end - read_read_file_start);
    beginning_read_single = read_the_single_file(read_single_file, &number_of_read_single);

    __time_t read_write_file_start = time(nullptr);
    beginning_write_single = read_the_single_file(write_single_file, &number_of_write_single);
    __time_t read_write_file_end = time(nullptr);
    printf("%-50s%lds\n", "reading write_single file costs", read_write_file_end - read_write_file_start);

    __time_t read_region_file_start = time(nullptr);
    beginning_region = read_the_region_file(region_file, &number_of_region);
    __time_t read_region_file_end = time(nullptr);
    printf("%-50s%lds\n", "reading region file costs", read_region_file_end - read_region_file_start);



/*
     For each variable/address, to count the total number of read operation and write operation from the same instance call.
     Since the read record and write record has same structure, we could count in read record and write record sequentially first,
     and then go to multi-thread calculation
*/


    __time_t start_to_generate_map_str_set_int = time(nullptr);

    // to create a map<string, set<int>> used for counting
    function_id_map region_map;
    mergeRegion(beginning_region, number_of_region, &region_map);

    __time_t end_up_map_generation_str_set_int = time(nullptr);
    printf("%-50s%lds\n", "generating region map<string, set<int>> costs",
           end_up_map_generation_str_set_int - start_to_generate_map_str_set_int);

    count_map count_result;

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
    printf("%-20s%lds\n", "count1 costs:", count1_end - count1_begin);

    // write count result into file
    const char result_file1[] = "result1_origin.csv";
    save_result(result_file1, &count_result);

    __time_t save1_end = time(nullptr);
    printf("%-20s%lds\n", "save1 costs", save1_end - count1_end);


    /* count2 again */

    __time_t start_to_generate_region_map_int_str = time(nullptr);

    // to create a map<int, string> used for counting
    map<int, string> region_map2;
    map_region(beginning_region, number_of_region, &region_map2);

    __time_t end_up_generating_region_map_int_str = time(nullptr);
    printf("%-50s%lds\n", "generating region map<string, set<int>> costs",
           end_up_generating_region_map_int_str - start_to_generate_region_map_int_str);

    count_map count_result2;

    __time_t count2_begin = time(nullptr);
    // count read operation
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
    printf("%-20s%lds\n", "count2 costs", count2_end - count2_begin);

    const char result_file2[] = "result2_origin.csv";
    save_result(result_file2, &count_result2);

    __time_t save2_end = time(nullptr);
    printf("%-20s%lds\n", "save2 costs", save2_end - count2_end);



    // do not forget to release the memory space to avoid memory leak!
    freeMemorySpace(beginning_region);
    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    return 0;
}


bool save_result(const char output[], count_map *count_result) {
    char addr_string[60];
    FILE *write_scream = fopen(output, "w");

    for (auto &k: *count_result) {
        string_to_char_array(k.first, addr_string);
        fprintf(write_scream, "%s,%d\n", addr_string, k.second);
    }
    fclose(write_scream);
    return true;
}







