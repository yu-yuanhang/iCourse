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

    size_t currCourseID = 0;
    

    
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
    
    bool flag = true;
    if (isTeacher) {    //teacher
        Instructor instructor(userName);
        free(userName);
        ret = instructor.getCourses(offset);    //录入课程列表信息
        SELF_ERROR_CHECK(ret, -1, "course list error");

//instructor.print();
//return 0;

        while (flag) {
            int inputs = 0;
            printf("==========================\n");
            printf("1.create\n");
            printf("2.delete\n");
            printf("3.show\n");
            printf("4.exit\n");   
            printf("please input : ");     
            scanf("%d", &inputs);

//printf("%d\n", inputs);

            //--------------------

            switch (inputs) {
            case 1: 
            {
                //-------------------------create

                //输入教室和时间 判断是否冲突

                FILE *file = fopen(CLASSROOM, "r");
                if (file == nullptr) {
                cerr << "can not open file" << endl;
                return -1;
                }

                char classroom[BUFSIZ] = {0};
                printf("please input classroom ID : "); scanf("%s", classroom);
                if (checkClassroom(classroom, file) != 0) {
                    printf("Can not find this classroom\n");
                    fclose(file);
                    break;
                }
                size_t week = 0;
                size_t sort = 0;
                printf("week : "); scanf("%zu", &week);
                printf("sort : "); scanf("%zu", &sort);
                if (!(week <=5 && week > 0) || !(sort <= 4 && sort > 0)) {
                    printf("Time error\n");
                    fclose(file);
                    break;
                }   

                if (checkTime(week, sort, file) != 0) {
                    printf("Time conflict\n");
                    fclose(file);
                    break;
                }
                
                //......输入课程信息

                //......更新文件

                fclose(file);
            }
                break;
            case 2:
                //delete
                break;
            case 3:
                //show
                break;
            case 4:
                //exit
                printf("byebye\n");
                flag = false;
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

        while (flag) {

        }
    }

    //------------------------------课程信息写回

    return 0;
}

