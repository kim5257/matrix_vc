/*
 * test.cpp
 *
 *  Created on: 2015. 1. 14.
 *      Author: asran
 */

#include "stdafx.h"
#include "test.h"
#include <stdio.h>
#include <stdlib.h>

namespace	test
{

/**
 * 생성자
 */
Test::Test			(	void	)
{
	matrixA		=	matrix_t(COL_SIZE, ROW_SIZE);
	matrixB1	=	matrix_t(COL_SIZE, ROW_SIZE);;
	matrixB2	=	matrix_t(COL_SIZE, 1);;
}

/**
 * 소멸자
 */
Test::~Test		(	void	)
{

}

/**
 * 시작 시간 측정
 */
void	Test::startMeasure	(	void	)
{
	mStartTime	=	clock();
}

/**
 * 종료 시간 측정
 */
void	Test::endMeasure		(	void	)
{
	mEndTime	=	clock();
	mDiffTime	=	mEndTime - mStartTime;
}

/**
 * 시작 및 종료에 걸린 시간 계산 및 출력
 */
void	Test::ptrMeasure		(	void	)
{
	clock_t	sec		=	mDiffTime / CLOCKS_PER_SEC;
	clock_t	msec	=	mDiffTime - (sec * CLOCKS_PER_SEC);
	printf("걸린시간 - %ld:%03ld\n\n", sec, msec);
}

/**
 * 임의값 시드 초기화
 */
void	Test::initRandomVal		(	void	)
{
	srand((unsigned int)time(NULL));
}

/**
 * 임의 값 추출
 * @return	추출 한 임의 값
 */
matrix::elem_t
		Test::getRandomVal		(	size_t		start,	///< 임의 값 범위 시작
									size_t		end		///< 임의 값 범위 끝
								)
{
	matrix::elem_t	val		=	(matrix::elem_t)((rand() % (end - start + 1)) + start);

	return	val;
}

/**
 * 행렬 A, B1, B2에 임의의 데이터 입력
 */
void	Test::inpData			(	void	)
{
	printf("\n\n"
			"데이터 입력\n"
			"==========\n");

	printf("행렬 A1에 데이터 입력 중...");
	fflush(stdout);

	initRandomVal();

	startMeasure();
	// 랜덤 값으로 A 행렬에 값 넣기
	for(matrix::col_t cnt=0;cnt<matrixA.getCol();cnt++)
	{
		for(matrix::row_t cnt2=0;cnt2<VAL_PER_COL;cnt2++)
		{
			matrixA.setElem(cnt,(matrix::row_t)getRandomVal(0,matrixA.getRow()-1),getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}
	}
	endMeasure();
	printf("완료\n");
	ptrMeasure();

	printf("행렬 B1에 데이터 입력 중...");
	fflush(stdout);

	startMeasure();
	// 랜덤 값으로 B1 행렬에 값 넣기
	for(matrix::col_t cnt=0;cnt<matrixB1.getCol();cnt++)
	{
		for(matrix::row_t cnt2=0;cnt2<VAL_PER_COL;cnt2++)
		{
			matrixB1.setElem(cnt,(matrix::row_t)getRandomVal(0,matrixB1.getRow()-1),getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}
	}
	endMeasure();
	printf("완료\n");
	ptrMeasure();

	printf("행렬 B2에 데이터 입력 중...");
	fflush(stdout);

	startMeasure();
	// 랜덤 값으로 B2 행렬에 값 넣기
	for(matrix::col_t cnt=0;cnt<matrixB2.getCol();cnt++)
	{
		matrixB2.setElem(cnt,0,getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
	}
	endMeasure();
	printf("완료\n");
	ptrMeasure();
}

/**
 * 행렬 A, B1, B2의 데이터 크기 출력
 */
void	Test::ptrDataSize		(	void	)
{
	printf("\n\n"
			"데이터 크기\n"
			"===========\n");

	printf("%-15s : %ld\n"
			"%-15s : %ld\n"
			"%-15s : %ld\n"
			"matrixA",
			matrixA.getSize(),
			"matrixB1",
			matrixB1.getSize(),
			"matrixB2",
			matrixB2.getSize());
}

/**
 * 대입 연산 시험
 */
void	Test::testEqual		(	void	)
{
	bool	flag	=	false;

	printf("\n\n"
			"대입 시험\n"
			"=========\n");

	printf("(1) 단일 쓰레드 대입 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1.equal(matrixA);

	endMeasure();

	if( matrixResult1 == matrixA )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("통과"):("문제 있음"));

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 대입 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1.pequal(matrixA);

	endMeasure();

	if( matrixResult1 == matrixA )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("통과"):("문제 있음"));

	ptrMeasure();
#endif

}

/**
 * 비교 연산 시험
 */
void	Test::testCompare		(	void	)
{
	bool	flag	=	false;

	printf("\n\n"
			"비교 시험\n"
			"=========\n");
	printf("시험 준비 중...");
	fflush(stdout);

	// matrixResult에 matrixA 내용 넣기
	matrixResult1	=	matrixA;

	printf("완료\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	if( matrixResult1.compare(matrixA) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	endMeasure();

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	if( matrixResult1.pcompare(matrixA) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	endMeasure();

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));

	ptrMeasure();
#endif

}

/**
 * 덧셈 연산 시험
 */
void	Test::testAdd			(	void	)
{
	printf("\n\n"
			"덧셈 시험\n"
			"=========\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.add(matrixB1);

	endMeasure();

	printf("완료\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.padd(matrixB1);

	endMeasure();

	printf("완료\n");
	ptrMeasure();

	printf("결과 비교 중...");
	fflush(stdout);

	bool	flag	=	false;

	if( matrixResult1.pcompare(matrixResult2) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));
#endif
}

/**
 * 뺄셈 연산 시험
 */
void	Test::testSub			(	void	)
{
	printf("\n\n"
			"뺄셈 시험\n"
			"=========\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.sub(matrixB1);

	endMeasure();

	printf("완료\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.psub(matrixB1);

	endMeasure();

	printf("완료\n");
	ptrMeasure();

	printf("결과 비교 중...");
	fflush(stdout);

	bool	flag	=	false;

	if( matrixResult1.pcompare(matrixResult2) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));

#endif

}

/**
 * 곱셈 연산 시험
 */
void	Test::testMul			(	void	)
{
	printf("\n\n"
			"곱셈 시험\n"
			"=========\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.multiply(matrixB2);

	endMeasure();

	printf("완료\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.pmultiply(matrixB2);

	endMeasure();

	printf("완료\n");
	ptrMeasure();

	printf("결과 비교 중...");
	fflush(stdout);

	bool	flag	=	false;

	if( matrixResult1.pcompare(matrixResult2) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));
#endif

}

/**
 * 상수 곱셈 연산 시험
 */
void	Test::testElmMul		(	void	)
{
	printf("\n\n"
			"행렬 * 상수 곱셈 시험\n"
			"===================\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.multiply(2);

	endMeasure();

	printf("완료\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.pmultiply(2);

	endMeasure();

	printf("완료\n");
	ptrMeasure();

	printf("결과 비교 중...");
	fflush(stdout);

	bool	flag	=	false;

	if( matrixResult1.pcompare(matrixResult2) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));
#endif

}

/**
 * 전치 행렬 곱셈 연산 시험
 */
void	Test::testTMul		(	void	)
{
	printf("\n\n"
			"전치 행렬 곱셈 시험\n"
			"==================\n");

	printf("(1) 단일 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.tmultiply(matrixB2);

	endMeasure();

	printf("완료\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) 멀티 쓰레드 동작 시험...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.ptmultiply(matrixB2);

	endMeasure();

	printf("완료\n");
	ptrMeasure();

	printf("결과 비교 중...");
	fflush(stdout);

	bool	flag	=	false;

	if( matrixResult1.pcompare(matrixResult2) )
	{
		flag	=	true;
	}
	else
	{
		flag	=	false;
	}

	printf("완료\n"
			"결과: %s\n",
			(flag)?("일치함"):("불 일치함"));
#endif
}

};
