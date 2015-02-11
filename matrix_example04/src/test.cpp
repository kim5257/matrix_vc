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
 * ������
 */
Test::Test			(	void	)
{
	matrixA		=	matrix_t(COL_SIZE, ROW_SIZE);
	matrixB1	=	matrix_t(COL_SIZE, ROW_SIZE);;
	matrixB2	=	matrix_t(COL_SIZE, 1);;
}

/**
 * �Ҹ���
 */
Test::~Test		(	void	)
{

}

/**
 * ���� �ð� ����
 */
void	Test::startMeasure	(	void	)
{
	mStartTime	=	clock();
}

/**
 * ���� �ð� ����
 */
void	Test::endMeasure		(	void	)
{
	mEndTime	=	clock();
	mDiffTime	=	mEndTime - mStartTime;
}

/**
 * ���� �� ���ῡ �ɸ� �ð� ��� �� ���
 */
void	Test::ptrMeasure		(	void	)
{
	clock_t	sec		=	mDiffTime / CLOCKS_PER_SEC;
	clock_t	msec	=	mDiffTime - (sec * CLOCKS_PER_SEC);
	printf("�ɸ��ð� - %ld:%03ld\n\n", sec, msec);
}

/**
 * ���ǰ� �õ� �ʱ�ȭ
 */
void	Test::initRandomVal		(	void	)
{
	srand((unsigned int)time(NULL));
}

/**
 * ���� �� ����
 * @return	���� �� ���� ��
 */
matrix::elem_t
		Test::getRandomVal		(	size_t		start,	///< ���� �� ���� ����
									size_t		end		///< ���� �� ���� ��
								)
{
	matrix::elem_t	val		=	(matrix::elem_t)((rand() % (end - start + 1)) + start);

	return	val;
}

/**
 * ��� A, B1, B2�� ������ ������ �Է�
 */
void	Test::inpData			(	void	)
{
	printf("\n\n"
			"������ �Է�\n"
			"==========\n");

	printf("��� A1�� ������ �Է� ��...");
	fflush(stdout);

	initRandomVal();

	startMeasure();
	// ���� ������ A ��Ŀ� �� �ֱ�
	for(matrix::col_t cnt=0;cnt<matrixA.getCol();cnt++)
	{
		for(matrix::row_t cnt2=0;cnt2<VAL_PER_COL;cnt2++)
		{
			matrixA.setElem(cnt,(matrix::row_t)getRandomVal(0,matrixA.getRow()-1),getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}
	}
	endMeasure();
	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� B1�� ������ �Է� ��...");
	fflush(stdout);

	startMeasure();
	// ���� ������ B1 ��Ŀ� �� �ֱ�
	for(matrix::col_t cnt=0;cnt<matrixB1.getCol();cnt++)
	{
		for(matrix::row_t cnt2=0;cnt2<VAL_PER_COL;cnt2++)
		{
			matrixB1.setElem(cnt,(matrix::row_t)getRandomVal(0,matrixB1.getRow()-1),getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
		}
	}
	endMeasure();
	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� B2�� ������ �Է� ��...");
	fflush(stdout);

	startMeasure();
	// ���� ������ B2 ��Ŀ� �� �ֱ�
	for(matrix::col_t cnt=0;cnt<matrixB2.getCol();cnt++)
	{
		matrixB2.setElem(cnt,0,getRandomVal(VAL_RANGE_START, VAL_RANGE_END));
	}
	endMeasure();
	printf("�Ϸ�\n");
	ptrMeasure();
}

/**
 * ��� A, B1, B2�� ������ ũ�� ���
 */
void	Test::ptrDataSize		(	void	)
{
	printf("\n\n"
			"������ ũ��\n"
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
 * ���� ���� ����
 */
void	Test::testEqual		(	void	)
{
	bool	flag	=	false;

	printf("\n\n"
			"���� ����\n"
			"=========\n");

	printf("(1) ���� ������ ���� ����...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("���"):("���� ����"));

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("���"):("���� ����"));

	ptrMeasure();
#endif

}

/**
 * �� ���� ����
 */
void	Test::testCompare		(	void	)
{
	bool	flag	=	false;

	printf("\n\n"
			"�� ����\n"
			"=========\n");
	printf("���� �غ� ��...");
	fflush(stdout);

	// matrixResult�� matrixA ���� �ֱ�
	matrixResult1	=	matrixA;

	printf("�Ϸ�\n");

	printf("(1) ���� ������ ���� ����...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));

	ptrMeasure();
#endif

}

/**
 * ���� ���� ����
 */
void	Test::testAdd			(	void	)
{
	printf("\n\n"
			"���� ����\n"
			"=========\n");

	printf("(1) ���� ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.add(matrixB1);

	endMeasure();

	printf("�Ϸ�\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.padd(matrixB1);

	endMeasure();

	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� �� ��...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));
#endif
}

/**
 * ���� ���� ����
 */
void	Test::testSub			(	void	)
{
	printf("\n\n"
			"���� ����\n"
			"=========\n");

	printf("(1) ���� ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.sub(matrixB1);

	endMeasure();

	printf("�Ϸ�\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.psub(matrixB1);

	endMeasure();

	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� �� ��...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));

#endif

}

/**
 * ���� ���� ����
 */
void	Test::testMul			(	void	)
{
	printf("\n\n"
			"���� ����\n"
			"=========\n");

	printf("(1) ���� ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.multiply(matrixB2);

	endMeasure();

	printf("�Ϸ�\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.pmultiply(matrixB2);

	endMeasure();

	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� �� ��...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));
#endif

}

/**
 * ��� ���� ���� ����
 */
void	Test::testElmMul		(	void	)
{
	printf("\n\n"
			"��� * ��� ���� ����\n"
			"===================\n");

	printf("(1) ���� ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.multiply(2);

	endMeasure();

	printf("�Ϸ�\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.pmultiply(2);

	endMeasure();

	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� �� ��...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));
#endif

}

/**
 * ��ġ ��� ���� ���� ����
 */
void	Test::testTMul		(	void	)
{
	printf("\n\n"
			"��ġ ��� ���� ����\n"
			"==================\n");

	printf("(1) ���� ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult1		=	matrixA.tmultiply(matrixB2);

	endMeasure();

	printf("�Ϸ�\n");

	ptrMeasure();

#if( TEST_MULTI_THREAD != 0 )

	printf("(2) ��Ƽ ������ ���� ����...");
	fflush(stdout);

	startMeasure();

	matrixResult2		=	matrixA.ptmultiply(matrixB2);

	endMeasure();

	printf("�Ϸ�\n");
	ptrMeasure();

	printf("��� �� ��...");
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

	printf("�Ϸ�\n"
			"���: %s\n",
			(flag)?("��ġ��"):("�� ��ġ��"));
#endif
}

};
