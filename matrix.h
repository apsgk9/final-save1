/*
* Author: Marky Santos-Tankia
* File: matrix.h Date: 
* Class: CS 5201
* Instructor : Clayton Price
*
* matrix file
*/

/*! \file
 *
 * A matrix library.
 */

#ifndef MATRIX_H
#define MATRIX_H


#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <sstream> 
#include <functional>
#include "vector.h"
#include <math.h>  

using std::string;
using std::ostream;
using std::cout;
using std::istream;

/*
* Class: 
*/
template<typename T>
class matrix
{
private:
  vector<T>* grid;
  int current_cols;
  int current_rows;

  /*!
  * @brief initializes matrix
  * @param[in]  input_size integer
  * @pre  input_rows is non negative
  * @pre  input_coloumns is non negative
  * @post creates new matrix specified by input_rows, input_coloumns
  * @throw invalid_argument if input_size is negative
  */

  void init(const int input_rows, const int input_coloumns);

  /*!
  * @brief Does operations for two T types
  * @param[in] left T type
  * @param[in] right T type
  * @param[in] symbol char arithmetic sign
  * @pre left and right matrix must be same dimensions
  * @pre T = T (assignment) must be defined.
  * @pre T + T (assignment) must be defined.
  * @pre T - T (assignment) must be defined.
  * @post return result of type T of the left
  * @post and right arithmetic results
  * @throw invalid_argument if symbol not supported
  */

  static matrix<T> plusminusHandler(const matrix<T>& lMat,
    const matrix<T>& rMat, const char& symbol);

  //PUBLIC------------------------------
public:

  /*!
  * @brief Constructs vector of specificied size
  * @brief  defaults to 0,0 size if input not passed
  * @param[in] row of int
  * @param[in] col of int
  * @pre size cannot be negative
  * @post creates vector of specified size
  */
  matrix(const int row=0, const int col=0);

  /*!
  * @brief creates matrix from 2d list
  * @param[in]  init_list 2D matrix
  * @pre  T = T (assignment) must be defined
  * @pre  initialization 2d array must have consistent coloumns
  * @post copies elements from init_list to arr in order
  * @throw invalid_argument initialization list has inconsistent coloumns
  */

  matrix(const std::initializer_list<std::initializer_list<T>> init_list);

  /*!
  * @brief  copy constructor
  * @param[in]  otherMatrix
  * @pre  otherVector must have pass init() preconditions
  * @pre  T = T (assignment) must be defined
  * @post copies contents of otherVector to *this vector
  */
    
  matrix(const matrix<T>& otherMatrix);

  /*!
  * @brief  copy constructor
  * @post returns current_cols
  */

  int cols() const;

  /*!
  * @brief  
  * @post returns current_rows
  */

  int rows() const;

  /*!
  * @brief prints contents from grid
  * @param[in] os ostream
  * @param[in] Obj Object called
  * @pre << T (insertion) defined
  * @post prints each element of arr
  * @post seperated by " " and '\n'
  * @post seperates the rows, last row no leading
  * @post '\n'
  */

  template<typename U>
  friend ostream& operator << (ostream& os, const matrix<U>& Obj);

  /*!
  * @brief  replaces vector contents with input stream
  * @param[in]  finput  input stream
  * @param[in]  Obj  matrix object being called
  * @pre  finput stream contents must be getline compatible
  * @pre  contents must be white space delimited, all in oneline
  * @pre  seperated by '\n'. Will continue until geltline string length is 0.
  * @post Creates matrix contents from input stream given
  * @post modifies Obj vector with finput contents
  * @post returns finput
  */

  template<typename U>
  friend istream& operator >> (istream& finput, matrix<T>& Obj);

  /*!
  * @brief assigns source to this matrix (by value)
  * @param[in] source matrix<T>
  * @post copies contents from source to *this vector
  */

  matrix<T>& operator = (const matrix<T>& source);

  /*!
  * @brief cleans pointers
  * @post deletes [] grid if not nullptr
  */

  ~matrix();


  //-------------------------ARITHMETIC-------------------------------------------

  /*!
  * @brief adds two matrices
  * @param[in] lhs vector
  * @param[in] rhs vector
  * @pre must pass plusminusHandler() preconditions
  * @post returns result of matrix addition
  */

  template<typename U>
  friend matrix<U> operator+(const matrix<U>& lhs, const matrix<U>& rhs);

  /*!
  * @brief subtracts two matrices
  * @param[in] lhs matrix
  * @param[in] rhs matrix
  * @pre must pass plusminusHandler() preconditions
  * @post returns result of matrix subtraction
  */

  template<typename U>
  friend matrix<U> operator-(const matrix<U>& lhs, const matrix<U>& rhs);

