#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MyStruct.h"
#include "read_the_single_file.h"



int main() {
    // input files

     char read_single_file[] = "../read_first_100_lines.out";
//    const char *write_single_file = "../write_first_100_lines.out";

    // pointer to the address where the dynamically allocated memory for our data starts
    MyStruct *beginning_read_single = nullptr;
//    MyStruct *beginning_write_single = nullptr;

    // numbers of our data reading from files
    unsigned long int ZERO = 0;
    unsigned long int *number_of_read_single = &ZERO;
//    unsigned long int *number_of_write_single = &ZERO;

    // read and extract data from files
    beginning_read_single = read_the_single_file(read_single_file, number_of_read_single);

    printf("Data below is reading from the memory\n");
    for (int i = 0; i < *number_of_read_single; i++) {
        printf("0x%08x \t%d \t%d\n", (beginning_read_single + i)->address, (beginning_read_single + i)->id,
               (beginning_read_single + i)->times);
    }

    free(beginning_read_single);
    return 0;
}


