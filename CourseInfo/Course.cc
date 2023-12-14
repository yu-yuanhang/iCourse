#include "./Course.h"

using std::cout;
using std::cin;
using std::endl;

//-----------------------------------

size_t Basic::_currentID = 0;

//-----------------------------------

//Lesson::Lesson() {}
//Lesson::~Lesson() {}

int Lesson::getClassInfo() {
    return 0;
}


//-----------------------------------


//Labs::Labs() {}
//Labs::~Labs() {}

int Labs::getClassInfo() {
    return 0;
}

void Lesson::print() const {
    //printf("void print() const\n");
    printf("courseID : %zu\n\
classroom : %s\n\
hour : %zu\n\
classtime : week %c num %c\n\
classtype : %s\n\
className : %s\n\
teacherName : %s\n\
Credit : %zu\n\
maxSeats : %zu\n\
spareSeats : %zu\n\
fileNum : %zu\n\
", _courseID, _classroom, _hour, _classTime[0] + 1, _classTime[1] + 1,\
_classType == eLesson ? "Lesson" : "Labs",\
_className, _instructorName, _Credit, _maxSeats, _spareSeats, _fileNum);
}

void Labs::print() const {
    //printf("void print() const\n");
    printf("courseID : %zu\n\
classroom : %s\n\
hour : %zu\n\
classtime : week %c num %c\n\
classtype : %s\n\
className : %s\n\
teacherName : %s\n\
Credit : %zu\n\
maxSeats : %zu\n\
spareSeats : %zu\n\
fileNum : %zu\n\
", _courseID, _classroom, _hour, _classTime[0] + 1, _classTime[1] + 1,\
_classType == eLesson ? "Lesson" : "Labs",\
_className, _instructorName, _Credit, _maxSeats, _spareSeats, _fileNum);
}