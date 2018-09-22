#include <cstdlib>
#include <cstdio>
#include <cstring>

#include "MyStruct.h"
#include "read_the_single_file.h"


int main() {
    // input files

    char read_single_file[] = "../read_first_100_lines.out";
    char write_single_file[] = "../write_first_100_lines.out";

    // pointer to the address where the dynamically allocated memory for our data starts
    MyStruct *beginning_read_single = nullptr;
    MyStruct *beginning_write_single = nullptr;

    // numbers of our data reading from files
    unsigned long int number_of_read_single = 0;
    unsigned long int number_of_write_single = 0;

    // read and extract data from files
    beginning_read_single = read_the_single_file(read_single_file, &number_of_read_single);
    beginning_write_single = read_the_single_file(write_single_file, &number_of_write_single);

    printf("reading lines: %ld\n", sizeof(beginning_read_single));
    printf("reading lines: %ld\n", sizeof(beginning_write_single));
    printf("reading lines: %ld\n", number_of_read_single);
    printf("reading lines: %ld\n", number_of_write_single);

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

    // do not forget to release the memory space to avoid memory leak!
    free(beginning_read_single);
    free(beginning_write_single);
    
    return 0;
}


