#ifndef HEAD_H
#define HEAD_H

#include <iostream>
#include <stdio.h>
#include <memory.h>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::cerr;

#define CLASSROOM "./Resourse/Classroom"
#define COURSEINFO "./Resourse/CourseInfo"
#define USERINFO "./Resourse/User/"
#define USERIDINFO "./Resourse/UserInfo"

#define BUFSIZE (1024)
#define MINIBUFSIZE (128)
#define USERIDLENGTH ((3) + (1))

/* #define ARGC_CHECK(argc, num) {\ */
/*     if(argc != num) {\ */
/*         fprintf(stderr, "args error!\n");\ */
/*         return -1;\ */
/*     }\ */
/* } */

#define ERROR_CHECK(ret, num, msg) {\
    if(ret == num) {\
        perror(msg);\
        return -1;\
    }\
}

#define SELF_ERROR_CHECK(ret, num, msg) {\
    if(ret == num) {\
        cout << msg << endl;\
        return -1;\
    }\
}


/* #define THREAD_ERROR_CHECK(ret, msg) {\ */
/*     if(ret != 0) {\ */
/*         fprintf(stderr, "%s:%s\n", msg, strerror(ret));\ */
/*     }\ */
/* } */

//----------------------------------------------------------------
int getInput(char *input, size_t length);
int getFileLine(const char *filePath, char *line, size_t length);

int checkClassroom(const char *classroom, FILE *file, size_t &maxSeats);
int checkTime(size_t week, size_t sort, FILE *file);

int getCourseID(size_t &currCourseID);
int getUserID(const char *userName, char *ID);

//==================================================================

unsigned long string_to_ulong(char* str);
int ulong_to_string(char *str,unsigned long num);


#endif
