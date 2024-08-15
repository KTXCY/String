//
// Created by KCY on 24-8-15.
//

#ifndef KMP__H
#define KMP__H


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 255

typedef struct String
{
    char *ch;
    int length;
} String;

bool InitString(String *S);

bool FreeString(String *S);

bool AssignString(String *S, const char *str);

int Index_BF(String S, String T, int pos);

int Index_KMP(String S, String T, int pos, int *next);

bool Get_next(String T, int *next);

#endif //KMP__H
