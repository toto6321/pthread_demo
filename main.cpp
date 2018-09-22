#include <cstdlib>
#include <cstdio>
#include <cstring>

/*struct MyTuple {
    int address;
    int id;
    int times;
};*/

int main() {

    const char read_file[] = "../read_first_100_lines.out";
    FILE *read_single;
    char buffer[50];
    int operation_id, address, call_id, times;
    float read_timestamp;
    char *buffer_string;

    // read the file
    read_single = fopen(read_file, "r");
    if (read_single == nullptr) {
        printf("Reading %s failed!", read_file);
        exit(2);
    }

    while (nullptr != (buffer_string = fgets(buffer, 50, read_single))) {
        printf("%s", buffer_string);
        sscanf(buffer_string, "%d %f %x %d", &operation_id, &read_timestamp, &address, &call_id);
        printf("%d\t%.1f\t0x%08x\t%d\n", operation_id, read_timestamp, address, call_id);

        printf("\n");
    }

    fclose(read_single);

    printf("Reading %s succeeded!\n", read_file);
    return 0;
}
