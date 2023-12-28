#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned long string_to_ulong(char* str) {
    return strtoul(str, NULL, 10);
}

int ulong_to_string(char *str,unsigned long num) {
    sprintf(str, "%lu", num);
    return 0;
}

int getCourseID(size_t &currCourseID) {

    // currCourseID 初始化为 0

    FILE *file = fopen("./../Resourse/courseInfo", "r");
    if (file == nullptr) {
        std::cerr << "can not open file" << std::endl;
        return -1;
    }

    char line[BUFSIZ] = {0};

    bool flag = true;

    while (flag) {
        if (fgets(line, BUFSIZ, file) == nullptr) break;
        if ('0' == line[0]) {   //有效位判断
            for (int i = 0; i < 10; ++i) fgets(line, BUFSIZ, file);
            memset(line, 0, BUFSIZ);
        } else if ('1' == line[0]) {
            memset(line, 0, BUFSIZ);
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            currCourseID = string_to_ulong(line);
            ++currCourseID;
        
            for (int i = 0; i < 9; ++i) fgets(line, BUFSIZ, file);
            memset(line, 0, BUFSIZ);
        } else {
            //...
        }
    }

    return 0;
}

enum test {
    a,
    b,
    c
};

int main(int argc, char *argv[]) {
    std::cout << "Hello world" << std::endl;

    size_t curr = 0;

    getCourseID(curr);
    cout << curr << endl;

    return 0;
}

