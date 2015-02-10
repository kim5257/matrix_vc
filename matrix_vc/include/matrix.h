/*
 * matrix.h
 *
 *  Created on: 2014. 12. 26.
 *      Author: asran
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <stdio.h>
#include "matrix_typedef.h"

namespace matrix
{

/**
 * ��� ǥ�� Ŭ����
 */
class	Matrix
{
private:
	size_t		mCol;		///< �� ũ��
	size_t		mRow;		///< �� ũ��
	elem_t*		mData;		///< ��� ������
public:
				Matrix			(	void	);
				Matrix			(	size_t		col,
									size_t		row
								);
				Matrix			(	const Matrix&		matrix		);
	virtual	~Matrix		(	void	);
public:
	elem_t		getElem		(	size_t		col,
									size_t		row
								) const;
	void		setElem		(	size_t		col,
									size_t		row,
									elem_t		elem
								);
	Matrix		add				(	const Matrix&	operand	) const;
	Matrix		sub				(	const Matrix&	operand	) const;
	Matrix		multiply		(	const Matrix&	operand	) const;
	Matrix		multiply		(	elem_t		operand	) const;
	Matrix		transpose		(	void	) const;
	const Matrix&		equal			(	const Matrix&	operand	);
	Matrix		solution		(	const Matrix&	operand	);
public:
	inline Matrix		operator+		(	const Matrix&	operand	) const;
	inline Matrix		operator-		(	const Matrix&	operand	) const;
	inline Matrix		operator*		(	const Matrix&	operand	) const;
	inline Matrix		operator*		(	elem_t		operand		) const;
	inline const Matrix&		operator=		(	const Matrix&	operand	);
public:
	inline bool	isValid		(	void	);
	inline size_t	getCol			(	void	) const;
	inline size_t	getRow			(	void	) const;
private:
	void		allocElems		(	size_t		col,
									size_t		row
								);
	void		freeElems		(	void	);
	void		copyElems		(	const Matrix&		matrix		);
	void		chkSameSize	(	const Matrix&		matrix		) const;
	void		chkBound		(	size_t		col,
									size_t		row
								) const;
};

/**
 * ��� ����
 * @return		��� ���� ���
 */
Matrix		Matrix::operator+		(	const Matrix&	operand	) const
{
	return	add(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
Matrix		Matrix::operator-		(	const Matrix&	operand	) const
{
	return	sub(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
Matrix		Matrix::operator*		(	const Matrix&	operand	) const
{
	return	multiply(operand);
}

/**
 * ��� ����
 * @return		��� ���� ���
 */
Matrix		Matrix::operator*		(	elem_t		operand		) const
{
	return	multiply(operand);
}

/**
 * ��� ����
 * @return		���� �� ���
 */
const Matrix&		Matrix::operator=		(	const Matrix&	operand	)
{
	return	equal(operand);
}

/**
 * ��� ��ü�� ��ȿ���� �˻�
 * @return		��� ��ü�� ��ȿ�ϸ� true, ��ȿ���� ������ false
 */
bool	Matrix::isValid		(	void	)
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
size_t	Matrix::getCol			(	void	) const
{
	return	mCol;
}

/**
 * �� ũ�� ��������
 * @return		�� ũ��
 */
size_t	Matrix::getRow			(	void	) const
{
	return	mRow;
}

};

#endif /* MATRIX_H_ */
