#include <iostream>
#include <string.h>
#include <time.h>
#include "generator.h"
using namespace std;

//check函数：对命令行输入进行检测和报错处理
bool check(int argc, char* argv[]) {
    //未输入参数处理
    if (argc == 1) {
        cout << "请输入参数!" << endl;
        return false;
    }
    //参数错误处理
    else if (strcmp(argv[1], "-c")) {
        cout << "参数错误!" << endl;
        return false;
    }
    //整数错误处理
    else if (argc != 3 || atoi(argv[2]) == 0) {
        cout << "请输入一个1~1000000之间的整数!" << endl;
        return false;
    }
    return true;
}

//main函数
int main(int argc, char* argv[]) {
    //先对命令行输入进行处理
    while (!check(argc, argv)) {
        exit(0);
    }
    generator generator;
    const int first = ((4 + 3) % 9 + 1);
    int n;
    //将输入的整数转化为int类型
    n = atoi(argv[2]);
    srand((unsigned)time(NULL));
    //清空目标文件
    generator.clearFile();
    //生成数独棋盘并输出
    for (int i = 0; i < n; i++) {
        generator.resetMatrix(first);
        if (generator.generate(1)) {
            generator.outputFile();
        }
    }
    //提示输出信息
    cout << "成功生成" << n << "个数独棋盘!" << endl;
    return 0;
}
