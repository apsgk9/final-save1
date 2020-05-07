/*
* Author: Marky Santos-Tankia
* File: jacobi.h Date: 5/10/20
* Class: CS 5201
* Instructor : Clayton Price
*
* MyVector file
*/

/*! \file
 *
 * A jacobi solver library.
 */
#include "solverInterface.h"


#ifndef JACOBI_H
#define JACOBI_H
class jacobi :  public virtual solverInterface<double>
{
private:
  double error_threshold;
public:

  /*!
  * @brief default
  * @pre input_threshold should be >0 but depends
  * @post creates a gaussseidel solver object
  * @throw invalid_argument if error is negative
  */
  jacobi(double input_threshold = 0.002);

  /*!
  * @brief Ax=b solver
  * @param[in] a square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves using the gaussseidel method
  * @post solves an Ax=b and returns a solution vector
  * @throw invalid_argument if matrix has non positive rows/cols
  * @throw invalid_argument a matrix coloumn is not equal b vector size
  */
  virtual vector<double> operator()(const matrix<double>& a, const vector<double>& b) const;

  /*!
  * @brief Ax=b solver
  * @param[in] a compactmatrix square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves using the gaussseidel method
  * @post uses a compactmatrix to solve faster
  * @post solves an Ax=b and returns a solution vector
  * @throw invalid_argument if matrix has non positive rows/cols
  * @throw invalid_argument a matrix coloumn is not equal b vector size
  */
  virtual vector<double> operator()(const compactmatrix<double>& a, const vector<double>& b) const;

};

#endif