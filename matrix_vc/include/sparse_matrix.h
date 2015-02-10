/*
 * sparse_matrix.h
 *
 *  Created on: 2015. 1. 12.
 *      Author: asran
 */

#ifndef SPARSE_MATRIX2_H_
#define SPARSE_MATRIX2_H_

#include <stdio.h>
#include "matrix_typedef.h"

namespace	matrix
{

/**
 * ��� ��� ǥ�� Ŭ����
 */
class	SparseMatrix
{
public:
	enum	FuncKind
	{
		FUNC_ADD,			///< ����
		FUNC_SUB,			///< ����
		FUNC_MULTIPLY,		///< ����
		FUNC_ELEM_MUL,		///< ��� x ���� ��
		FUNC_PMULTIPLY,		///< ��ġ ��� ����
		FUNC_COPY,			///< ��� ����
		FUNC_COMPARE,		///< ��� ��
	};
	struct		OpInfo
	{
		const SparseMatrix*		operandA;
		const SparseMatrix*		operandB;
		elem_t					elemOperandB;
		SparseMatrix*			result;
		THREAD_RETURN_TYPE		retVal;
	};
private:
	col_t			mCol;		///< �� ũ��
	row_t			mRow;		///< �� ũ��
	vector_data_t*	mData;		///< ��� ������
public:
				SparseMatrix		(	void	);
				SparseMatrix		(	col_t		col,
										row_t		row
									);
				SparseMatrix		(	const SparseMatrix&		matrix		);
	virtual		~SparseMatrix		(	void	);
public:
	elem_t		getElem		(	col_t				col,
								row_t				row
							) const;
	void		setElem		(	col_t				col,
								row_t				row,
								elem_t				elem
							);
	SparseMatrix	add			(	const SparseMatrix&	operand	) const;
	SparseMatrix	padd		(	const SparseMatrix&	operand	) const;
	SparseMatrix	sub			(	const SparseMatrix&	operand	) const;
	SparseMatrix	psub		(	const SparseMatrix&	operand	) const;
	SparseMatrix	multiply	(	const SparseMatrix&	operand	) const;
	SparseMatrix	pmultiply	(	const SparseMatrix&	operand	) const;
	SparseMatrix	multiply	(	elem_t		operand	) const;
	SparseMatrix	pmultiply	(	elem_t		operand	) const;
	SparseMatrix	tmultiply	(	const SparseMatrix&	operand	) const;
	SparseMatrix	ptmultiply	(	const SparseMatrix&	operand	) const;
	const SparseMatrix&		equal		(	const SparseMatrix&	operand	);
	const SparseMatrix&		pequal		(	const SparseMatrix&	operand	);
	bool			compare	(	const SparseMatrix&	operand	) const;
	bool			pcompare	(	const SparseMatrix&	operand	) const;
	SparseMatrix	solution	(	const SparseMatrix&	operand	);
public:
	inline SparseMatrix		operator+		(	const SparseMatrix&	operand	) const;
	inline SparseMatrix		operator-		(	const SparseMatrix&	operand	) const;
	inline SparseMatrix		operator*		(	const SparseMatrix&	operand	) const;
	inline SparseMatrix		operator*		(	elem_t		operand		) const;
	inline const SparseMatrix&		operator=		(	const SparseMatrix&	operand	);
	inline bool	operator==		(	const SparseMatrix&	operand	) const;
public:
	inline bool	isValid		(	void	);
	inline col_t	getCol			(	void	) const;
	inline row_t	getRow			(	void	) const;
	inline size_t	getSize		(	void	) const;
private:
	void		allocElems		(	col_t		col,
									row_t		row
								);
	void		freeElems		(	void	);
	void		copyElems		(	const SparseMatrix&		matrix		);
	void		pcopyElems		(	const SparseMatrix&		matrix		);
	void		chkSameSize	(	const SparseMatrix&		matrix		) const;
	void		chkBound		(	col_t		col,
									row_t		row
								) const;
	void		doThreadFunc	(	FuncKind		kind,
									OpInfo&		info
								) const;
	void		doThreadFunc	(	FuncKind		kind,
									OpInfo&		info
								);
private:
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadFunc			(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadAdd			(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadSub			(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadMultiply		(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadElemMul		(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadTmultiply		(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadCopy			(	void*	pData	);
	static THREAD_RETURN_TYPE THREAD_FUNC_TYPE	threadCompare		(	void*	pData	);
private:
	static void		delElem_		(	vector_data_t*	data,
										col_t			col,
										row_t			row
									);
	static elem_t	getElem_		(	vector_data_t*	data,
										col_t			col,
										row_t			row
									);
	static void		setElem_		(	vector_data_t*	data,
										col_t			col,
										row_t			row,
										elem_t			elem
									);
};

/**
 * ��� ����
 * @return		��� ���� ���
 */
SparseMatrix		SparseMatrix::operator+		(	const SparseMatrix&	operand	///< �ǿ�����
													) const
{
	return	padd(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
SparseMatrix		SparseMatrix::operator-		(	const SparseMatrix&	operand	///< �ǿ�����
													) const
{
	return	psub(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
SparseMatrix		SparseMatrix::operator*		(	const SparseMatrix&	operand	///< �ǿ�����
													) const
{
	return	pmultiply(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
SparseMatrix		SparseMatrix::operator*		(	elem_t		operand	///< �ǿ�����
													) const
{
	return	pmultiply(operand);
}

/**
 * ��� ����
 * @return		���� �� ���
 */
const SparseMatrix&		SparseMatrix::operator=		(	const SparseMatrix&	operand	///< �ǿ�����
															)
{
	return	pequal(operand);
}

/**
 * ��� ��
 * @return		�� ���
 */
bool	SparseMatrix::operator==	(	const SparseMatrix&	operand	///< �ǿ�����
										) const
{
	return	pcompare(operand);
}

/**
 * ��� ��ü�� ��ȿ���� �˻�
 * @return		��� ��ü�� ��ȿ�ϸ� true, ��ȿ���� ������ false
 */
bool	SparseMatrix::isValid		(	void	)
{
	bool	ret		=	false;

	if( (mCol != 0) &&
		(mRow != 0) )
	{
		ret		=	true;
	}

	return	ret;
}

/**
 * �� ũ�� ��������
 * @return		�� ũ��
 */
col_t	SparseMatrix::getCol		(	void	) const
{
	return	mCol;
}

/**
 * �� ũ�� ��������
 * @return		�� ũ��
 */
row_t	SparseMatrix::getRow		(	void	) const
{
	return	mRow;
}

/**
 * ��� ��� ������ �� ��������
 * @return		��� ������ ũ��
 */
size_t	SparseMatrix::getSize		(	void	) const
{
	size_t		sum		=	0;

	for(size_t cnt=0;cnt<getCol();cnt++)
	{
		sum		+=	mData[cnt].mVector.size();
	}

	return	sum;
}

}



#endif /* SPARSE_MATRIX2_H_ */
