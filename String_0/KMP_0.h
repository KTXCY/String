//
// Created by KCY on 24-8-15.
//

#ifndef KMP_0_H
#define KMP_0_H


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXLEN 255

typedef struct String {
    char *ch;
    int length;
} String;

bool InitString(String *S);

bool FreeString(String *S);

int Index_BF(String S, String T, int pos);

bool AssignString(String *S, const char *str);

void Get_next(String T, int *next);

int Index_KMP(String S, String T, int pos, int *next);


#endif //KMP_0_H
