#include "./Md5.h"
#include "Teacher.h"

using std::cout;
using std::cin;
using std::endl;

//-----------------------------------------------
int main(int argc, char *argv[]) {

    //------------------------------------------
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    //------------------------------------------

    std::cout << "Hello world" << std::endl;

    //----------------------------系统初始化工作
    int ret = 0;

    //......录入 courseID 编号静态数据

    //......录入 教室占用信息
    
    //----------------------------用户登录
    
    bool isTeacher = 0;

    cout << "input user name : ";
    //char userName[BUFSIZ] = {0};
    char *userName = (char *)malloc(BUFSIZ * sizeof(char));
    memset(userName, 0, BUFSIZ);
    ret = getInput(userName, BUFSIZ);
    if (-1 == ret) free(userName);
    SELF_ERROR_CHECK(ret, -1, "input error");

    cout << "intput passwd : ";
    long offset = 0;
    ret = keyVerification(userName, offset, isTeacher);
    if (-1 == ret) free(userName);
    SELF_ERROR_CHECK(ret, -1, "user name or passwd error");

    //cout << isTeacher << endl;
    //cout << offset << endl;  
    
    //----------------------------
    
    if (isTeacher) {    //teacher
        Instructor instructor(userName);
        free(userName);
        ret = instructor.getCourses(offset);    //录入课程列表信息
        SELF_ERROR_CHECK(ret, -1, "course list error");

instructor.print();
return 0;
        while (true) {
            int inputs = 0;
            printf("==========================\n");
            printf("1.create\n");
            printf("2.delete\n");
            printf("3.show\n");
            //scanf("please input : %zu", inputs);
            cin >> inputs;

            //--------------------

            switch (inputs) {
            case 1:
                //create

                break;
            case 2:
                //delete
                break;
            case 3:
                //show
                break;

            default:
                break;
            }

        }
    } else {    //student
        //......
        free(userName);
        //录入课程信息到内存 HashMap 保存 key CourseName : val CourseNum
        //......

        while (true) {

        }
    }

    //------------------------------课程信息写回

    return 0;
}

