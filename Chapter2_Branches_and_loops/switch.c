#include <stdio.h>
#include <string.h>
#include<stdlib.h>
int main(void) {
    int input = 3;
    // printf("Hello World\n");
    switch (input) {
        case 1:
        case 2:
        case 3:
        case 4:
            printf("%d\n",4);
            break;
        case 5:
            break;
        default: printf("result: %d\n",5);

    }

    return 0;
}
