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
