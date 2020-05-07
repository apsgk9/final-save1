/*
* Author: Marky Santos-Tankia
* File: main.cpp Date: 3/13/20
* Class: CS 5201
* Instructor : Clayton Price
*
* main file
*/
#include <iostream>
#include "matrix.h"
#include "global.h"
#include "vector.h"
#include "compactmatrix.h"
#include "Poisson.h"
#include "solverInterface.h"
#include "jacobi.h"
#include "cholesky.h"
#include "gaussseidel.h"

using std::cout;
using std::cin;
using std::endl;

void driver2();

int main()
{

  try
  {
    driver2();
  }
  catch (const std::out_of_range & oor) {
    std::cerr << "\nOut of Range error: " << oor.what() << '\n';
  }
  catch (const std::invalid_argument & ia) {
    std::cerr << "Invalid argument: " << ia.what() << '\n';
  }
  catch (const std::length_error & le) {
    std::cerr << "Length error: " << le.what() << '\n';
  }
  catch (const std::domain_error & de) {
    std::cerr << "Domain error: " << de.what() << '\n';
  }
  catch (const std::range_error & re) {
    std::cerr << "Range error: " << re.what() << '\n';
  }
  catch (...)
  {
    std::cerr << "An unknown error has occured." << '\n';
  }

  return 0;
}

void driver2()
{
  string fin= "output.txt";
  string fout= "heat.csv";
  string fout2 = "heat2.csv";
  Poisson P2D(fin,fout,0.01);
  Poisson P2D2(fin, fout2, 0.01);
  //Poisson<double> P2D;
  jacobi j(0.002);
  cholesky c;
  gaussseidel g(0.001);
  //cout << "gaussseidel\n";
  P2D.fastsolve(g);
  cout << "\njacobi\n";
  P2D2.fastsolve(j);
}


