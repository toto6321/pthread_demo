#include <stdlib.h>
#include <stdio.h>


/*struct MyTuple {
    int address;
    int id;
    int times;
};*/

int main() {

    const char *read_file = "read_first_100_lines.out";
    FILE *read_single = fopen(read_file, "r");
    char *buffer;
    int *operation_id = 0, *address = 0, *call_id = 0, times = 0;
    float *read_timestamp = 0;
    if (read_single == NULL) {
        printf("Reading %s failed!", read_file);
        exit(2);
    }
/*    while (EOF != fscanf(read_single, "%d %f %d %d", operation_id, read_timestamp, address, call_id)) {
        printf("%d\t%f\t%d\t%d", *operation_id, *read_timestamp, *address, *call_id);
    }*/

    fclose(read_single);

    printf("Reading %s succeeded!\n", read_file);
    return 0;
}

/*
void extract_data(int *operation_id, int *timestamp, float *read_timestamp, int *call_id) {

}*/
