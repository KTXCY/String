//
// Created by KCY on 24-8-15.
//

#include "KMP_1.h"

int main()
{
    String S;
    String T;
    const char *str1 = "Hello, World";
    const char *str2 = "World";
    InitString(&S);
    InitString(&T);
    AssignString(&S, str1);
    AssignString(&T, str2);

    printf("%s\n", S.ch + 1);
    printf("%s\n", T.ch + 1);

    int a = Index_BF(S, T, 1);

    printf("%d\n", a);

    printf("%s\n", S.ch + a);

    int next[MAXLEN];
    Get_next(T, next);

    int b = Index_KMP(S, T, 1, next);


    printf("%d\n", b);

    printf("%s\n", S.ch + b);

    FreeString(&S);
    FreeString(&T);
    return 0;
}