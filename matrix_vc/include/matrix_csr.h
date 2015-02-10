/*
 * matrix_csr.h
 *
 *  Created on: 2015. 1. 28.
 *      Author: asran
 */

#ifndef INCLUDE_MATRIX_CSR_H_
#define INCLUDE_MATRIX_CSR_H_

#include <stdio.h>
#include "matrix_typedef.h"

namespace	matrix
{

/**
 * ��� ��� ǥ�� Ŭ����
 */
class	MatrixCSR
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
		const MatrixCSR*	operandA;
		const MatrixCSR*	operandB;
		elem_t				elemOperandB;
		MatrixCSR*			result;
		void*				retVal;
	};
private:
	col_t				mCol;			///< �� ũ��
	row_t				mRow;			///< �� ũ��
	col_t*				mColStart;
	elem_vector_t		mData;

public:
				MatrixCSR		(	void	);
				MatrixCSR		(	size_t		col,
									size_t		row
								);
				MatrixCSR		(	const MatrixCSR&		matrix		);
	virtual	~MatrixCSR		(	void	);
public:
	elem_t		getElem		(	size_t				col,
									size_t				row
								) const;
	void		setElem		(	size_t				col,
									size_t				row,
									elem_t				elem
								);
	MatrixCSR	add			(	const MatrixCSR&	operand	) const;
	MatrixCSR	padd		(	const MatrixCSR&	operand	) const;
	MatrixCSR	sub			(	const MatrixCSR&	operand	) const;
	MatrixCSR	psub		(	const MatrixCSR&	operand	) const;
	MatrixCSR	multiply	(	const MatrixCSR&	operand	) const;
	MatrixCSR	pmultiply	(	const MatrixCSR&	operand	) const;
	MatrixCSR	multiply	(	elem_t		operand	) const;
	MatrixCSR	pmultiply	(	elem_t		operand	) const;
	MatrixCSR	tmultiply	(	const MatrixCSR&	operand	) const;
	MatrixCSR	ptmultiply	(	const MatrixCSR&	operand	) const;
	const MatrixCSR&		equal		(	const MatrixCSR&	operand	);
	const MatrixCSR&		pequal		(	const MatrixCSR&	operand	);
	bool			compare	(	const MatrixCSR&	operand	) const;
	bool			pcompare	(	const MatrixCSR&	operand	) const;
	MatrixCSR	solution	(	const MatrixCSR&	operand	);
public:
	inline MatrixCSR		operator+		(	const MatrixCSR&	operand	) const;
	inline MatrixCSR		operator-		(	const MatrixCSR&	operand	) const;
	inline MatrixCSR		operator*		(	const MatrixCSR&	operand	) const;
	inline MatrixCSR		operator*		(	elem_t		operand		) const;
	inline const MatrixCSR&		operator=		(	const MatrixCSR&	operand	);
	inline bool	operator==		(	const MatrixCSR&	operand	) const;
public:
	inline bool	isValid		(	void	);
	inline size_t	getCol			(	void	) const;
	inline size_t	getRow			(	void	) const;
	inline size_t	getSize		(	void	) const;
private:
	void		allocElems		(	size_t		col,
									size_t		row
								);
	void		freeElems		(	void	);
	void		copyElems		(	const MatrixCSR&		matrix		);
	void		pcopyElems		(	const MatrixCSR&		matrix		);
	void		chkSameSize	(	const MatrixCSR&		matrix		) const;
	void		chkBound		(	size_t		col,
									size_t		row
								) const;
	void		doThreadFunc	(	FuncKind		kind,
									OpInfo&		info
								) const;
	void		doThreadFunc	(	FuncKind		kind,
									OpInfo&		info
								);
private:
	static void*	threadFunc			(	void*	pData	);
	static void*	threadAdd			(	void*	pData	);
	static void*	threadSub			(	void*	pData	);
	static void*	threadMultiply	(	void*	pData	);
	static void*	threadElemMul		(	void*	pData	);
	static void*	threadTmultiply	(	void*	pData	);
	static void*	threadCopy			(	void*	pData	);
	static void*	threadCompare		(	void*	pData	);
private:
	static void		delElem_		(	vector_data_t*	data,
											size_t				col,
											size_t				row
										);
	static elem_t		getElem_		(	vector_data_t*	data,
											size_t				col,
											size_t				row
										);
	static void		setElem_		(	vector_data_t*	data,
											size_t				col,
											size_t				row,
											elem_t				elem
										);
};

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::operator+		(	const MatrixCSR&	operand	///< �ǿ�����
													) const
{
	return	add(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::operator-		(	const MatrixCSR&	operand	///< �ǿ�����
													) const
{
	return	sub(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::operator*		(	const MatrixCSR&	operand	///< �ǿ�����
													) const
{
	return	multiply(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
MatrixCSR		MatrixCSR::operator*		(	elem_t		operand	///< �ǿ�����
													) const
{
	return	multiply(operand);
}

/**
 * ��� ����
 * @return		���� �� ���
 */
const MatrixCSR&		MatrixCSR::operator=		(	const MatrixCSR&	operand	///< �ǿ�����
															)
{
	return	equal(operand);
}

/**
 * ��� ��
 * @return		�� ���
 */
bool	MatrixCSR::operator==	(	const MatrixCSR&	operand	///< �ǿ�����
										) const
{
	return	compare(operand);
}

/**
 * ��� ��ü�� ��ȿ���� �˻�
 * @return		��� ��ü�� ��ȿ�ϸ� true, ��ȿ���� ������ false
 */
bool	MatrixCSR::isValid		(	void	)
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
size_t	MatrixCSR::getCol		(	void	) const
{
	return	mCol;
}

/**
 * �� ũ�� ��������
 * @return		�� ũ��
 */
size_t	MatrixCSR::getRow		(	void	) const
{
	return	mRow;
}

/**
 * ��� ��� ������ �� ��������
 * @return		��� ������ ũ��
 */
size_t	MatrixCSR::getSize		(	void	) const
{
	return	mData.size();
}

}

#endif /* INCLUDE_MATRIX_CSR_H_ */
