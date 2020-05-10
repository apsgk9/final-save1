/*
* Author: Marky Santos-Tankia
* File: Poisson.h Date: 5/10/20
* Class: CS 5201
* Instructor : Clayton Price
*
* Poisson file
*/

/*! \file
 *
 * A Poisson library.
 */

#ifndef Poisson_H
#define Poisson_H

#include "matrix.h"
#include <iostream>
#include <fstream>
#include "solverInterface.h"

using std::cout;
using std::cin;
using std::endl;

class Poisson
{
private:
  string file_input;
  string file_output;
  matrix<bool> image;
  matrix<double> A;
  compactmatrix<double> compact_A;
  vector<double> b;
  vector<double> answer;
public:

  /*!
  * @brief default constructor
  */
  Poisson() = default;

  /*!
  * @brief default copy constructor
  */
  Poisson(const Poisson& otherPoisson) = default;

  Poisson(const string input_file,const string output_file,double forcing_function);

  /*!
  * @brief creates a B vector based on the forcing function
  * @param[in] input_ff forcing function value
  * @pre T = T assingment operator must be defined
  * @post returns a b vector based on forcing function
  */
  static vector<double> createBvector(double input_ff,int size);

  /*!
  * @brief creates the A matrix based on image
  * @param[in] givenMatrix this must be black and white image in terms of B/W
  * @pre T = T assingment operator must be defined
  * @post returns the A matrix based on image givenMatrix
  */
  static matrix<double> createPoissonAMatrix(matrix<bool> givenMatrix);
  /*!
  * @brief solves Ax=b
  * @param[in] s solver to solve that outputs an answer from Ax=b
  * @pre s has to be compatible with A matrix and b vector 
  * @post returns the A matrix based on image givenMatrix
  * @post prints out the results to file_output
  */
  void solve(solverInterface<double>& s);

  /*!
  * @brief solves Ax=b with compact matrix
  * @param[in] s solver to solve that outputs an answer from Ax=b
  * @pre s has to be compatible with compact_A compact matrix and b vector
  * @post prints out the results to file_output
  */
  void fastsolve(solverInterface<double>& s);

  /*!
  * @brief prints to answer to file given
  * @param[in] file file for the answer to be printed out 
  * @pre answer must be solved first
  * @post prints out the results to file
  * @throw invalid_argument answer has not been found yet
  */
  void printtofile(string file);
  /*!
  * @brief creates b/w image from textfile
  * @param[in] file file for the answer to be printed out
  * @pre answer must be solved first
  * @pre text file must contain 'W' And 'B" 
  * @post creates matrix<bool> image from textfile
  */
  static matrix<bool> retrieve(string textfile);
};
//#include "Poisson.cpp"

#endif
