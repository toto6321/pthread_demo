#include <cstdlib>
#include <cstdio>
#include <cstring>

struct MyTuple {
    int address = 0;
    int id = 0;
    int times = 0;
};

int main() {
    // input file name
    const char read_file[] = "../read_first_100_lines.out";

    // file pointer
    FILE *read_single;

    // char buffer to hold data within fgets()
    char buffer[50];

    // variables to pass data to tuple property
    int operation_id, address, call_id, times;
    float read_timestamp;

    // char pointer to the address where the returned buffer of fgets() starts to be stored.
    char *buffer_string;

    // pointer to the address where the dynamically allocated memory for our data starts
    MyTuple *beginning = NULL ;

    // numbers of our data reading from files
    unsigned long int number_of_read_single = 0;

    unsigned int size_of_my_tuple = sizeof(MyTuple);

    // read the file
    read_single = fopen(read_file, "r");
    if (read_single == nullptr) {
        printf("Reading %s failed!", read_file);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, 50, read_single))) {
        // extract data from the buffer_string
        sscanf(buffer_string, "%d %f %x %d", &operation_id, &read_timestamp, &address, &call_id);
        times = 1;

        // dynamically allocate memory to store our data
        if (number_of_read_single == 0) {
            // number_of_read_singe = 0 means current data is the first, and we need to newly allocate memory space.
            beginning = (MyTuple *) calloc(number_of_read_single + 1, size_of_my_tuple);
        } else {
            // number_of_read_single > 0 means there exist data and we need to resize the memory space by 1 to store current data
            beginning = (MyTuple *) realloc(beginning, size_of_my_tuple * (number_of_read_single + 1));
        }
        (beginning + number_of_read_single)->address = address;
        (beginning + number_of_read_single)->id = call_id;
        (beginning + number_of_read_single)->times = times;

        // count + 1
        number_of_read_single++;

//        printf("%d\t%.1f\t0x%08x\t%d\n", operation_id, read_timestamp, address, call_id);
    }

    printf("Data below is reading from the memory\n");
    for (int i = 0; i < number_of_read_single; i++) {
        printf("0x%08x \t%d \t%d\n", (beginning + i)->address, (beginning + i)->id, (beginning + i)->times);
    }


    fclose(read_single);
    free(beginning);
    return 0;
}
