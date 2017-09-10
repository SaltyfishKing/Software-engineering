#pragma once
#include <fstream>
using namespace std;

class generator
{
private:
    int sudoku[9][9];

public:
    bool isRowColLegal(int row, int col, int val);
    bool isBlockLegal(int row, int col, int val);
    bool generate(int m);
    int** returnMatrix();
    void resetMatrix(int first);
    void clearFile();
    void outputFile();
};