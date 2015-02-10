/*
 * sparse_matrix_csr.cpp
 *
 *  Created on: 2015. 1. 28.
 *      Author: asran
 */

#include "matrix_csr.h"
#include "matrix_error.h"
#include <math.h>

#define	THREAD_FUNC_THRESHOLD	(1)
#define	THREAD_NUM					(4)

namespace matrix
{

typedef	void*(*Operation)(void*);

struct		FuncInfo
{
	MatrixCSR::OpInfo		opInfo;
	Operation				func;
	size_t					startCol;
	size_t					endCol;
};

/**
 * ������
 */
MatrixCSR::MatrixCSR			(	void	)
:mCol(0),
mRow(0),
mColStart(NULL)
{
}

/**
 * ������
 */
MatrixCSR::MatrixCSR			(	size_t		col,	///< �� ũ��
									size_t		row		///< �� ũ��
								)
:mCol(0),
mRow(0),
mColStart(NULL)
{
	allocElems(col, row);
}

/**
 * ���� ������
 */
MatrixCSR::MatrixCSR			(	const MatrixCSR&		matrix		///< ���� �� ��ü
								)
:mCol(0),
mRow(0),
mColStart(NULL)
{
	allocElems(matrix.getCol(), matrix.getRow());
	copyElems(matrix);
}

/**
 * �Ҹ���
 */
MatrixCSR::~MatrixCSR		(	void	)
{
	freeElems();
}

/**
 * ��� ��� �� ����
 * @return		������ ��� ��� ��
 */
elem_t		MatrixCSR::getElem		(	size_t		col,	///< ���� �� �� ��ġ
											size_t		row		///< ���� �� �� ��ġ
										) const
{
	chkBound(col, row);

	elem_t	value	=	0;
	size_t	start	=	mColStart[col];
	size_t	end		=	mColStart[col+1];

	for(size_t cnt=start;cnt<end;cnt++)
	{
		if( mData[cnt].mRow == row )
		{
			value	=	mData[cnt].mData;
			break;
		}
	}

	return	value;
}

/**
 * ��� ��� �� ����
 */
void		MatrixCSR::setElem		(	size_t		col,	///< ���� �� �� ��ġ
											size_t		row,	///< ���� �� �� ��ġ
											elem_t		elem	///< ���� �� ��� ��
										)
{
	chkBound(col, row);

	bool	found	=	false;
	size_t	start	=	mColStart[col];
	size_t	end		=	mColStart[col+1];

	for(size_t cnt=start;cnt<end;cnt++)
	{
		if( mData[cnt].mRow == row )
		{
			mData[cnt].mData	=	elem;
			found	=	false;
		}
	}

	if( found == false )
	{
		elem_vector_itor	itor	=	mData.begin() + end;
		mData.insert(itor, node_t(row, elem));

		for(size_t cnt=col+1;cnt<mCol+1;cnt++)
		{
			mColStart[cnt]++;
		}
	}
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::add		(	const MatrixCSR&	operand	///< �ǿ�����
										) const
{
	chkSameSize(operand);

	MatrixCSR				result		=	MatrixCSR(getCol(), getRow());
	const elem_vector_t&	vec			=	operand.mData;

	result.mData.reserve(mData.size());

	for(size_t col=0;col<getCol();++col)
	{
		size_t		start	=	mColStart[col];
		size_t		end		=	mColStart[col+1];

		for(size_t cnt=start;cnt<end;++cnt)
		{
			result.setElem	(	col,
									mData[cnt].mRow,
									mData[cnt].mData
								);
		}

		start	=	operand.mColStart[col];
		end		=	operand.mColStart[col+1];

		for(size_t cnt=start;cnt<end;++cnt)
		{
			result.setElem	(	col,
									vec[cnt].mRow,
									result.getElem(col, vec[cnt].mRow) + vec[cnt].mData
								);
		}
	}

	return	result;
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::sub		(	const MatrixCSR&	operand	///< �ǿ�����
										) const
{
	chkSameSize(operand);

	MatrixCSR				result		=	MatrixCSR(getCol(), getRow());
	const elem_vector_t&	vec			=	operand.mData;

	result.mData.reserve(mData.size());

	for(size_t col=0;col<getCol();++col)
	{
		size_t		start	=	mColStart[col];
		size_t		end		=	mColStart[col+1];

		for(size_t cnt=start;cnt<end;++cnt)
		{
			result.setElem	(	col,
									mData[cnt].mRow,
									mData[cnt].mData
								);
		}

		start	=	operand.mColStart[col];
		end		=	operand.mColStart[col+1];

		for(size_t cnt=start;cnt<end;++cnt)
		{
			result.setElem	(	col,
									vec[cnt].mRow,
									result.getElem(col, vec[cnt].mRow) - vec[cnt].mData
								);
		}
	}

	return	result;
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::multiply	(	const MatrixCSR&	operand	///< �ǿ�����
										) const
{
	if( ( getCol() != operand.getRow() ) &&
		( getRow() != operand.getCol() ) )
	{
		throw	matrix::ErrMsg::createErrMsg("��� ũ�Ⱑ �ùٸ��� �ʽ��ϴ�.");
	}

	MatrixCSR				result		=	MatrixCSR(getCol(), operand.getRow());
	const elem_vector_t&	vec			=	operand.mData;

	for(size_t col=0;col<getCol();++col)
	{
		size_t		start	=	mColStart[col];
		size_t		end		=	mColStart[col+1];

		for(size_t cnt=start;cnt<end;++cnt)
		{
			size_t		start2	=	operand.mColStart[mData[cnt].mRow];
			size_t		end2	=	operand.mColStart[mData[cnt].mRow+1];

			for(size_t cnt2=start2;cnt2<end2;++cnt2)
			{
				result.setElem	(	col,
										vec[cnt2].mRow,
										result.getElem(col, vec[cnt2].mRow) + (mData[cnt].mData * vec[cnt2].mData)
									);
			}
		}
	}

	return	result;
}


/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::multiply	(	elem_t		operand	///< �ǿ�����
										) const
{
	MatrixCSR	result				=	MatrixCSR(getCol(), getRow());

	for(size_t col=0;col<getCol();++col)
	{
		size_t		start	=	mColStart[col];
		size_t		end		=	mColStart[col+1];

		for(size_t cnt=start;cnt!=end;++cnt)
		{
			result.setElem	(	col,
									mData[cnt].mRow,
									mData[cnt].mData * operand
								);
		}
	}

	return	result;
}

/**
 * ��ġ ��� ��ȯ �� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::tmultiply		(	const MatrixCSR&	operand	///< �ǿ�����
											) const
{
	if( ( getCol() != operand.getRow() ) &&
		( getRow() != operand.getCol() ) )
	{
		throw	matrix::ErrMsg::createErrMsg("��� ũ�Ⱑ �ùٸ��� �ʽ��ϴ�.");
	}

	MatrixCSR				result		=	MatrixCSR(getCol(), operand.getRow());
	const elem_vector_t&	vec			=	operand.mData;

	for(size_t col=0;col<getCol();++col)
	{
		size_t		start	=	mColStart[col];
		size_t		end		=	mColStart[col+1];

		for(size_t cnt=start;cnt!=end;++cnt)
		{
			size_t		start2	=	operand.mColStart[col];
			size_t		end2	=	operand.mColStart[col+1];

			for(size_t cnt2=start2;cnt2!=end2;++cnt2)
			{
				result.setElem	(	mData[cnt].mRow,
										vec[cnt2].mRow,
										result.getElem(mData[cnt].mRow, vec[cnt2].mRow) + (mData[cnt].mData * vec[cnt2].mData)
									);
			}
		}
	}

	return	result;
}

/**
 * ��� ����
 * @return		���� �� ���
 */
const MatrixCSR&		MatrixCSR::equal		(	const MatrixCSR&	operand	///< �ǿ�����
												)
{
	try
	{
		chkSameSize(operand);
		copyElems(operand);
	}
	catch( ErrMsg*	exception	)
	{
		freeElems();
		allocElems(operand.getCol(), operand.getRow());
		copyElems(operand);
	}

	return	*this;
}

/**
 * ��� �� ����
 * @return		�� ����� ��ġ�ϸ� true, �� ��ġ�ϸ� false
 */
bool			MatrixCSR::compare			(	const MatrixCSR&	operand
												) const
{
	bool	ret		=	true;

	if( getSize() == operand.getSize() )
	{
		for(size_t col=0;col<getCol();++col)
		{
			size_t	start	=	mColStart[col];
			size_t	end		=	mColStart[col+1];

			for(size_t cnt=start;cnt<end;++cnt)
			{
				elem_t	val		=	operand.getElem(col, mData[cnt].mRow);
				if( mData[cnt].mData != val )
				{
					ret		=	false;
					break;
				}
			}

			if( ret == false )
			{
				break;
			}
		}
	}
	else
	{
		ret		=	false;
	}

	return	ret;
}

/**
 * ��� ������ ���� �Ҵ�
 * @exception		�޸� �Ҵ� ���� �� ���� �߻�
 */
void		MatrixCSR::allocElems		(	size_t		col,	///< �� ũ��
												size_t		row		///< �� ũ��
											)
{
	try
	{
		mCol	=	col;
		mRow	=	row;

		mColStart	=	new col_t[col+1];
		memset(mColStart, 0, sizeof(col_t) * (col+1));
	}
	catch (	std::bad_alloc&	exception		)
	{
		throw matrix::ErrMsg::createErrMsg(exception.what());
	}
}

/**
 * ��� ������ ���� �Ҵ� ����
 */
void		MatrixCSR::freeElems		(	void	)
{
	delete[]	mColStart;
	mCol	=	0;
	mRow	=	0;
}

/**
 * ��� ������ ����
 */
void		MatrixCSR::copyElems		(	const MatrixCSR&		matrix		///< ���� �� ���
										)
{
	memcpy(mColStart, matrix.mColStart, sizeof(col_t) * (mCol + 1));
	mData	=	matrix.mData;
}


/**
 * ���� ũ���� ������� �˻�
 * @exception		����� ���� ũ�Ⱑ �ƴ� ��� ���� �߻�
 */
void		MatrixCSR::chkSameSize	(	const MatrixCSR&		matrix		///< �� �� ���
										) const
{
	if( ( getCol() != matrix.getCol() ) ||
		( getRow() != matrix.getRow() ) )
	{
		throw matrix::ErrMsg::createErrMsg("��� ũ�Ⱑ �ùٸ��� �ʽ��ϴ�.");
	}
}

/**
 * ��� ��� ���� ���� �˻�
 * @exception		���� ���� ���� ��� ���� �߻�
 */
void		MatrixCSR::chkBound		(	size_t		col,	///< ���� �� �� ��ġ
											size_t		row		///< ���� �� �� ��ġ
										) const
{
	if( ( col >= mCol ) ||
		( row >= mRow ) )
	{
		throw	matrix::ErrMsg::createErrMsg("������ �Ѿ�� �����Դϴ�.");
	}
}

}
