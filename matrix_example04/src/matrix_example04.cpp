// matrix_example04.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "test.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		test::Test		test;

		test.inpData();			// 행렬 데이터 입력
		test.ptrDataSize();		// 행렬 데이터 크기 출력
		test.testCompare();		// 비교 연산 시험
		test.testEqual();		// 대입 연산 시험
		test.testAdd();			// 덧셈 연산 시험
		test.testSub();			// 뺄셈 연산 시험
		test.testMul();			// 곱셈 연산 시험
		test.testElmMul();		// 상수 곱셈 연산 시험
		test.testTMul();		// 전치 행렬 곱셈 연산 시험
	}
	catch( matrix::ErrMsg*	exception	)
	{
		fprintf(stderr, "%s\n", exception->getErrString());
		matrix::ErrMsg::destroyErrMsg(exception);
	}

	return	0;
}

