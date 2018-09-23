#include <cstdlib>
#include <cstdio>

#include <string>
#include <map>
#include <set>
/*
// Standford cslib package
#include "StanfordCPPLib/collections/hashmap.h"
#include "StanfordCPPLib/collections/hashset.h"
*/

// my package
#include "my_struct.h"
#include "read_the_single_file.h"
#include "read_the_region_file.h"

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

/*
    printf("##### read single file: \n");
    for (int i = 0; i < number_of_read_single; i++) {
        printf("0x%08x \t%d \t%d\n", (beginning_read_single + i)->address, (beginning_read_single + i)->id,
               (beginning_read_single + i)->times);
    }

    printf("##### write single file: \n");
    for (int i = 0; i < number_of_write_single; i++) {
        printf("0x%08x \t%d \t%d\n", (beginning_write_single + i)->address, (beginning_write_single + i)->id,
               (beginning_write_single + i)->times);
    }
*/

/*
// since we have hashmap, sorting become unnecessary
//    sort_region(beginning_region, number_of_region);

    printf("##### region file: \n");
    for (int i = 0; i < number_of_region; i++) {
        printf("%-25s %d\n", (beginning_region + i)->function_name, (beginning_region + i)->id);
    }
*/

//    HashMap<string, HashSet<int>> *region_map;
    map<string, set<int>> *region_map;
    region_map = mergeRegion(beginning_region, number_of_region);

    map<string, set<int>>::iterator it = region_map->begin();
    for (; it != region_map->end(); it++) {
        std::cout << it->first;
        for (const_iterator j = it->second.begin(); j != it->second.end(); j++) {
            cout << *j << "," << endl;
        }
    }
//    cout << region_map->keys() << endl;

    // do not forget to release the memory space to avoid memory leak!
    freeMemorySpace(beginning_read_single);
    freeMemorySpace(beginning_write_single);
    freeMemorySpace(beginning_region);

    return 0;
}






