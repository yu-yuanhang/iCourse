#  basic

int number

char *classroom

size_t hour

classTime

virtual getClassInfo

# lesson

type enum lesson

char *className

char *instructorName

size_t Credit

最大人数

剩余位置

课程大纲 // 

课件 //

# labs

type enum labs

char *className

char *instructorName

size_t Credit

最大人数

剩余位置

课程大纲 // 

实验内容 //

# instructor

char *name 

size_t age

ClassList classList 

# student

char *name 

size_t age

ClassList classList 


//------------------------------------------------CourseInfo 格式
0                           CourseID
c101                        classroom
36                          hour
120                         week2 第三节 将授课
Advanced operating system   CourseName
dingyan                     instructorName
3                           credit
60                          最大人数
60                          当前人数
0                           课程大纲:课件 的数量

//----------------------------------Courseware 课件/实验 命名规则
CourseID_filename

//----------------------------------FileInfo 格式(模拟 大纲和课件)
有效位 courseID  0(大纲):1(课件或实验)  文件名



