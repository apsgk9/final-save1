/*
* Author: Marky Santos-Tankia
* File: vector.h Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* MyVector file
*/

/*! \file
 *
 * A Vector library.
 */

#ifndef VECTOR_H
#define VECTOR_H


#include <iostream>
#include <initializer_list>
#include <iterator>
#include <string>
#include <sstream> 
#include <functional>
#include "global.h"

using std::string;
using std::ostream;
using std::cout;
using std::istream;

/*
* Class: vector
*  Limited emulation of vector class for use of IG or any other.
*  Can use for range loops,resize (can cause garbage elements), etc.
*  @note Do not attempt to do operations on a empty vector. 
*  This can be made either through input_size=0 or
*  default constructor.
*  @note Resizing the array bigger than current_size can lead to empty
*  elements. Do not attempt to read these empty positions. only write.
*/
template<typename T>
class vector
{
private:
  T* arr; // pointer to the first element of the underlying array
  int current_size;       // size of this myvec

  /*!
  * @brief initializes array
  * @param[in]  input_size integer
  * @pre  input_size is non negative
  * @post creates new array specified by input_size
  * @throw invalid_argument if input_size is negative
  */

  void init(int input_size);


  /*!
  * @brief Does operations for two T types
  * @param[in] left T type
  * @param[in] right T type
  * @param[in] symbol char arithmetic sign
  * @pre T = T (assingment) must be defined.
  * @pre T + T (assingment) must be defined.
  * @pre T - T (assingment) must be defined.
  * @pre T * T (assingment) must be defined.
  * @post return result of type T of the left
  * @post and right arithmetic results
  * @throw invalid_argument if symbol not supported
  */

  static T handleMath(const char& symbol, const T& left, const T& right);

  /*!
  * @brief Creates a vector with two vector passed
  * @brief with specified operation
  * @param[in] lVec left vector
  * @param[in] rVec right vector
  * @param[in] symbol operation to use
  * @pre vector sizes are equal
  * @pre vector passed must have have no null elements
  * @pre T = T (assingment) must be defined.
  * @post returns new vector with combination of
  * @post two arrays with specified operation
  * @throw invalid_argument if vector sizes are unequal
  */

  static vector<T> operatorhandler(const vector<T>& lVec,
    const vector<T>& rVec, const char& symbol);





  //PUBLIC------------------------------
public:

  /*!
  * @brief Constructs vector of specificied size
  * @brief  defaults to 0 size if input not passed
  * @param[in] size of int
  * @pre size cannot be negative
  * @post creates vector of specified size
  */

  explicit vector(int size = 0);

  /*!
  * @brief  makes a new vector from given array
  * @param[in] input_array array to replace current arr
  * @param[in] input_size size of array
  * @pre  input_array is not empty
  * @pre  input_size is the same size as array
  * @post initiliaze new array, given input_array size
  * @post copy over input_array to initialized array
  * @note array size cannot be found, must be passed
  */

  vector(const T* input_array, const int input_size); // constructor

  /*!
  * @brief creates vector from initializer list
  * @param[in]  initializer_list<T>
  * @pre  T = T (assignment) must be defined
  * @post copies elements from init_list to arr in order
  */

  vector(std::initializer_list<T> l);

  /*!
  * @brief  copy constructor
  * @param[in]  otherVector
  * @pre  otherVector must have pass init() preconditions
  * @post copies contents of otherVector to *this vector
  */

  vector(const vector<T>& otherVector);

  /*!
  * @brief gives size of vector
  * @post returns integer current_size
  */

  int size() const;
  /*!
  * @brief  checks if empty
  * @post return bool of (current_size <= 0) ? true : false;
  */
  bool empty() const;

  /*!
  * @brief resizes vector
  * @param[in] new_size integer
  * @pre new_size non negative
  * @post creates new vector size given
  * @throw invalid_argument if negative new_size
  */

  void resize(const int new_size);


  /*!
  * @brief  add and store vector
  * @pre rhs must be same size as *this vector
  * @pre must pass operatorhandler() preconditions
  * @post adds and copies contents of otherVector to *this vector
  * @note almost same contents as operator+(vector lhs,vector rhs)
  */

  vector<T>& operator +=(const vector<T>& rhs);

  /*!
  * @brief  subtract and store vector
  * @pre rhs must be same size as *this vector
  * @pre must pass operatorhandler() preconditions
  * @post subtract and copies contents of otherVector to *this vector
  * @note almost same contents as operator-(vector lhs,vector rhs)
  */

  vector<T>& operator -=(const vector<T>& rhs);

  /*!
  * @brief adds two vectors
  * @param[in] lhs vector
  * @param[in] rhs vector
  * @pre must pass operatorhandler() preconditions
  * @post returns result of vector addition
  */

  template<typename U>
  friend vector<U> operator+(const vector<U>& lhs, const vector<U>& rhs);


  /*!
  * @brief
  * @param[in] lhs vector
  * @param[in] rhs vector
  * @pre must pass operatorhandler() preconditions
  * @post returns result of vector subtraction
  */

