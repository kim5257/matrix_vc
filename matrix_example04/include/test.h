/*
 * test.h
 *
 *  Created on: 2015. 1. 14.
 *      Author: asran
 */

#ifndef TEST_H_
#define TEST_H_

#include <time.h>
#include "setting.h"

namespace	test
{

class	Test
{
private:
	clock_t		mStartTime;		///< 연산 시작 시간
	clock_t		mEndTime;		///< 연산 종료 시간
	clock_t		mDiffTime;		///< 시간 차
private:
	matrix_t	matrixA;		///< 행렬 A  ( N x N )
	matrix_t	matrixB1;		///< 행렬 B1 ( N x N )
	matrix_t	matrixB2;		///< 행렬 B2 ( N x 1 )
	matrix_t	matrixResult1;	///< 결과 행렬1
	matrix_t	matrixResult2;	///< 결과 행렬2
public:
				Test		(	void	);
	virtual		~Test		(	void	);
private:
	void	startMeasure	(	void	);
	void	endMeasure		(	void	);
	void	ptrMeasure		(	void	);
	void	initRandomVal	(	void	);
	matrix::elem_t
			getRandomVal	(	size_t		start,
								size_t		end
							);
public:
	void	inpData			(	void	);
	void	ptrDataSize		(	void	);
	void	testEqual		(	void	);
	void	testCompare		(	void	);
	void	testAdd			(	void	);
	void	testSub			(	void	);
	void	testMul			(	void	);
	void	testElmMul		(	void	);
	void	testTMul		(	void	);
};

};

#endif /* TEST_H_ */
