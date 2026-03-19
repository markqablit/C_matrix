#include "io.h"
#include "stdio.h"

int type_select(){
    char c = '0';
    while (c != '1' && c != '2'){
        puts("Select matrix type:\n1 - double type\n2 - complex type");
        c = getchar();
        if (c == '1') return 1;
        else if (c == '2') return 2;
        puts("Wrong select");
    }
}

int action_select(){
    char c = '0';
    while (c != '1' && c != '2'){
        puts("Select action:\n1 - create matrix\n2 - delete amtrix\n3 - set elem\n4 - get elem\n5 - unput matrix\n6 - exit");
        c = getchar();
        switch (c)
        {
        case '1':
            return 1;
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        default:
            puts("Wrong select");
        }
        puts("Wrong type");
    }
}




