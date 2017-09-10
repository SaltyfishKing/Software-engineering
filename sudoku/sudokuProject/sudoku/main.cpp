#include <iostream>
#include <string.h>
#include <time.h>
#include "generator.h"
using namespace std;

//check��������������������м��ͱ�����
bool check(int argc, char* argv[]) {
    //δ�����������
    if (argc == 1) {
        cout << "���������!" << endl;
        return false;
    }
    //����������
    else if (strcmp(argv[1], "-c")) {
        cout << "��������!" << endl;
        return false;
    }
    //����������
    else if (argc != 3 || atoi(argv[2]) == 0) {
        cout << "������һ��1~1000000֮�������!" << endl;
        return false;
    }
    return true;
}

//main����
int main(int argc, char* argv[]) {
    //�ȶ�������������д���
    while (!check(argc, argv)) {
        exit(0);
    }
    generator generator;
    const int first = ((4 + 3) % 9 + 1);
    int n;
    //�����������ת��Ϊint����
    n = atoi(argv[2]);
    srand((unsigned)time(NULL));
    //���Ŀ���ļ�
    generator.clearFile();
    //�����������̲����
    for (int i = 0; i < n; i++) {
        generator.resetMatrix(first);
        if (generator.generate(1)) {
            generator.outputFile();
        }
    }
    //��ʾ�����Ϣ
    cout << "�ɹ�����" << n << "����������!" << endl;
    return 0;
}
