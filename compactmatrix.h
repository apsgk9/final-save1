/*
* Author: Marky Santos-Tankia
* File: compactmatrix.h Date: 5/10/20
* Class: CS 5201
* Instructor : Clayton Price
*
* MyVector file
*/

/*! \file
 *
 * A compact matrix library.
 */

#ifndef COMPACTMATRIX_H
#define COMPACTMATRIX_H

#include "matrix.h"

template <typename T>
struct point
{
public:
  int x;
  int y;
  T value;
  point(const int i_x, const int i_y, const T& i_value)
  {
    x = i_x;
    y = i_y;
    value = i_value;
  }

};
template <typename T>
class compactmatrix 
{
private:
  matrix<T> data;
  vector<T> data_diag; 
  vector<int> rowstarts; //indicates where each row starts int he matrix of data
  int m_size;
  int rowsize;
  int colsize;
  
public:
  /*!
  * @brief default constructor
  */
  compactmatrix()= default;

  /*!
  * @brief constructor
  * @param[in] i_matrix matrix to be converted
  * @post creates a compacted matrix that removes 0s;
  */
  compactmatrix(const matrix<T>& i_matrix);
  /*!
  * @brief
  * @post outputs all matrix values with their associated row and coloumn
  */
  template<typename U>
  friend ostream& operator << (ostream& os, const compactmatrix<U>& Obj);

  /*!
  * @brief
  * @post returns size of the compact matrix
  */
  int size();
  /*!
  * @brief
  * @post returns size of the compact matrix
  */
  int size() const;

  /*!
  * @brief
  * @param[in] a index to be called on
  * @post returns value at the index specified
  */
  T value(int a);
  /*!
  * @brief
  * @param[in] a index to be called on
  * @post returns col value at the index specified
  */
  T col(int a);
  /*!
  * @brief
  * @param[in] a index to be called on
  * @post returns row value at the index specified
  */
  T row(int a);
  /*!
  * @brief const
  * @param[in] a index to be called on
  * @post returns value at the index specified
  */
  T value(int a)const;
  /*!
  * @brief const
  * @param[in] a index to be called on
  * @post returns col value at the index specified
  */
  T col(int a)const;
  /*!
  * @brief const
  * @param[in] a index to be called on
  * @post returns row value at the index specified
  */
  T row(int a) const;

  /*!
  * @brief
  * @post returns the original row value this matrix was made from
  */

  int size_row();
  /*!
  * @brief
  * @post returns the original col value this matrix was made from
  */
  int size_col();
  /*!
  * @brief const
  * @post returns the original row value this matrix was made from
  */
  int size_row() const;
  /*!
  * @brief const
  * @post returns the original row value this matrix was made from
  */
  int size_col() const;

  /*!
  * @brief const
  * @param[in] a row to be selected
  * @post returns the starting index that starts the row
  */
  int rowindex(int a) const;
  /*!
  * @brief 
  * @param[in] a row to be selected
  * @post returns the starting index that starts the row
  */
  int rowindex(int a);
  /*!
  * @brief 
  * @param[in] a index to be called on
  * @post returns value of the diagonal value at specified row (i,i)
  */
  T diag(int a);
  /*!
  * @brief const
  * @param[in] a index to be called on
  * @post returns value of the diagonal value at specified row (i,i)
  */
  T diag(int a) const;
};


#include "compactmatrix.hpp"

#endif
