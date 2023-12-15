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
    }
    ~User() {
        //释放 Course List 资源
        //......

        free(_name);
    }

public:
    int getCourses(const long &offset);
    int listLoad(const char *courseID, FILE *file);
    
    void print() const;

protected:
    char *_name;
    size_t _courseNum;
    void *_head;
    void *_tail;

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

