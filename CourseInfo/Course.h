#pragma once

#include "./../head.h"

#define CLASSEIDLENGTH (4)
#define CLASSTiMELENGTH (2)

enum ClassType {
    eLesson,
    eLabs,
};

class Basic {
public:
    Basic(size_t courseID, const char *classroom, size_t hour, const char *classTime, ClassType classType):
    _next(nullptr),
    _courseID(courseID),
    _classroom{'\0','\0','\0','\0','\0'},
    _hour(hour),
    _classTime{'\0','\0','\0',},
    _classType(classType)
    {
        if (nullptr == classroom && nullptr == classTime) return;
        strncpy(_classroom, classroom, CLASSEIDLENGTH);
        strncpy(_classTime, classTime, CLASSTiMELENGTH);
    }
    ~Basic() {}

    ClassType getType() const {
        return _classType;
    }

protected:
    int getCurrentID();
    virtual int getClassInfo () = 0;//更具课程ID录入课程信息
    

public:
    void *_next;
    static size_t _currentID;//初始化为 0

protected:
    size_t _courseID;
    char _classroom[CLASSEIDLENGTH + 1];
    size_t _hour;
    char _classTime[CLASSTiMELENGTH + 1];
    ClassType _classType;

private:

};

class Lesson : protected Basic {
public:
    Lesson(size_t courseID, const char *classroom, size_t hour, const char *classTime, ClassType classType, const char* className, const char *instructorName, size_t Credit, size_t maxSeats, size_t spareSeats, size_t fileNum):
    Basic(courseID, classroom, hour, classTime, classType),
    _className(nullptr),
    _instructorName(nullptr),
    _Credit(Credit),
    _maxSeats(maxSeats),
    _spareSeats(spareSeats),
    _fileNum(fileNum)
    {
        if (nullptr == className && nullptr == instructorName) return;

        _className = (char *)malloc((strlen(className) + 1) * sizeof(char));
        memset(_className, 0, strlen(className) + 1);
        strncpy(_className, className, strlen(className) + 1);

        _instructorName = (char *)malloc((strlen(instructorName) + 1) * sizeof(char));
        memset(_instructorName, 0, strlen(instructorName) + 1);
        strncpy(_instructorName, instructorName, strlen(instructorName) + 1);
    }
    ~Lesson() {
        free(_instructorName);
        free(_className);
        //_next 的释放逻辑由 链表整体负责
    };

    void print() const;

protected:
    int getClassInfo () override;

protected:
private:
    char *_className;
    char *_instructorName;
    size_t _Credit;
    size_t _maxSeats;
    size_t _spareSeats;
    
    //课程大纲 课件
    //......
    size_t _fileNum;
public:
};

class Labs : protected Basic {
public:
    Labs(size_t courseID, const char *classroom, size_t hour, const char *classTime, ClassType classType, const char* className, const char *instructorName, size_t Credit, size_t maxSeats, size_t spareSeats, size_t fileNum):
    Basic(courseID, classroom, hour, classTime, classType),
    _className(nullptr),
    _instructorName(nullptr),
    _Credit(Credit),
    _maxSeats(maxSeats),
    _spareSeats(spareSeats),
    _fileNum(fileNum)
    {
        if (nullptr == className && nullptr == instructorName) return;

        _className = (char *)malloc((strlen(className) + 1) * sizeof(char));
        memset(_className, 0, strlen(className) + 1);
        strncpy(_className, className, strlen(className) + 1);

        _instructorName = (char *)malloc((strlen(instructorName) + 1) * sizeof(char));
        memset(_instructorName, 0, strlen(instructorName) + 1);
        strncpy(_instructorName, instructorName, strlen(instructorName) + 1);
    }
    ~Labs() {
        free(_instructorName);
        free(_className);
    };

    void print() const;


protected:
    int getClassInfo () override;
    
protected:
private:
    char *_className;
    char *_instructorName;
    size_t _Credit;
    size_t _maxSeats;
    size_t _spareSeats;
    
    //课程大纲 课件
    //......
    size_t _fileNum;
public:
};




