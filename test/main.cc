#include <iostream>



int main () {
    FILE *file = fopen("./aa", "r+");

    char str[1024] = {0};

    fgets(str, 1024, file);
    fgets(str, 1024, file);
    fgets(str, 1024, file);

    //fprintf(file, "\n%s", "!!!!");
    fputs("1 0 2 3\n", file);

    fclose(file);
    return 0;
}