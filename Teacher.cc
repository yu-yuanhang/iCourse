#include "./Teacher.h"

int User::getCourses(const long &offset) {
    FILE *file_U = fopen(USERINFO, "r");
    ERROR_CHECK(file_U, nullptr, "can not open userInfo");

    char line[BUFSIZ] = {0};
    char courseID[MINIBUFSIZE] = {0};
    //设置偏移量
    fseek(file_U, offset, SEEK_SET);
    if (fgets(line, BUFSIZ, file_U) == nullptr) {fclose(file_U);return -1;}
    if (line[0] == '\n') {fclose(file_U);return 0;}

    FILE *file_C = fopen(COURSEINFO, "r");
    if (nullptr == file_C) fclose(file_U);
    ERROR_CHECK(file_C, nullptr, "can not open courseInfo")

    int idx = 0;
    while (true) {
        while (32 != line[idx] && '\n' != line[idx]) {
            courseID[idx] = line[idx];
            ++idx;
        }

        //--------------------添加课程列表信息
        int ret = listLoad(courseID, file_C);

        if ('\n' == line[idx++]) break;
        memset(courseID, 0, strlen(courseID));
    }

    fclose(file_C);
    fclose(file_U);
    return 0;
}

int User::listLoad(const char *courseID, FILE *file) {

    if (nullptr == courseID && nullptr == file) return -1;

    //重置文件偏移量
    fseek(file, 0, SEEK_SET);

    char line[BUFSIZ] = {0};
    while (fgets(line, BUFSIZ, file) != nullptr) {
        if (0 == strncmp(line, courseID, strlen(courseID))) {
            //加载课程信息到列表
            size_t tmpID = strtoul(courseID, NULL, 10);//courseID
            char classroom[CLASSEIDLENGTH + 2] = {0};//classroom
            fgets(classroom, sizeof(classroom), file);
            classroom[CLASSEIDLENGTH] = '\0';
            memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            size_t hour = strtoul(line, NULL, 10);//hour
            char classTime[CLASSTiMELENGTH + 2 + 1] = {0};//classtime type
            fgets(classTime, sizeof(classTime), file);
            classTime[CLASSTiMELENGTH + 1] = '\0';
            ClassType type;
            if('0' == classTime[CLASSTiMELENGTH]) type = eLesson;
            else type = eLabs;
            char className[BUFSIZ] = {0};//className
            fgets(className, BUFSIZ, file);
            className[strlen(className) - 1] = '\0';
            char instructorName[BUFSIZ] = {0};//instructorName
            fgets(instructorName, BUFSIZ, file);
            instructorName[strlen(instructorName) - 1] = '\0';
            memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            size_t Credit = strtoul(line, NULL, 10);//Credit
            memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            size_t maxSeats = strtoul(line, NULL, 10);//maxSeats
            memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            size_t spareSeats = strtoul(line, NULL, 10);//spareSeats
            memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
            line[strlen(line) - 1] = '\0';
            size_t fileNum = strtoul(line, NULL, 10);//fileNum

            //此处申空间但是没有进行内存初始化
            if (nullptr == _head) {
                //判断课程类型
                if (eLesson == type) _head = new Lesson(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
                else _head = new Labs(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
          
                _tail = _head;
            } else {
                void *ptmp = nullptr;
                if (eLesson == type) ptmp = new Lesson(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
                else ptmp = new Labs(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
                
                if (eLesson == ((Basic *)_tail)->getType()) ((Lesson *)_tail)->_next = (void *)ptmp;
                else ((Labs *)_tail)->_next = (void *)ptmp;

                _tail = ptmp;
            }

            //更新 CourseNum 信息
            ++_courseNum;
            break;
        }
        
        for (int i = 0; i < 9; ++i) {
            //memset(line, 0, strlen(line));
            fgets(line, BUFSIZ, file);
        }
        memset(line, 0, strlen(line));
    }

    //fseek(file, 0, SEEK_SET);
    return 0;
}


void User::print() const {
    if (0 == _courseNum) {
        printf("no Courses information\n");
        return;
    }
    for(int i = 0; i < _courseNum; ++i) {
        
    }
    return;
}