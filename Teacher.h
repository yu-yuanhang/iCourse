#pragma once

#include "./head.h"
#include "./CourseInfo/Course.h"

class User {
public:
    User(const char *name):
    _name(nullptr),
    _courseNum(0),
    _head(nullptr),
    _tail(nullptr)
    {
        _name = (char *)malloc((strlen(name) + 1) * sizeof(char));
        memset(_name, 0, strlen(name) + 1);
        strncpy(_name, name, strlen(name));
        //录入 ID信息
        getUserID(_name, _id);
    }
    ~User() {
        //释放 Course List 资源
        //......

        free(_name);
    }

public:
    int getCourses();
    int listLoad(const char *courseID, FILE *file);
    
    void print() const;
    //---------------------------------------------------------
    static int wbCourseInfo_add_course(const void *tail);
    static int wbClassroom(const char *classroom, const char *time, char value);
    static int wbUserInfo(const char *id, void *head);
    static int wbFilesInfo();
    //---------------------------------------------------------
public:
    char *_name;
    size_t _courseNum;
    void *_head;
    void *_tail;
    char _id[USERIDLENGTH] ={0};
};

class Instructor : public User {
public:
    Instructor(const char *name): User(name) {
        //....
    }
    ~Instructor() {}

    int addCourse(const char *classroom, size_t week, size_t sort, size_t &currCourseID, size_t maxSeats);

public:
protected:
//-------------------------------------------

};

class Student : public User {
public:
    Student(const char *name): User(name) {
        //....
    }
    ~Student() {}

public:
protected:
//-------------------------------------------

};

