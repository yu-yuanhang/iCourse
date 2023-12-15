#include "./head.h"

int getInput(char *input, size_t length) {
    if (nullptr == input) {
        return -1;
    }

    char ch;
    int i = 0;
    while ((ch = getchar()) != '\n') {
        input[i++] = ch;
        if (i > length) return -1;
    }
    return 0;
}

int getFileLine(const char *filePath, char *line, size_t length) {

    if (nullptr == filePath && nullptr == line) return -1;

    FILE *file = fopen(filePath, "r");
    if (file == nullptr) {
        std::cerr << "can not open file" << std::endl;
        return -1;
    }

    if (fgets(line, length, file) != nullptr) {
        std::cout << line << std::endl;
    } else {
        std::cerr << "read file error" << std::endl;
    }

    fclose(file);
    return 0;
}

int checkClassroom(const char *classroom, FILE *file, size_t &maxSeats) {

    if (nullptr == classroom && nullptr == file) return -1;

    char line[BUFSIZ] = {0};
    while (fgets(line, BUFSIZ, file) != nullptr) {
        line[strlen(line) - 1] = '\0';
        if (strcmp(line, classroom) == 0) {
            memset(line, 0, BUFSIZ);
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            maxSeats = string_to_ulong(line);
            return 0;
        }

        for(int i = 0; i < 6; ++i) fgets(line, BUFSIZ, file);
        memset(line, 0, BUFSIZ);
    }

    return -1;

}

int checkTime(size_t week, size_t sort, FILE *file) {

    if (nullptr == file) return -1;

    if (!(week <=5 && week > 0) || !(sort <= 4 && sort > 0)) {
        return -2;
    }   

    char line[BUFSIZ] = {0};
    for(int i = 0; i < week - 1; ++i) {
        fgets(line, BUFSIZ, file);
    }
    memset(line, 0, BUFSIZ);
    fgets(line, BUFSIZ, file);

//printf("%s\n", line);

    if ('1' == line[sort - 1]) return -1;
    else if ('0' == line[sort - 1]) return 0;

    return -1;
}

int getCourseID(size_t &currCourseID) {

    FILE *file = fopen(COURSEINFO, "r");
    if (file == nullptr) {
        std::cerr << "can not open file" << std::endl;
        return -1;
    }

    char line[BUFSIZ] = {0};

    bool flag = true;

    while (flag) {
        if (fgets(line, BUFSIZ, file) == nullptr) break;
        line[strlen(line) - 1] = '\0';
        currCourseID = string_to_ulong(line);
        ++currCourseID;
        
        for (int i = 0; i < 9; ++i) fgets(line, BUFSIZ, file);
        memset(line, 0, BUFSIZ);
    }

    return 0;
}

unsigned long string_to_ulong(char* str) {
    return strtoul(str, NULL, 10);
}

int ulong_to_string(char *str,unsigned long num) {
    sprintf(str, "%lu", num);
    return 0;
}
