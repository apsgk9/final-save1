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

#ifndef SOLVERINTERFACE_H
#define SOLVERINTERFACE_H

#include "matrix.h"
#include "compactmatrix.h"

template <typename T>
class solverInterface
{
public:
  /*!
  * @brief pure virtual function
  * @param[in] a square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves an Ax=b and returns a solution vector
  */

  virtual vector<T> operator()(const matrix<T>& a, const vector<T>& b) const = 0;

  /*!
  * @brief pure virtual function
  * @param[in] a compact square matrix(or any compatible matrix to the solver)
  * @param[in] b right hand side known variables
  * @pre both A and b need to be compatible
  * @post solves an Ax=b and returns a solution vector
  */
  virtual vector<T> operator()(const compactmatrix<T>& a, const vector<T>& b) const = 0;

};

#endif
