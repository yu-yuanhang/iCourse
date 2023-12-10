SRC:=$(wildcard ./*.cc) $(wildcard ./CourseInfo/*.cc)
OBJ:=$(patsubst %.cc, %.o, $(SRC))

iCourse=./iCourse

ALL:$(iCourse)

$(iCourse):$(OBJ)
	g++ $^ -o $@
%.o:%.c
	g++ -c $^ -o $@ -g

.PHONY:clear rebuild print
clear:
	$(RM) $(OBJ) $(iCourse)
rebuild:clear ALL
print:
	echo $(OBJ)