  template<typename U>
  friend vector<U> operator-(const vector<U>& lhs, const vector<U>& rhs);

  /*!
  * @brief  complements vector
  * @pre arr must have no garbage elements
  * @pre arr must have no null elements
  * @post modifies into a complemented vector
  */

  vector<T> operator-() const;

  /*!
  * @brief  calculate p-norm
  * @pre arr must have no garbage elements
  * @pre T += T (plus equals) must be defined
  * @pre satisfy customPow,nthRoot preconditions
  * @post returns a (double) scalar of p-norm calculated
  */

  double operator^(const int input_pow) const;

  /*!
  * @brief  replaces vector contents with input stream
  * @param[in]  finput  input stream
  * @param[in]  Obj  vector object being called
  * @pre  finput stream contents must be getline compatible
  * @pre  contents must be white space delimited, all in oneline
  * @post creates vector contents from input stream given
  * @post modifies Obj vector with finput contents
  * @post returns finput
  */

  template<typename U>
  friend istream& operator >> (istream& finput, vector<U>& Obj);

  /*!
  * @brief prints contents from Arr
  * @param[in] os ostream
  * @param[in] Obj Object called
  * @pre << T (insertion) defined
  * @post prints each element of arr
  * @post seperated by " "
  */

  template<typename U>
  friend ostream& operator << (ostream& os, const vector<U>& Obj);

  /*!
  * @brief
  * @param[in]
  * @pre f must be able to handle unassigned elements 
  * @pre "function f must have the signature T f(T) (for template type T)"
  * @post function calls each element and stores them into new vector
  * @post return new vector
  */
  template<typename U>
  vector<T> apply(const U& f);


  /*!
  * @brief  returns value of element at position
  * @param[in]  index_var index position to access
  * @pre index_var must be bounded,non negative
  * @pre resizing bigger can make empty elements giving garbage
  * @post returns value to element at given index_var
  * @throw range_error if out of bounds
  * @throw range_error vector is empty
  * @note empty elements can occur resulting in accessing garbage
  */

  const T  operator [] (const int index_var) const;

  /*!
  * @brief  returns reference of element at position
  * @param[in]  index_var index position to access
  * @pre index_var must be bounded,non negative
  * @pre resizing bigger can make empty elements giving garbage
  * @post returns reference to element at given index_var
  * @throw range_error if out of bounds
  * @throw range_error vector is empty
  * @note empty elements can occur resulting int accessing garbage
  */

  T& operator [] (const int index_var);


  /*!
  * @brief  Dot operator
  * @param[in] lhs left hand vector
  * @param[in] rhs right hand vector
  * @pre T must define = (assingment) operator
  * @pre T must define += (plus equals) operator
  * @pre must pass operator handler precondition (T * T defined in this case)
  * @post returns runs operatorhandlerfunction
  * @post returns sums up vector from said function
  * @post returns result of type T scalar dot operator
  */

  template<typename U>
  friend U operator*(const vector<U>& lhs, const vector<U>& rhs);


  /*!
  * @brief multiple vector by scalar multiple
  * @param[in] lhsScalar multiply by
  * @param[in] rhs vector to be multiplied
  * @pre rhs size > 0
  * @pre vector passed must have have no garbage elements
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies each element of vector by lhsScalar
  * @post returns resulting vector
  * @throw invalid_argument vector size < 0
  */

  template<typename U>
  friend vector<U> operator*(const U& lhsScalar, const vector<U>& rhs);

  /*!
  * @brief multiple vector by scalar multiple
  * @param[in] rhsScalar multiply by
  * @param[in] lhs vector to be multiplied
  * @pre rhs size > 0
  * @pre vector passed must have have no garbage elements
  * @pre T must define T * T (multiplication) operator
  * @pre T must define T = T (assignment) operator
  * @post mutiplies each element of vector by rhsScalar
  * @post returns resulting vector
  * @throw invalid_argument vector size < 0
  */

  template<typename U>
  friend vector<U> operator*(const vector<U>& lhs, const U& rhsScalar);

  /*!
  * @brief assigns source to this vector (by value)
  * @param[in] source vector<T>
  * @post copies contents from source to *this vector
  */

  vector<T>& operator = (const vector<T>& source);

  /*!
  * @brief cleans pointers
  * @post deletes [] arr if not nullptr
  */

  ~vector();

  /*!
  * @brief begin pointer
  * @post returns pointer to first element of arr
  * @post returns nullptr if size < 0
  */

  T* begin() const;
  /*!
  * @brief end pointer
  * @post returns pointer to one past last element of arr
  * @post returns nullptr if size < 0
  */
  T* end() const;

  /*!
  * @brief returns length of vector (norm 2)
  * @pre must pass ^operator preconditions
  * @post returns norm 2 of the vector
  */
  operator double() const;

  /*!
  * @brief do nothing, throw away for compiler warnings to be pleased
  * @post do nothing
  */
  void donothing() const
  {}
};


#include "global.h"
#include "vector.hpp"


#endif
