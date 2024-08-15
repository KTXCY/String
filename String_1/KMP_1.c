//
// Created by KCY on 24-8-15.
//

#include "KMP_1.h"

bool InitString(String *S)
{
    if (S == NULL)
    {
        return false;
    }
    S->ch = (char *)malloc(MAXLEN + 1);
    if (S->ch == NULL)
    {
        return false;
    }
    S->ch[0];
    S->length = 0;
    return true;
}

bool FreeString(String *S)
{
    if (S == NULL)
    {
        return false;
    }
    if (S->ch)
    {
        free(S->ch);
        S->ch = NULL;
        S->length = 0;
    }
    return true;
}

bool AssignString(String *S, const char *str)
{
    if (S == NULL || S->ch == NULL || str == NULL)
    {
        return false;
    }
    int Len = strlen(str);
    if (Len >= MAXLEN)
    {
        return false;
    }
    strcpy(S->ch + 1, str);
    S->length = Len;
    return true;
}

int Index_BF(String S, String T, int pos)
{
    if (S.ch == NULL || T.ch == NULL)
    {
        return -1;
    }
    if (pos < 1 || pos > S.length)
    {
        return -1;
    }
    int i = pos;
    int j = 1;
    while (i <= S.length || j <= T.length)
    {
        if (S.ch[i] == T.ch[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T.length)
    {
        return i - T.length;
    }
    else
    {
        return -1;
    }
}

int Index_KMP(String S, String T, int pos, int *next)
{
    if (S.ch == NULL || T.ch == NULL || next == NULL)
    {
        return -1;
    }
    if (pos < 1 || pos > S.length)
    {
        return -1;
    }

    int i = pos;
    int j = 1;
    while (i <= S.length || j <= T.length)
    {
        if (S.ch[i] == T.ch[j] || j == 0)
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }
    }
    if (j > T.length)
    {
        return i - T.length;
    }
    else
    {
        return -1;
    }
}

bool Get_next(String T, int *next)
{
    if (T.ch == NULL || next == NULL)
    {
        return false;
    }
    int i = 1;
    int j = 0;
    next[0] = 0;
    next[1] = 0;
    while (i < T.length)
    {
        if (j == 0 || T.ch[i] == T.ch[j])
        {
            i++;
            j++;
            if (T.ch[i] != T.ch[j])
            {
                next[i] = j;
            }
            else
            {
                next[i] = next[j];
            }
        }
        else
        {
            j = next[j];
        }
    }
    return true;
}