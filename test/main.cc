#include <iostream>
#include "./Md5.h"

#define BUFSIZE (1024)

using std::cout;
using std::cin;
using std::endl;

int main () {

    char className[BUFSIZE] = {0};   //className
    printf("class name : "); scanf("%s", className);
    className[BUFSIZE - 1] = '\0';
cout << "className  = " << className << endl;
    setbuf(stdin, NULL);

    // instructorName = _name

    size_t Credit;
    printf("Ctedit : "); fgets(buffer, sizeof(buffer), stdin);
    if (Credit > 3 || 0 == Credit) {
        printf("Credit erro\n");
        return -1;
    }

    return 0;
}