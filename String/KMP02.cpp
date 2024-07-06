//
// Created by mynam on 2024/7/6.
//

//
// Created by mynam on 2024/7/6.
//KMP算法，下标位置为0

#include <iostream>
#include <cstring>
#include <new>

#define MAXSIZE 255

using namespace std;

typedef struct String {
    char *data;
    int length;
    bool isAllocated;
} String;

/**
 * @brief 初始化字符串对象
 *
 * 为给定的字符串对象分配内存空间，并设置其初始状态。
 *
 * @param str 指向要初始化的字符串对象的指针
 *
 * @return 如果初始化成功，则返回true；否则返回false
 */
bool InitString(String *str) {
    // 如果传入的指针为空，则返回false
    if (str == nullptr) {
        return false;
    }
    try {
        // 为字符串对象分配内存空间
        str->data = new char[MAXSIZE];
        // 设置字符串的长度为0
        str->length = 0;
        // 标记字符串的内存是动态分配的
        str->isAllocated = true;
        // 分配成功，返回true
        return true;
    } catch (const bad_alloc &e) {
        // 捕获内存分配失败异常
        cerr << "Memory allocation failed: " << e.what() << endl;
        // 返回false表示初始化失败
        return false;
    }
}


/**
 * @brief 释放字符串内存
 *
 * 释放给定字符串对象的内存，并将其重置为未分配状态。
 *
 * @param str 指向要释放的字符串对象的指针
 *
 * @return 如果成功释放字符串，则返回true；否则返回false
 */
bool FreeString(String *str) {
    // 如果指针为空，则直接返回false
    if (str == nullptr) {
        return false;
    }
    // 如果字符串已分配内存
    if (str->isAllocated) {
        // 释放字符串的data数组内存
        delete[] str->data;
        // 将data指针置为空
        str->data = nullptr;
        // 将字符串长度置为0
        str->length = 0;
        // 标记字符串未分配内存
        str->isAllocated = false;
    }
    // 返回true表示成功释放字符串
    return true;
}


/**
 * @brief 赋值字符串
 *
 * 将给定的字符串赋值给String对象的data成员，并更新String对象的长度。
 *
 * @param S 要被赋值的String对象的指针
 * @param str 要赋值的字符串
 *
 * @return 如果赋值成功，返回true；否则返回false
 *
 * @note 如果S或str为空指针，或者str的长度大于等于MAXSIZE，则赋值失败。
 */
bool AssignString(String *S, const char *str) {
    // 判断指针S和str是否为空
    if (S == nullptr || str == nullptr) {
        return false;
    }
    // 判断字符串str的长度是否大于等于MAXSIZE
    if (strlen(str) >= MAXSIZE) {
        return false;
    }
    // 将字符串str复制到S的data中
    strcpy(S->data , str);
    // 更新S的长度为字符串str的长度
    S->length = strlen(str);
    // 返回true表示赋值成功
    return true;
}


/**
 * @brief 获取字符串的 next 数组
 *
 * 根据给定的字符串 T，计算并填充 next 数组，用于 KMP 算法中的字符串匹配。
 *
 * @param T 字符串对象
 * @param next 指向 next 数组的指针
 */
void get_next(String T, int *next) {
    // 如果字符串T的数据指针为空或者next指针为空，则直接返回
    if (T.data == nullptr || next == nullptr) {
        return;
    }
    int i = 1;
    // 初始化第一个字符的next值为-1
    next[0] = -1;
    int j = 0;
    // 遍历字符串T，从第二个字符开始
    while (i < T.length) {
        // 如果当前字符与j指向的字符相同，或者j为0（即初始位置）
        if (T.data[i] == T.data[j] || j == 0) {
            // i和j都向后移动一位
            i++;
            j++;
            // 如果当前字符与j指向的字符不相同
            if (T.data[i] != T.data[j]) {
                // 将j的值赋给当前字符的next值
                next[i] = j;
            } else {
                // 否则，将j对应的next值赋给当前字符的next值
                next[i] = next[j];
            }
        } else {
            // 如果当前字符与j指向的字符不相同，则将j回溯到其next值所指向的位置
            j = next[j];
        }
    }
}


/**
 * @brief 在字符串S中查找字符串T的首次出现位置（KMP算法）
 *
 * 使用KMP算法在字符串S中从指定位置pos开始查找字符串T的首次出现位置。
 *
 * @param S 主字符串
 * @param T 要查找的子字符串
 * @param pos 开始查找的位置（索引从0开始）
 * @param next 部分匹配表数组
 *
 * @return 如果找到，返回子字符串T在主字符串S中首次出现的位置索引（从0开始）；
 *         如果未找到，则返回-1。
 */
int Index_KPM(String S, String T, int pos, const int *next) {
    // 判断主字符串S、子字符串T以及部分匹配表数组next是否为空
    if (S.data == nullptr || T.data == nullptr || next == nullptr) {
        return -1;
    }
    // 如果开始查找的位置pos大于子字符串T的长度，则无法找到，直接返回-1
    if (pos > T.length) {
        return -1;
    }

    // 初始化指针i指向主字符串S中开始查找的位置pos
    int i = pos;
    // 初始化指针j指向子字符串T的起始位置
    int j = 0;

    // 当指针i没有超出主字符串S的范围且指针j没有超出子字符串T的范围时，继续循环
    while (i <= S.length && j < T.length) {
        // 如果j指向子字符串T的起始位置，或者当前主字符串S的字符与子字符串T的字符相等
        if (j == 0 || S.data[i] == T.data[j]) {
            // 指针i和j都向后移动一位
            i++;
            j++;
        } else {
            // 如果当前主字符串S的字符与子字符串T的字符不相等，则根据部分匹配表数组next将指针j回溯
            j = next[j];
        }
    }

    // 如果指针j等于子字符串T的长度，则说明找到了子字符串T在主字符串S中的位置
    if (j == T.length) {
        // 返回子字符串T在主字符串S中首次出现的位置索引（从0开始）
        return i -T.length;
    } else {
        // 如果没有找到子字符串T，则返回-1
        return -1;
    }
}


int main() {
    String S;
    String T;

    const char *str1 = "Hello, World!!!!!!";
    const char *str2 = "World!!";

    InitString(&S);
    InitString(&T);

    AssignString(&S, str1);
    AssignString(&T, str2);

    int next[90];
    get_next(T, next);
    int pos = Index_KPM(S, T, 1, next);

    cout << pos << endl;

    cout << S.data + 7 << endl;

    FreeString(&S);
    FreeString(&T);
    return 0;
}