#include "stdafx.h"
#include "..\sudoku\generator.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace Microsoft::VisualStudio::TestTools::UnitTesting;

namespace sudokuTest
{
	[TestClass]
	public ref class UnitTest
	{
	private:
		TestContext^ testContextInstance;

	public: 
		property Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ TestContext
		{
			Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ get()
			{
				return testContextInstance;
			}
			System::Void set(Microsoft::VisualStudio::TestTools::UnitTesting::TestContext^ value)
			{
				testContextInstance = value;
			}
		};

		#pragma region Additional test attributes
		#pragma endregion 

        //测试isRowColLegal()函数
		[TestMethod]
		void isRowColLegal_Test()
		{
            generator gTest;
            //将矩阵左上角置为8，其余置为0
            gTest.resetMatrix(8);
            //测试在第一行，第六列填入8（结果应为false）
            bool test1 = gTest.isRowColLegal(0, 5, 8);
            //测试在第五行，第一列填入8（结果应为false）
            bool test2 = gTest.isRowColLegal(5, 0, 8);
            //测试在第一行，第二列插入1（结果应为true）
            bool test3 = gTest.isRowColLegal(0, 1, 1);
            Assert::AreEqual(test1, false);
            Assert::AreEqual(test2, false);
            Assert::AreEqual(test3, true);
		};

        //测试isBlockLegal()函数
        [TestMethod]
        void isBlockLegal_Test()
        {
            generator gTest;
            //将矩阵左上角置为8，其余置为0
            gTest.resetMatrix(8);
            //测试在第二行，第二列填入8（结果应为false）
            bool test1 = gTest.isBlockLegal(1, 1, 8);
            //测试在第二行，第二列填入1（结果应为true）
            bool test2 = gTest.isBlockLegal(1, 1, 1);
            Assert::AreEqual(test1, false);
            Assert::AreEqual(test2, true);
        };

        //测试resetMatrix()函数
        [TestMethod]
        void resetMatrix_Test()
        {
            generator gTest;
            //将矩阵左上角置为5，其余置为0
            gTest.resetMatrix(5);
            int** p = gTest.returnMatrix();
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (i == 0 && j == 0) {
                        //测试第一行，第一列是否为5
                        Assert::AreEqual(p[i][j], 5);
                    }
                    else {
                        //测试其余位置是否为0
                        Assert::AreEqual(p[i][j], 0);
                    }
                }
            }
        };
	};
}
