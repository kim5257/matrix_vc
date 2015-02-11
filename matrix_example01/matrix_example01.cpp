// matrix_example01.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "matrix.h"
#include "matrix_error.h"

int _tmain(int argc, _TCHAR* argv[])
{
	try
	{
		matrix::Matrix	matrixA	=	matrix::Matrix(4,4);		// 4x4 A��� ����
		matrix::Matrix	matrixB	=	matrix::Matrix(4,4);		// 4x4 B��� ����
		matrix::Matrix	matrixC;

		// A ��� ������ �ֱ�
		matrixA.setElem(0,0,1);
		matrixA.setElem(0,1,2);
		matrixA.setElem(0,2,3);
		matrixA.setElem(0,3,4);
		matrixA.setElem(1,0,5);
		matrixA.setElem(1,1,6);
		matrixA.setElem(1,2,7);
		matrixA.setElem(1,3,8);
		matrixA.setElem(2,0,9);
		matrixA.setElem(2,1,10);
		matrixA.setElem(2,2,11);
		matrixA.setElem(2,3,12);
		matrixA.setElem(3,0,13);
		matrixA.setElem(3,1,14);
		matrixA.setElem(3,2,15);
		matrixA.setElem(3,3,16);

		// B ��� ������ �ֱ�
		matrixB.setElem(0,0,16);
		matrixB.setElem(0,1,15);
		matrixB.setElem(0,2,14);
		matrixB.setElem(0,3,13);
		matrixB.setElem(1,0,12);
		matrixB.setElem(1,1,11);
		matrixB.setElem(1,2,10);
		matrixB.setElem(1,3,9);
		matrixB.setElem(2,0,8);
		matrixB.setElem(2,1,7);
		matrixB.setElem(2,2,6);
		matrixB.setElem(2,3,5);
		matrixB.setElem(3,0,4);
		matrixB.setElem(3,1,3);
		matrixB.setElem(3,2,2);
		matrixB.setElem(3,3,1);

		// A��� ���
		printf("A = \n");
		for(matrix::col_t col=0;col<matrixA.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixA.getRow();row++)
			{
				printf("%6.2f ", matrixA.getElem(col, row));
			}
			printf("\n");
		}

		// B��� ���
		printf("B = \n");
		for(matrix::col_t col=0;col<matrixB.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixB.getRow();row++)
			{
				printf("%6.2f ", matrixB.getElem(col, row));
			}
			printf("\n");
		}

		// C = A + B
		matrixC	=	matrixA + matrixB;

		// C ��� ���
		printf("C = A + B\n");
		for(matrix::col_t col=0;col<matrixC.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixC.getRow();row++)
			{
				printf("%6.2f ", matrixC.getElem(col, row));
			}
			printf("\n");
		}

		// C = A - B
		matrixC	=	matrixA - matrixB;

		// C ��� ���
		printf("C = A - B\n");
		for(matrix::col_t col=0;col<matrixC.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixC.getRow();row++)
			{
				printf("%6.2f ", matrixC.getElem(col, row));
			}
			printf("\n");
		}

		// C = A * B
		matrixC	=	matrixA.multiply(matrixB);

		// C ��� ���
		printf("C = A * B\n");
		for(matrix::col_t col=0;col<matrixC.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixC.getRow();row++)
			{
				printf("%6.2f ", matrixC.getElem(col, row));
			}
			printf("\n");
		}

		// C = A * 2
		matrixC	=	matrixA.multiply(2);

		// C ��� ���
		printf("C = A * 2\n");
		for(matrix::col_t col=0;col<matrixC.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixC.getRow();row++)
			{
				printf("%6.2f ", matrixC.getElem(col, row));
			}
			printf("\n");
		}

		// C = (A ��ġ���) * 2
		matrixC	=	matrixA.transpose() * matrixB;

		// C ��� ���
		printf("C = A.transpose() * B\n");
		for(matrix::col_t col=0;col<matrixC.getCol();col++)
		{
			for(matrix::row_t row=0;row<matrixC.getRow();row++)
			{
				printf("%6.2f ", matrixC.getElem(col, row));
			}
			printf("\n");
		}
	}
	catch( matrix::ErrMsg*	exception	)
	{
		printf("Exception: %s\n", exception->getErrString());

		matrix::ErrMsg::destroyErrMsg(exception);
	}


	return	0;
}
