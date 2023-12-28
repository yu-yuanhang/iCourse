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
    getCourseID(currCourseID);
//printf("currCourseID = %zu\n", currCourseID);
    
    //----------------------------用户登录
    
    bool isTeacher = 0;

    cout << "input user name : ";
    //char userName[BUFSIZE] = {0};
    char *userName = (char *)malloc(BUFSIZE * sizeof(char));
    memset(userName, 0, BUFSIZE);
    ret = getInput(userName, BUFSIZE);
    if (-1 == ret) free(userName);
    SELF_ERROR_CHECK(ret, -1, "input error");

    cout << "intput passwd : ";
    ret = keyVerification(userName, isTeacher);
    if (-1 == ret) free(userName);
    SELF_ERROR_CHECK(ret, -1, "user name or passwd error");

//cout << isTeacher << endl;
 
    
    //----------------------------
    
    bool flag = true;
    if (isTeacher) {    //teacher
        Instructor instructor(userName);
        free(userName);
        ret = instructor.getCourses();    //录入课程列表信息
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
                ERROR_CHECK(file, nullptr, "can not open file")
                //if (file == nullptr) {
                //cerr << "can not open file" << endl;
                //return -1;
                //}

                char classroom[BUFSIZE] = {0};
                size_t maxSeats = 0;
                printf("please input classroom ID : "); scanf("%s", classroom);
                if (checkClassroom(classroom, file, maxSeats) != 0) {
                    printf("Can not find this classroom\n");
                    fclose(file);
                    break;
                }
                size_t week = 0;
                size_t sort = 0;
                printf("week : "); scanf("%zu", &week);
                printf("sort : "); scanf("%zu", &sort);

                if (ret = checkTime(week, sort, file) != 0) {
                    if (-1 == ret) {
                        printf("Time conflict\n");
                    } else if (-2 == ret) {
                        printf("Time error\n");
                    }
                    fclose(file);
                    break;
                }
                
                //输入课程信息
                ret = instructor.addCourse(classroom, week, sort, currCourseID, maxSeats);
            
                //......更新文件
                //CourseInfo
                User::wbCourseInfo_add_course(instructor._tail);
                //UserInfo 
                User::wbUserInfo(instructor._id, instructor._head);
                //Classroom
                User::wbClassroom(((Basic *)instructor._tail)->_classroom, ((Basic *)instructor._tail)->_classTime, '1');
                fclose(file);
            }
                break;
            case 2:
                //delete
                break;
            case 3:
                //show
                instructor.print();
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

