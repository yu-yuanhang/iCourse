#include "./Teacher.h"

int User::getCourses() {
    char filePath[BUFSIZE] = {0};
    sprintf(filePath, "%s%s", USERINFO, this->_id);
//cout << "filePath = " << filePath << endl;

    FILE *file_U = fopen(filePath, "r");
    char line[BUFSIZE] = {0};
    char courseID[MINIBUFSIZE] = {0};
    //设置偏移量
    for (int i = 0; i < 2; ++i) fgets(line, BUFSIZE, file_U);
    memset(line, 0, BUFSIZE);
    fgets(line, BUFSIZE, file_U);
//printf("%d : %c\n", line[0], line[0]);

    //fseek(file_U, offset, SEEK_SET);
    //if (fgets(line, BUFSIZE, file_U) == nullptr) {fclose(file_U);return -1;}
    if (line[0] == 0) {fclose(file_U);return 0;}

    FILE *file_C = fopen(COURSEINFO, "r");
    if (nullptr == file_C) fclose(file_U);
    ERROR_CHECK(file_C, nullptr, "can not open courseInfo");

//cout << "line = " << line << endl;
    int idx = 0, curr = 0;
    while (true) {
        while (32 != line[idx] && '\0' != line[idx]) {
            courseID[curr++] = line[idx];
            ++idx;
        }
//cout << "courseID = " << courseID << endl;
        //--------------------添加课程列表信息
        int ret = listLoad(courseID, file_C);
        if ('\0' == line[idx++]) break;
        curr = 0;
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

    char line[BUFSIZE] = {0};
    while (fgets(line, BUFSIZE, file) != nullptr) {
        if ('0' == line[0]) {
            for (int i = 0; i < 10; ++i) {
                fgets(line, BUFSIZE, file);
            }
        } else if('1' == line[0]) {
            memset(line, 0, BUFSIZE);
            fgets(line, BUFSIZE, file);
            if (0 == strncmp(line, courseID, strlen(courseID))) {
                // 加载课程信息到列表
                size_t tmpID = strtoul(courseID, NULL, 10); // courseID
                char classroom[CLASSEIDLENGTH + 2] = {0};   // classroom
                fgets(classroom, sizeof(classroom), file);
                classroom[CLASSEIDLENGTH] = '\0';
                memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
                line[strlen(line) - 1] = '\0';
                size_t hour = strtoul(line, NULL, 10);         // hour
                char classTime[CLASSTiMELENGTH + 2 + 1] = {0}; // classtime type
                fgets(classTime, sizeof(classTime), file);
                classTime[CLASSTiMELENGTH + 1] = '\0';
                ClassType type;
                if ('0' == classTime[CLASSTiMELENGTH]) type = eLesson;
                else type = eLabs;
                char className[BUFSIZE] = {0}; // className
                fgets(className, BUFSIZE, file);
                className[strlen(className) - 1] = '\0';
                char instructorName[BUFSIZE] = {0}; // instructorName
                fgets(instructorName, BUFSIZE, file);
                instructorName[strlen(instructorName) - 1] = '\0';
                memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
                line[strlen(line) - 1] = '\0';
                size_t Credit = strtoul(line, NULL, 10); // Credit
                memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
                line[strlen(line) - 1] = '\0';
                size_t maxSeats = strtoul(line, NULL, 10); // maxSeats
                memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
                line[strlen(line) - 1] = '\0';
                size_t spareSeats = strtoul(line, NULL, 10); // spareSeats
                memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
                line[strlen(line) - 1] = '\0';
                size_t fileNum = strtoul(line, NULL, 10); // fileNum

                // 此处申空间但是没有进行内存初始化
                if (nullptr == _head) {
                    // 判断课程类型
                    if (eLesson == type)
                        _head = new Lesson(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
                    else
                        _head = new Labs(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);

                    _tail = _head;
                } else {
                    void *ptmp = nullptr;
                    if (eLesson == type)
                        ptmp = new Lesson(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);
                    else
                        ptmp = new Labs(tmpID, classroom, hour, classTime, type, className, instructorName, Credit, maxSeats, spareSeats, fileNum);

                    // if (eLesson == ((Basic *)_tail)->getType()) ((Lesson *)_tail)->_next = (void *)ptmp;
                    // else ((Labs *)_tail)->_next = (void *)ptmp;

                    ((Basic *)_tail)->_next = (void *)ptmp;

                    _tail = ptmp;
                }

                // 更新 CourseNum 信息
                ++_courseNum;
                break;
            }

            for (int i = 0; i < 9; ++i) {
                // memset(line, 0, strlen(line));
                fgets(line, BUFSIZE, file);
            }
        } else {
            //...
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
    void *ptmp = _head;
    for(int i = 0; i < _courseNum; ++i) {
        printf("---------------------\n");
        if (eLesson == ((Basic *)ptmp)->getType()) ((Lesson *)ptmp)->print();
        else ((Labs *)ptmp)->print();
        ptmp = (void *)((Basic *)ptmp)->_next;
    }
    return;
}

int Instructor::addCourse(const char *classroom, size_t week, size_t sort, size_t &currCourseID, size_t maxSeats) {

    if (nullptr == classroom) return -1;
    // 对于 week 和 sort 正确性检查实现在函数外 check 函数

    // courseID classroom
    
    size_t hour;
    printf("hour : "); scanf("%zu", &hour); //hour
    if(hour > 80 || hour < 10) {
        printf("hour error\n");
        return -1;
    }

    int tmp;
    char classTime[CLASSTiMELENGTH + 1] = {0};  //classTime
    sprintf(classTime, "%zu%zu", week - 1, sort - 1);
    ClassType type;                             //type
    printf("course Type : 0 = lesson , 1 = lab : "); scanf("%d", &tmp);
    if (0 == tmp) {
        type = eLesson;
    } else if (1 == tmp) {
        type == eLabs;
    } else {
        printf("type error\n");
        return -1;
    }
//printf("tmp = %d\n", tmp);

    char className[BUFSIZE] = {0};   //className
    printf("class name : "); 
    fgetc(stdin); fgets(className, BUFSIZE, stdin);
    className[BUFSIZE - 1] = '\0';
    if ('\n' == className[strlen(className) - 1]) className[strlen(className) - 1] = '\0'; 
//cout << "className  = " << className << endl;
    setbuf(stdin, NULL);

    // instructorName = _name

    size_t Credit;
    printf("Ctedit : "); scanf("%zu", &Credit);
    if (Credit > 3 || 0 == Credit) {
        printf("Credit erro\n");
        return -1;
    }
    
    //maxSeat == spearSeat
    
    size_t fileNum = 0;

    if (nullptr == _head) {
    //判断课程类型
        if (eLesson == type) _head = new Lesson(currCourseID, classroom, hour, classTime, type, className, _name, Credit, maxSeats, maxSeats, fileNum);
        else _head = new Labs(currCourseID, classroom, hour, classTime, type, className, _name, Credit, maxSeats, maxSeats, fileNum);
          
        _tail = _head;
    } else {
        void *ptmp = nullptr;
        if (eLesson == type) ptmp = new Lesson(currCourseID, classroom, hour, classTime, type, className, _name, Credit, maxSeats, maxSeats, fileNum);
        else ptmp = new Labs(currCourseID, classroom, hour, classTime, type, className, _name, Credit, maxSeats, maxSeats, fileNum);
                
        //if (eLesson == ((Basic *)_tail)->getType()) ((Lesson *)_tail)->_next = (void *)ptmp;
        //else ((Labs *)_tail)->_next = (void *)ptmp;

        ((Basic *)_tail)->_next = (void *)ptmp;

        _tail = ptmp;
    }

    //更新 CourseNum 信息
    ++_courseNum;
    ++currCourseID;

    return 0;
}

//================================================================

int User::wbCourseInfo_add_course(const void *tail) {
    if (nullptr == tail) return -1;

    FILE *file = fopen(COURSEINFO, "a+");
    ERROR_CHECK(file, nullptr, "CourseInfo open error");
    //if (nullptr == file) {
    //    printf("CourseInfo open error\n");
    //    return -1;
    //}

    char str[BUFSIZE] = {0};

    fputs("\n1", file); //有效位
    ulong_to_string(str, ((Basic *)tail)->_courseID);  //CourseID
    fprintf(file, "\n%s", str);
    memset(str, 0, BUFSIZE);
    fprintf(file, "\n%s", ((Basic *)tail)->_classroom);    //classroom
    ulong_to_string(str, ((Basic *)tail)->_hour);  //hour
    fprintf(file, "\n%s", str);
    memset(str, 0, BUFSIZE);
    fprintf(file, "\n%s", ((Basic *)tail)->_classTime);    //classTime
    if (eLesson == ((Basic *)tail)->_classType) {
        fputs("0", file);  //classType

        fprintf(file, "\n%s", ((Lesson *)tail)->_className);
        fprintf(file, "\n%s", ((Lesson *)tail)->_instructorName);
        ulong_to_string(str, ((Lesson *)tail)->_Credit);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Lesson *)tail)->_maxSeats);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Lesson *)tail)->_spareSeats);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Lesson *)tail)->_fileNum);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
    }
    else {
        fputs("1", file);

        fprintf(file, "\n%s", ((Labs *)tail)->_className);
        fprintf(file, "\n%s", ((Labs *)tail)->_instructorName);
        ulong_to_string(str, ((Labs *)tail)->_Credit);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Labs *)tail)->_maxSeats);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Labs *)tail)->_spareSeats);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
        ulong_to_string(str, ((Labs *)tail)->_fileNum);
        fprintf(file, "\n%s", str);
        memset(str, 0, BUFSIZE);
    }
    
    fclose(file);

    return 0;
}

