#include <cstdlib>
#include <cstdio>

#include <string>
#include <map>
#include <set>

// my package
#include "include/toto/my_struct.h"
#include "include/toto/read_the_single_file.h"
#include "include/toto/read_the_region_file.h"

typedef set<int>::iterator const_iterator;
using namespace std;

template<class T>
bool freeMemorySpace(T *p) {
    if (nullptr != p) {
        free(p);
    }
}

int main() {

    // input files
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
//    beginning_read_single = read_the_single_file(read_single_file, &number_of_read_single);
//    beginning_write_single = read_the_single_file(write_single_file, &number_of_write_single);
    beginning_region = read_the_region_file(region_file, &number_of_region);

    function_id_map region_map;
    mergeRegion(beginning_region, number_of_region, &region_map);

    for (auto &it : region_map) {
        cout << it.first << "\t";
        for (int j : it.second) {
            cout << j << ",";
        }
        cout << endl;
    }


    // do not forget to release the memory space to avoid memory leak!
    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    freeMemorySpace(beginning_region);

    return 0;
}






