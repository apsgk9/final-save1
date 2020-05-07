/*
* Author: Marky Santos-Tankia
* File: cholesky.h Date: 5/10/20
* Class: CS 5201
* Instructor : Clayton Price
*
* MyVector file
*/

/*! \file
 *
 * A cholesky factorization solver library.
 */
#include "solverInterface.h"


#ifndef CHOLESKY_H
#define CHOLESKY_H
class cholesky : public virtual solverInterface<double>
{
public:
  /*!
  * @brief default
  * @post creates a cholesky solver object
  */
  cholesky() = default;

  /*!
  * @brief Ax=b solver
  * @param[in] a square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves using the cholesky method
  * @post solves an Ax=b and returns a solution vector
  * @throw invalid_argument if matrix has non positive rows/cols
  * @throw invalid_argument a matrix is not a square
  * @throw invalid_argument a matrix coloumn is not equal b vector size
  */

  virtual vector<double> operator()(const matrix<double>& a, const vector<double>& b) const;

  /*!
  * @brief Ax=b solver
  * @param[in] a compact square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves using the cholesky method
  * @post uses a compactmatrix to solve faster
  * @post solves an Ax=b and returns a solution vector
  * @throw invalid_argument if matrix has non positive rows/cols
  * @throw invalid_argument a matrix is not a square
  * @throw invalid_argument a matrix coloumn is not equal b vector size
  */

  virtual vector<double> operator()(const compactmatrix<double>& a, const vector<double>& b) const;

  /*!
  * @brief
  * @param[in] a square matrix
  * @param[in] lower matrix to be modified
  * @pre a must be symmetric
  * @post lower is modified to be the lower triangular matrix
  * @throw invalid_argument if a and lower do not have same dimesions
  */

  void Cholesky_Decomposition(const matrix<double>& a, matrix<double>& lower) const;
  /*!
  * @brief
  * @param[in] a square matrix
  * @param[in] lower matrix to be modified
  * @pre a must be symmetric
  * @post uses a compactmatrix to solve faster
  * @post lower is modified to be the lower triangular matrix
  * @throw invalid_argument if a and lower do not have same dimesions
  */
  void Cholesky_Decomposition(const compactmatrix<double>& a, matrix<double>& lower) const;

};

#endif