int User::wbClassroom(const char *classroom, const char *time, char value) {
    if (nullptr == classroom || nullptr == time) return -1;

    FILE *file = fopen(CLASSROOM, "r+");
    ERROR_CHECK(file, nullptr, "Classroom open error");

    char line[BUFSIZE] = {0};
    while (nullptr != fgets(line, BUFSIZE, file)) {
        line[strlen(line) - 1] = '\0';
        if (0 == strcmp(line, classroom)) {
            fgets(line, BUFSIZE, file);
            memset(line, 0, BUFSIZE);
            line[0] = time[0];
            size_t sort = string_to_ulong(line);
            for (int i = 0; i < sort; ++i) fgets(line, BUFSIZE, file);
            memset(line, 0, BUFSIZE);

            line[0] = time[1];
            sort = string_to_ulong(line);
            for (int i = 0; i < sort; ++i) fgetc(file);
            fputc(value, file);

            fclose(file);
            return 0;
        }
    }

    printf("classroom error\n");
    fclose(file);
    return -1;
}

int User::wbUserInfo(const char *id, void *head) {
    if (nullptr == id) return -1;

    char filePath[BUFSIZE] = {0};
    sprintf(filePath, "%s%s", USERINFO, id);
    FILE *file = fopen(filePath, "r+");
    
    char line[BUFSIZE] = {0};
    fgets(line, BUFSIZE, file);
    fgets(line, BUFSIZE, file);
    memset(line, 0, BUFSIZE);

    size_t pos = ftell(file);
    ftruncate(fileno(file), pos);

    if (nullptr == head) {
        fclose(file);
        return 0;
    }

    Basic *tmp = (Basic *)head;
    while (true) {
        ulong_to_string(line, tmp->_courseID);
        fputs(line, file);
        tmp = (Basic *)tmp->_next;
        if (nullptr == tmp) break;
        fputc(32, file);
    }

    fclose(file);
    return 0;
}