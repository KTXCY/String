/*************************************************************************
        > File Name: String.c
        > Author: XYC
        > Mail: kitschxcy@outlook.com
        > Created Time: 2024年07月08日 星期一 10时01分13秒
 ************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 256

typedef struct String {
    char *data;
    int length;
} String;

bool InitString(String *base) {
    if (base == NULL) {
        return false;
    }
    base->data = (char *) malloc(sizeof(char) * MAXSIZE);
    if (base->data == NULL) {
        return false;
    }
    base->length = 0;
    return true;
}

bool FreeString(String *base) {
    if (base == NULL) {
        return false;
    }
    if (base->data != NULL) {
        free(base->data);
        base->data = NULL;
        base->length = 0;
    }
    return true;
}

bool AssignString(String *base, const char *str) {
    if (base == NULL || str == NULL) {
        return false;
    }
    if (strlen(str) >= MAXSIZE) {
        return false;
    }
    strcpy(base->data, str);
    base->length = strlen(str);
    return true;
}

/*
int Index_BF(String S, String T, int pos){
    if(pos < 0 || pos > MAXSIZE - 1){
        return -1;
    }
    if(S.data == NULL || T.data == NULL){
        return -1;
    }
    int i = pos;
    int j = 0;
    while(i < S.length && j < T.length){
        if(S.data[i] == T.data[j]){
            i++;
            j++;
        }else{
            i = i - j + 1;
            j = 0;
        }
    }
    if(j == T.length){
        return i - T.length;
    }else{
        return -1;
    }
}
*/

void get_next(String T, int *next) {
    if (T.data == NULL || next == NULL) {
        return;
    }
    int i = 0;
    int j = -1;
    next[0] = -1;
    while (i < T.length - 1) {
        if (j == -1 || T.data[i] == T.data[j]) {
            i++;
            j++;
            if (T.data[i] != T.data[j]) {
                next[i] = j;
            } else {
                next[i] = next[j];
            }
        } else {
            j = next[j];
        }

    }
}

int Index_KMP(String S, String T, int pos, const int *next) {
    if (pos < 0 || pos > S.length - 1) {
        return -1;
    }
    if (next == NULL || S.data == NULL || T.data == NULL) {
        return -1;
    }

    int i = pos;
    int j = 0;
    while (i < S.length && j < T.length) {
        if (j == -1 || S.data[i] == T.data[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
    }
    if (j == T.length) {
        return i - T.length;
    } else {
        return -1;
    }

}

int main() {
    String S;
    String T;
    const char *str1 = "Hello, World!!!!!!!!!!!!!!!!";
    const char *str2 = "World";

    InitString(&S);
    InitString(&T);

    AssignString(&S, str1);
    AssignString(&T, str2);
    printf("%s\n", S.data);
    printf("%s\n", T.data);

    int next[MAXSIZE];
    get_next(T, next);

    int i = Index_KMP(S, T, 0, next);

    printf("%d\n", i);

    printf("%s\n", S.data + i);

    FreeString(&S);
    FreeString(&T);
    return 0;
}