  /*!
  * @brief  add and store matrix
  * @pre rhs must be same size as *this matrix
  * @pre must pass plusminusHandler() preconditions
  * @post adds and copies contents of otherVector to *this vector
  * @note almost same contents as operator+(matrix lhs,matrix rhs)
  */

  matrix <T>& operator +=(const matrix<T>& rhs);

  /*!
  * @brief  subtract and store matrix
  * @pre rhs must be same size as *this matrix
  * @pre must pass plusminusHandler() preconditions
  * @post subtract and copies contents of otherVector to *this matrix
  * @note almost same contents as operator-(matrix lhs,matrix rhs)
  */

  matrix <T>& operator -=(const matrix<T>& rhs);

  /*!
  * @brief multiply matrix by scalar multiple
  * @param[in] rhsScalar multiply by
  * @param[in] lhs matrix to be multiplied
  * @pre rhs size > 0
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies each element of vector by rhsScalar
  * @post returns resulting matrix
  * @throw invalid_argument  matrix col or row < 0
  */
  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const U& rhsScalar);

  /*!
  * @brief multiply matrix by scalar multiple
  * @param[in] lhsScalar multiply by
  * @param[in] rhs matrix to be multiplied
  * @pre rhs size > 0
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies each element of vector by lhsScalar
  * @post returns resulting matrix
  * @throw invalid_argument matrix col or row < 0
  */

  template<typename U>
  friend matrix<U> operator*(const U& lhsScalar , const matrix<U>& rhs);

  /*! 
  * @brief accessoperator of matrix
  * @pre i and j cannot be out of bounds
  * @post returns reference to grid[i][j] (row,col)
  * @throw invalid_argument out of bounds.
  */

  T& operator()(const int i, const int j);

  /*! 
  * @brief accessoperator const version of matrix
  * @pre i and j cannot be out of bounds
  * @post returns reference to grid[i][j] (row,col)
  * @throw invalid_argument out of bounds.
  */

  T operator()(const int i, const int j) const;

  /*!
  * @brief multiple matrix by scalar multiple
  * @param[in] lhs matrix
  * @param[in] rhs matrix
  * @pre lhs.current_cols == rhs.current_rows
  * @pre T must define T + T (multiplication) operator
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies matrices and creates 
  * @post (rhs.current_cols,lhs.current_rows) matrix
  * @post returns resulting matrix 
  * @throw invalid_argument matrix col or row < 0
  */
  template<typename U>
  friend matrix<U> operator*(const matrix<U>& lhs, const matrix<U>& rhs);

  /*!
  * @brief multiple matrix by vector
  * @param[in] lhs matrix
  * @param[in] rhs vector
  * @pre lhs.current_cols == rhs.size()
  * @pre T must define T + T (multiplication) operator
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies matrices and creates 
  * @post coloumn vector /(lhs.current_rows,1 column) matrix
  * @post returns resulting vector 
  * @throw invalid_argument matrix col or row < 0
  */
  template<typename U>
  friend vector<U> operator*(const matrix<U>& lhs, const vector<U>& rhs);

  /*!
  * @brief multiple matrix by vector
  * @param[in] lhs vector
  * @param[in] rhs matrix
  * @pre lhs.size() == rhs.current_cols
  * @pre T must define T + T (multiplication) operator
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies matrices and creates 
  * @post (lhs.size() row,rhs.current_cols) matrix
  * @post returns resulting matrix 
  * @throw invalid_argument matrix col or row < 0
  */

  template<typename U>
  friend matrix<U> operator*(const vector<U>& lhs, const  matrix<U>& rhs);

  /*!
  * @brief returns frobenius 
  * @pre  matrix cannot be empty
  * @pre  -T (unary) must be defined
  * @post returns transposed matrix
  * @throw range_error matrix is empty
  */
  matrix<T> operator-() const;
  /*!
  * @brief outputs identity vector given size
  * @pre size>0
  * @post returns identity vector give size
  * @throw invalid_argument if size<=0
  */
  static matrix<T> identity(const int size);
  /*!
  * @brief returns frobenius norm
  * @pre  matrix cannot be empty
  * @post returns transposed matrix
  * @throw range_error matrix is empty
  */
  matrix<T> transpose() const;

  /*!
  * @brief newton's method invert
  * @pre matrix cannot be empty
  * @pre well conditioned matrix
  * @pre square matrix
  * @post return's inverted method
  * @post using newton-schulz method
  * @throw range_error matrix is empty
  * @throw range_error matrix must be square
  */
  matrix<T> invert() const;

  /*!
  * @brief returns frobenius norm
  * @pre  T+= T defined
  * @pre  T *T  defined
  * @post returns frobenius norm as double
  */
  explicit operator double() const;


  /*!
  * @brief  move constructor
  * @param[in]  otherMatrix
  * @pre  
  * @post 
  */

  matrix(matrix<T>&& otherMatrix);

};


#include "global.h"
#include "matrix.hpp"


#endif
