#include "generator.h"
#include <iostream>
#include <stdlib.h>
using namespace std;

//isRowOrColLegal�������жϵ�ǰ���������Ƿ���������Ҫ��
bool generator::isRowColLegal(int row, int col, int val) {
    //���ж�
    for (int i = 0; i < col; i++) {
        if (sudoku[row][i] == val) {
            return false;
        }
    }

    //���ж�
    for (int i = 0; i < row; i++) {
        if (sudoku[i][col] == val) {
            return false;
        }
    }
    return true;
}

//isBlockLegal�������жϵ�ǰ���������Ƿ��������ھŹ�����Ҫ��
bool generator::isBlockLegal(int row, int col, int val) {

    //�����ǰλ���ھŹ����ڶ�Ӧ�����к�
    int s_row, s_col;
    s_row = row / 3 * 3;
    s_col = col / 3 * 3;

    //�ھŹ����ڽ����ж�
    for (int i = s_row; i < s_row + 3; i++) {
        for (int j = s_col; j < s_col + 3; j++) {
            if (sudoku[i][j] == val && i != row && j != col) {
                return false;
            }
        }
    }
    return true;
}

//generate���������������̿���81�������ո��û��ݷ���������
bool generator::generate(int m) {

    //mΪ��ǰ���ɵĿո��ţ�0-80��
    //m=81˵����ʱ�����Ѿ����ɽ�������������
    if (m == 81) {
        return true;
    }

    //ͨ�������õ�ǰ���к�
    int r, c;
    r = m / 9;
    c = m % 9;

    //�����ǰλ���Ѿ��������������������һ��λ��
    if (sudoku[r][c] != 0) {
        if (generate(m + 1)) {
            return true;
        }
    }

    //һ��ո����ɹ���
    else {
        //cnt��������ȷ������1-9���е��������
        int cnt = 0;
        int rd;
        //array�����������1-9���Ѿ����ɵ�����
        int array[9] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };
        while (cnt < 9) {
            //����1-9�������ֱ��array��û�и����ֵ����ɼ�¼
            while (1) {
                rd = rand() % 9 + 1;
                if (array[rd - 1] == 0) {
                    array[rd - 1] = 1;
                    cnt++;
                    break;
                }
            }
            //�Ե�ǰλ�ø�ֵ
            sudoku[r][c] = rd;
            //�жϵ�ǰ��ֵ�Ƿ�Ϸ�
            //�Ϸ������������һλ��
            if (isRowColLegal(r, c, rd) && isBlockLegal(r, c, rd)) {
                if (generate(m + 1)) {
                    return true;
                }
            }
        }
        //���Ϸ��򽫵�ǰλ�ø�ֵΪ0������
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

//resetMatrix�������������ɵ�������������Ϊ��ʼ״̬
void generator::resetMatrix(int first) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            sudoku[i][j] = 0;
        }
    }
    //��Ҫ������Ͻ�λ�ø��ض�ֵ
    sudoku[0][0] = first;
    return;
}

//clearFile��������ÿ��д��Ŀ���ļ�֮ǰ�Ƚ�ԭ�ļ����
void generator::clearFile() {
    ofstream outfile;
    outfile.open(".\\sudoku.txt");
    outfile.close();
    return;
}

//outputFile�����������ɵ��������������Ŀ���ļ�
void generator::outputFile() {
    ofstream outfile;
    //׷�����
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