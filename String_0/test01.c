//
// Created by KCY on 24-8-15.
//

#include "KMP_0.h"

int main() {
    String S;
    String T;

    const char *str1 = "Hello, World";
    const char *str2 = "World";

    InitString(&S);
    InitString(&T);

    AssignString(&S, str1);
    AssignString(&T, str2);

    printf("%s\n", S.ch);
    printf("%s\n", T.ch);

    printf("This is BF arithmetic\n");
    int a = Index_BF(S, T, 0);
    printf("%d\n", a);

    printf("This is KMP arithmetic\n");
    int next[MAXLEN];
    Get_next(T, next);
    a = Index_KMP(S, T, 0, next);
    printf("%d\n", a);


    FreeString(&T);
    FreeString(&S);
    return 0;
}
