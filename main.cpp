#include <stdlib.h>
#include <stdio.h>

/*struct MyTuple {
    int address;
    int id;
    int times;
};*/

int main() {

//    void extract_data(int *operation_id, int *timestamp, float *read_timestamp, int *call_id);

    const char *read_file = "../read_first_100_lines.out";
    FILE *read_single;
    char buffer[50];
    char row[4][25];
    int *operation_id, *address, *call_id, *times;
    float *read_timestamp = 0;
    char *cursor = "a";


    // read the file
    read_single = fopen(read_file, "r");
    if (read_single == NULL) {
        printf("Reading %s failed!", read_file);
        exit(2);
    }

//    char s[50];
    for (int i = 0; i < 1 || cursor != NULL; i++) {
        cursor = fgets(buffer, 50, read_single);
        sscanf(buffer, "[\n]\n", buffer);
        sscanf(buffer, "%s %s %s %s", row[0], row[1], row[2], row[3]);
//        sprintf(s, "%d\t%f\t%x\t%d\n", row[0], row[1], row[2], row[3]);
//        printf(s);
    }

    fclose(read_single);

    printf("Reading %s succeeded!\n", read_file);
    return 0;
}

void extract_data(char buffer[50]) {

}
