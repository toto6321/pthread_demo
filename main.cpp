#include <stdlib.h>
#include <stdio.h>
#include <bits/stdc++.h>
#include <ctime>
#include <pthread.h>

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

bool save_result(const char output[], map<string, int> *count_result) {
    char addr_string[FUNCTION_NAME_MAX_SIZE + 10 + 1];
    FILE *write_scream = fopen(output, "w");

    for (auto &k: *count_result) {
        string_to_char_array(k.first, addr_string);
        fprintf(write_scream, "%s,%d\n", addr_string, k.second);
    }
    fclose(write_scream);
    return true;
}

typedef struct {
    map<string, int> *count_result;
    map<int, string> *region_map;
    MyStruct *address_begin;
    unsigned long int index_begin;
    unsigned long int index_end;
} MyStruct2;


void *thread_function(void *p) {
    __time_t count_begin = time(nullptr);
    MyStruct2 *pointer = (MyStruct2 *) p;
    count(
            pointer->count_result,
            pointer->region_map,
            pointer->address_begin,
            pointer->index_begin,
            pointer->index_end
    );
    __time_t count_end = time(nullptr);
    printf("%-50s%lds\n", "multi-threads counting costs", count_end - count_begin);
}

int main() {

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


    // multi-thread numbers
    int number_of_threads = 0;
    printf("How many threads do you allow:\t");
    scanf("%d", &number_of_threads);


    /* According to some experiments, it has better performance to read file(s) with single thread.
     * (Sequential reading performance will get worse when the number of threads increase)
     * Refer to <http://www.drdobbs.com/parallel/multithreaded-file-io/220300055?pgno=2>.
     *
     * I don't use multi-thread to find the files.
     * */

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

    __time_t start_to_generate_region_map = time(nullptr);

    // to create a map<int, string> used for counting
    map<int, string> region_map;
    map_region(beginning_region, number_of_region, &region_map);

    __time_t end_up_generating_region_map_int_str = time(nullptr);
    printf("%-50s%lds\n", "generating region map<int, string> costs",
           end_up_generating_region_map_int_str - start_to_generate_region_map);

    map<string, int> count_result;


    /* multi-threads count*/

    if (number_of_threads > 1) {
        /* create threads */
        int extra_number_of_threads = number_of_threads - 1;
        unsigned long int offset = 0;

        // for read_single data
        offset = (unsigned long int) (int) ceil((number_of_read_single) / extra_number_of_threads);
        // to gain best performance, I am going to try to make it as even as possible

        // create another (number_of_threads-1) threads
        pthread_t threads[extra_number_of_threads];
        // int array to save return value of extra threads
        int thread_return_values[extra_number_of_threads];

        for (int i = 0; i < extra_number_of_threads; i++) {
            unsigned long int index_end = offset * i - 1;
            if (index_end >= number_of_read_single) {
                index_end = number_of_read_single - 1;
            }
            MyStruct2 parameter_struct = {&count_result, &region_map, beginning_read_single, offset * i, index_end};
            thread_return_values[i] = pthread_create(
                    threads + i,
                    nullptr,
                    thread_function,
                    (void *) &parameter_struct
            );
        }

        for (int j = 0; j < extra_number_of_threads; j++) {
            pthread_join(threads[j], nullptr);
        }


        // for read_single data
        offset = (unsigned long int) (int) ceil((number_of_read_single) / extra_number_of_threads);
        // to gain best performance, I am going to try to make it as even as possible

        // create another (number_of_threads-1) threads
        pthread_t threads2[extra_number_of_threads];
        // int array to save return value of extra threads
        int thread_return_values2[extra_number_of_threads];

        for (int i = 0; i < extra_number_of_threads; i++) {
            unsigned long int index_end = offset * i - 1;
            if (index_end >= number_of_write_single) {
                index_end = number_of_write_single - 1;
            }
            MyStruct2 parameter_struct = {&count_result, &region_map, beginning_write_single, offset * i, index_end};
            thread_return_values2[i] = pthread_create(
                    threads2 + i,
                    nullptr,
                    thread_function,
                    (void *) &parameter_struct
            );
        }


        for (int j2 = 0; j2 < extra_number_of_threads; j2++) {
            pthread_join(threads[j2], nullptr);
        }


    } else if (number_of_threads > 0) {
        // only main thread
    } else {
        printf("Please input a positive integer!\n");
    }

    __time_t count_end = time(nullptr);

    const char result_file[] = "result.csv";
    save_result(result_file, &count_result);

    __time_t save_end = time(nullptr);
    printf("%-50s%lds\n", "saving costs", save_end - count_end);





    // do not forget to release the memory space to avoid memory leak!
    freeMemorySpace(beginning_region);
    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    return 0;
}













