/*
* Author: ALAIN MARKUS SANTOS-TANKIA
* File: global.h Date: 3/13/20
* Class: CS 5201
* Instructor : CLATON PRICE
*
* header file of global
*/

#ifndef GLOBAL_H
#define GLOBAL_H


/*!
* Global functions
*   These functions are not bounded inside any class
*   Used for general scenarios
*/
#include <functional>
/*!
* @brief pow function for ints
* @param[in] input_element value to pow
* @param[in] input_pow how much to exponentiate
* @pre input_pow>=0
* @post returns pow of input_element
* @throw invalid_argument input_pow<0
*/
double customPow(const double input_element, const int input_pow);

/*!
* @brief  calculates nth root
* @param[in] value to find the nth root
* @param[in] N the nth to calculate to
* @pre N < 0 
* @post returns double scalar of given arguements
* @throw invalid_argument N<0
*/

double nthRoot(double value, int N);



#endif