// matrix_example04.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "test.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		test::Test		test;

		test.inpData();
		test.ptrDataSize();
		test.testCompare();
		test.testEqual();
		test.testAdd();
		test.testSub();
		test.testMul();
		test.testElmMul();
		test.testTMul();
		//test.ptrDataSize();
	}
	catch( matrix::ErrMsg*	exception	)
	{
		fprintf(stderr, "%s\n", exception->getErrString());
		matrix::ErrMsg::destroyErrMsg(exception);
	}

	return	0;
}

