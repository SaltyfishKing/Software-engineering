#include "generator.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

//isRowOrColLegal函数：判断当前填入数字是否满足行列要求
bool generator::isRowColLegal(int row, int col, int val) {
    //行判断
    for (int i = 0; i < col; i++) {
        if (sudoku[row][i] == val) {
            return false;
        }
    }

    //列判断
    for (int i = 0; i < row; i++) {
        if (sudoku[i][col] == val) {
            return false;
        }
    }
    return true;
}

//isBlockLegal函数：判断当前填入数字是否满足所在九宫格内要求
bool generator::isBlockLegal(int row, int col, int val) {

    //求出当前位置在九宫格内对应的行列号
    int s_row, s_col;
    s_row = row / 3 * 3;
    s_col = col / 3 * 3;

    //在九宫格内进行判断
    for (int i = s_row; i < s_row + 3; i++) {
        for (int j = s_col; j < s_col + 3; j++) {
            if (sudoku[i][j] == val && i != row && j != col) {
                return false;
            }
        }
    }
    return true;
}

//generate函数：将数独棋盘看作81个连续空格，用回溯法生成数独
bool generator::generate(int m) {

    //m为当前生成的空格标号（0-80）
    //m=81说明此时数独已经生成结束，结束生成
    if (m == 81) {
        return true;
    }

    //通过标号求得当前行列号
    int r, c;
    r = m / 9;
    c = m % 9;

    //如果当前位置已经填入数字则继续生成下一个位置
    if (sudoku[r][c] != 0) {
        if (generate(m + 1)) {
            return true;
        }
    }

    //一般空格生成过程
    else {
        //cnt用来计数确保生成1-9所有的随机数字
        int cnt = 0;
        int rd;
        //array数组用来标记1-9中已经生成的数字
        int array[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        while (cnt < 9) {
            //生成1-9随机数字直到array中没有该数字的生成记录
            while (1) {
                rd = rand() % 9 + 1;
                if (array[rd - 1] == 0) {
                    array[rd - 1] = 1;
                    cnt++;
                    break;
                }
            }
            //对当前位置赋值
            sudoku[r][c] = rd;
            //判断当前赋值是否合法
            //合法则继续生成下一位置
            if (isRowColLegal(r, c, rd) && isBlockLegal(r, c, rd)) {
                if (generate(m + 1)) {
                    return true;
                }
            }
        }
        //不合法则将当前位置赋值为0，回溯
        sudoku[r][c] = 0;
    }
    return false;
}

int** generator::returnMatrix() {
    int** p = new int*[9];
    for (int i = 0; i < 9; i++) {
        p[i] = new int[9];
        for (int j = 0; j < 9; j++) {
            p[i][j] = sudoku[i][j];
        }
    }
    return p;
}

//resetMatrix函数：将已生成的数独棋盘重置为初始状态
void generator::resetMatrix(int first) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }
    //按要求对左上角位置赋特定值
    sudoku[0][0] = first;
    return;
}

//clearFile函数：在每次写入目标文件之前先将原文件清空
void generator::clearFile() {
    ofstream outfile;
    outfile.open(".\\sudoku.txt");
    outfile.close();
    return;
}

//outputFile函数：将生成的数独棋盘输出到目标文件
void generator::outputFile() {
    ofstream outfile;
    //追加输出
    outfile.open(".\\sudoku.txt", ios::app);
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            outfile << sudoku[i][j] << ' ';
        }
        outfile << endl;
    }
    outfile << endl;
    outfile.close();
}