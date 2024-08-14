//
// Created by KCY on 24-8-15.
//

#include "KMP_0.h"

bool InitString(String *S) {
    if (S == NULL) {
        printf("Initialization error. Pointer is empty");
        return false;
    }
    S->ch = (char *) malloc(MAXLEN);
    if (S->ch == NULL) {
        printf("malloc errer, Pointer is emptr");
        return false;
    }
    S->length = 0;
    return true;
}

bool FreeString(String *S) {
    if (S == NULL) {
        return false;
    }
    if (S->ch != NULL) {
        free(S->ch);
        S->ch = NULL;
        S->length = 0;
    }
    return true;
}

bool AssignString(String *S, const char *str) {
    if (S == NULL || S->ch == NULL || str == NULL) {
        return false;
    }
    int len = strlen(str);
    if (len >= MAXLEN) {
        return false;
    }
    strcpy(S->ch, str);
    S->length = len;
    return 0;
}

int Index_BF(String S, String T, int pos) {
    if (S.ch == NULL || T.ch == NULL) {
        return -1;
    }
    if (pos < 0 || pos >= MAXLEN) {
        return -1;
    }
    int i = pos;
    int j = 0;
    while (i < S.length && j < T.length) // 从下标0开始
    {
        if (S.ch[i] == T.ch[j]) {
            i++;
            j++;
        } else {
            i = i - j + 1;
            j = 0;
        }
    }
    if (j == T.length) {
        return i - T.length;
    } else {
        return -1;
    }
}

void Get_next(String T, int *next) {
    if (T.ch == NULL || next == NULL) {
        return;
    }
    int i = 0;
    int j = -1;
    next[0] = -1;
    while (i < T.length - 1) {
        if (j == -1 || T.ch[i] == T.ch[j]) {
            i++;
            j++;
            if (T.ch[i] != T.ch[j]) {
                next[i] = j;
            } else {
                next[i] = next[j];
            }
        } else {
            j = next[j];
        }
    }
}

int Index_KMP(String S, String T, int pos, int *next) {
    if (S.ch == NULL || T.ch == NULL || next == NULL) {
        return -1;
    }
    if (pos < 0 || pos >= MAXLEN) {
        return -1;
    }
    int i = pos;
    int j = 0;
    while (i < S.length && j < T.length) {
        if (j == -1 || S.ch[i] == T.ch[j]) {
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
