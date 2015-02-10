// matrix_example03.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include "sparse_matrix.h"
#include "matrix_error.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define	COL_SIZE			(5000000)
#define	ROW_SIZE			(5000000)

#define	VAL_RANGE_START		(1)
#define	VAL_RANGE_END		(10)

#define	COL_PER_VAL			(1000000)

void	initRandomVal		(	void	)
{
	srand((unsigned int)time(NULL));
}

matrix::elem_t	getRandomVal		(	size_t		start,
											size_t		end
										)
{
	matrix::elem_t	val		=	(matrix::elem_t)((rand() % (end - start + 1)) + start);

	return	val;
}

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		matrix::SparseMatrix		matrixA	=	matrix::SparseMatrix(COL_SIZE,ROW_SIZE);
		matrix::SparseMatrix		matrixComp;
		matrix::SparseMatrix		matrixB	=	matrix::SparseMatrix(COL_SIZE,1);

		clock_t	startTime;
		clock_t	endTime;
		clock_t	diffTime;

		initRandomVal();

		printf("데이터 입력중...\n");

		startTime	=	clock();

		// 랜덤 값으로 대각선 열에 값 넣기
		for(matrix::col_t cnt=0;cnt<matrixA.getCol();cnt++)
		{
			matrixA.setElem(cnt,cnt,getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}

		// 랜덤 값으로 나머지 열에 값 넣기
		for(matrix::col_t cnt=0;cnt<matrixA.getCol();cnt++)
		{
			for(matrix::row_t cnt2=0;cnt2<COL_PER_VAL;cnt2++)
			{
				matrixA.setElem(cnt,(matrix::row_t)getRandomVal(0,matrixA.getRow()-1),getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
			}
		}

		// 랜덤 값으로 B 행렬에 값 넣기
		for(matrix::col_t cnt=0;cnt<matrixB.getCol();cnt++)
		{
			matrixB.setElem(cnt,0,getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));

		printf("대입 중...\n");

		startTime	=	clock();

		matrixComp		=	matrixA;

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));

		printf("비교 중...\n");

		startTime	=	clock();

		if( matrixComp == matrixA )
		{
			printf("비교 결과 일치\n");
		}
		else
		{
			printf("비교 결과 불일치\n");
		}

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));

		printf("matrixA 크기: %ld\n"
				"matrixB 크기: %ld\n",
				matrixA.getSize(),
				matrixB.getSize());

		printf("곱셈 중...\n");

		startTime	=	clock();

		matrix::SparseMatrix		matrixC1	=	matrixA.multiply(matrixB);

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));

		printf("쓰레드 곱셈 중...\n");

		startTime	=	clock();

		matrix::SparseMatrix		matrixC2	=	matrixA.pmultiply(matrixB);

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));

		printf("비교 중...\n");

		startTime	=	clock();

		if( matrixC1 == matrixC2 )
		{
			printf("비교 결과 일치\n");
		}
		else
		{
			printf("비교 결과 불일치\n");
		}

		endTime		=	clock();
		diffTime	=	endTime - startTime;

		printf("완료 - %ld:%06ld\n", (diffTime / CLOCKS_PER_SEC), diffTime - ((diffTime / CLOCKS_PER_SEC) * CLOCKS_PER_SEC));
	}
	catch( matrix::ErrMsg*	exception	)
	{
		fprintf(stderr, "%s\n", exception->getErrString());

		matrix::ErrMsg::destroyErrMsg(exception);
	}

	return	0;
}

