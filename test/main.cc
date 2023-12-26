#include <iostream>
#include "./Md5.h"



int main () {

    FILE *file = fopen("./aa", "r+");
    char line[1024] = {0};
    fgets(line, 1024, file);
    fgets(line, 1024, file);
    fgetc(file);
    fputc('1', file);

    fclose(file);
    return 0;
}