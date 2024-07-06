//
// Created by mynam on 2024/7/6.
//KMP算法，下标0位置不存元素

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
 * 初始化给定的字符串对象，为其分配内存空间，并设置初始状态。
 *
 * @param str 指向要初始化的字符串对象的指针
 *
 * @return 如果初始化成功，则返回 true；否则返回 false
 */
bool InitString(String *str) {
    // 如果传入的字符串指针为空，则直接返回false
    if (str == nullptr) {
        return false;
    }
    try {
        // 为字符串对象的data成员分配内存空间，大小为MAXSIZE+1
        str->data = new char[MAXSIZE + 1];
        // 在字符串的第一个位置插入一个'#'字符
        str->data[0] = '#';
        // 初始化字符串的长度为0
        str->length = 0;
        // 标记字符串的内存是动态分配的
        str->isAllocated = true;
        // 初始化成功，返回true
        return true;
    } catch (const bad_alloc &e) {
        // 捕获内存分配失败异常，并输出错误信息
        cerr << "Memory allocation failed: " << e.what() << endl;
        // 返回false表示初始化失败
        return false;
    }
}


/**
 * @brief 释放字符串内存
 *
 * 释放给定字符串对象的内存，并将相关成员变量重置为默认值。
 *
 * @param str 指向要释放的字符串对象的指针
 *
 * @return 如果成功释放内存，则返回 true；否则返回 false
 */
bool FreeString(String *str) {
    // 如果字符串对象指针为空，则直接返回false
    if (str == nullptr) {
        return false;
    }
    // 如果字符串对象的内存是动态分配的
    if (str->isAllocated) {
        // 释放字符串的内存
        delete[] str->data;
        // 将data指针置为空
        str->data = nullptr;
        // 将字符串长度置为0
        str->length = 0;
        // 标记字符串内存未分配
        str->isAllocated = false;
    }
    // 返回true表示成功释放字符串内存
    return true;
}


/**
 * @brief 将字符串赋值给String对象
 *
 * 将给定的C风格字符串`str`赋值给String对象`S`的`data`成员，并更新`S`的长度。
 *
 * @param S 指向String对象的指针
 * @param str 要赋值的C风格字符串
 *
 * @return 如果赋值成功，则返回true；否则返回false
 *
 * @note 字符串`str`的长度必须小于等于`MAXSIZE`，因为`data`成员的第一个字符位置被保留用于其他用途（如标记）
 */
bool AssignString(String *S, const char *str) {
    // 如果S或str为空指针，则返回false
    if (S == nullptr || str == nullptr) {
        return false;
    }
    // 如果字符串str的长度大于等于MAXSIZE+1，则返回false
    if (strlen(str) >= MAXSIZE + 1) {
        return false;
    }
    // 将字符串str从S->data的第二个位置开始拷贝（因为第一个位置被保留）
    strcpy(S->data + 1, str);
    // 更新S的长度为字符串str的长度
    S->length = strlen(str);
    // 赋值成功，返回true
    return true;
}


/**
 * @brief 获取字符串的 next 数组
 *
 * 根据给定的字符串 T，生成其 next 数组并保存到 next 指针指向的数组中。
 * next 数组用于 KMP 字符串匹配算法中。
 *
 * @param T 字符串对象
 * @param next 存储 next 数组的整数指针
 */
void get_next(String T, int *next) {
    // 如果字符串 T 的数据指针为空或者 next 指针为空，则直接返回
    if (T.data == nullptr || next == nullptr) {
        return;
    }
    int i = 1;
    // next[0] 初始化为 0，表示字符串 T 的第一个字符的 next 值为 0
    next[0] = 0;
    // next[1] 初始化为 0，表示字符串 T 的第二个字符的 next 值也为 0（通常用于简化算法逻辑）
    next[1] = 0;
    int j = 0;
    // 遍历字符串 T 的每个字符
    while (i < T.length) {
        // 如果当前字符与 j 指向的字符相同，或者 j 为 0（即初始位置）
        if (T.data[i] == T.data[j] || j == 0) {
            i++;
            j++;
            // 如果当前字符与 j 指向的字符不相同
            if (T.data[i] != T.data[j]) {
                // 将 j 的值赋给当前字符的 next 值
                next[i] = j;
            } else {
                // 否则，将 j 对应的 next 值赋给当前字符的 next 值
                next[i] = next[j];
            }
        // 如果当前字符与 j 指向的字符不相同
        } else {
            // 将 j 回溯到其 next 值所指向的位置
            j = next[j];
        }
    }
}


/**
 * @brief 在字符串S中查找字符串T首次出现的位置（KMP算法）
 *
 * 使用KMP算法从字符串S的指定位置pos开始，查找字符串T首次出现的位置。
 *
 * @param S 主字符串
 * @param T 要查找的子字符串
 * @param pos 开始查找的位置（索引从1开始）
 * @param next 部分匹配表数组
 *
 * @return 如果找到，则返回子字符串T在主字符串S中首次出现的位置索引（从1开始）；
 *         如果未找到，则返回0。
 *
 * @note 如果pos小于1或大于T的长度，将返回0。
 * @note 如果传入的主字符串S、子字符串T或部分匹配表数组next为空指针，将返回0。
 */
int Index_KPM(String S, String T, int pos, const int *next) {
    // 检查主字符串S、子字符串T和部分匹配表数组next是否为空指针
    if (S.data == nullptr || T.data == nullptr || next == nullptr) {
        return false;
    }
    // 检查pos是否合法
    if (pos < 1 || pos > T.length) {
        return false;
    }
    int i = pos; // 从指定位置pos开始比较
    int j = 1; // j用于记录子字符串T的索引
    while (i <= S.length && j <= T.length) {
        // 如果j为0，表示新一轮的比较开始，或者当前字符匹配成功
        if (j == 0 || S.data[i] == T.data[j]) {
            i++; // 主字符串S的索引向后移动
            j++; // 子字符串T的索引向后移动
        } else {
            // 当前字符匹配失败，根据部分匹配表数组next进行回溯
            j = next[j];
        }
    }
    // 如果j大于T的长度，表示字符串T已经完整匹配完毕
    if (j > T.length) {
        return i - T.length; // 返回子字符串T在主字符串S中首次出现的位置索引（从1开始）
    } else {
        return 0; // 未找到子字符串T，返回0
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

    cout << S.data + 8 << endl;

    FreeString(&S);
    FreeString(&T);
    return 0;
}



