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


using std::cin;
using std::cout;
using std::endl;

void driver(string fin, string fout, double forcing_function, int method, int mode = 0);

int main(int argc, char **argv)
{
  string fin;
  string fout;
  int method;
  int mode;
  int num=argc;
  bool success = false;
  if(argc==3)
  {
    fin = argv[1];
    fout = argv[2];
    method = 0;
    mode = 0;
    success = true;
  }
  if (argc == 4)
  {
    fin = argv[1];
    fout = argv[2];
    method = atoi(argv[3]);
    mode=0;
    success = true;
  }
  else if (argc == 5)
  {
    fin = argv[1];
    fout = argv[2];
    method = atoi(argv[3]);
    mode = atoi(argv[4]);
    success=true;
  }
  cout << "ARGUEMENTS:" << num-2 << endl;
  cout << "---------------" << endl;
  for (int i = 2; i < num; i++)
  {
    cout << argv[i] << endl;
  }
  cout << "---------------" << endl;
  if (success)
  {
    try
    {
      driver(fin, fout,1.0,method,mode);
    }
    catch (const std::out_of_range &oor)
    {
      std::cerr << "\nOut of Range error: " << oor.what() << '\n';
    }
    catch (const std::invalid_argument &ia)
    {
      std::cerr << "Invalid argument: " << ia.what() << '\n';
    }
    catch (const std::length_error &le)
    {
      std::cerr << "Length error: " << le.what() << '\n';
    }
    catch (const std::domain_error &de)
    {
      std::cerr << "Domain error: " << de.what() << '\n';
    }
    catch (const std::range_error &re)
    {
      std::cerr << "Range error: " << re.what() << '\n';
    }
    catch (...)
    {
      std::cerr << "An unknown error has occured." << '\n';
    }
  }
  else
  {
    std::cerr << "Arguements are invalid.\nInput must be:\n[image input] [image output] "
    <<"[method 0,1,2] [mode 0:compact 1:noncompact] " << '\n';
    std::cerr << "Mode is optional and defaulted to 0\n";
  }
  

  return 0;
}

void driver(string fin, string fout, double forcing_function, int method, int mode)
{
  Poisson P2D(fin, fout, forcing_function);
  string ask = "Error convergence difference stop criteria: ";
  double error;
  if (mode == 0)
  {
    cout << "Using Compact Matrix" << endl;
    if (method == 0)
    {
      cout << "Method: Gauss-Seidel" << endl;
      cout << ask;
      cin >> error;
      gaussseidel g(error);
      P2D.fastsolve(g);
    }
    else if (method == 1)
    {
      cout << "Method: Jacobi" << endl;
      cout << ask;
      cin >> error;
      jacobi j(error);
      P2D.fastsolve(j);
    }
    else if (method == 2)
    {
      cout << "Method: Cholesky Factorization" << endl;
      cholesky c;
      P2D.fastsolve(c);
    }
    else
    {
      throw std::invalid_argument("cannot find method specified");
    }
  }
  else if (mode == 1)
  {
    cout << "Using Normal Matrix" << endl;
    if (method == 0)
    {
      cout << "Method: Gauss-Seidel" << endl;
      cout << ask;
      cin >> error;
      gaussseidel g(error);
      P2D.solve(g);
    }
    else if (method == 1)
    {
      cout << "Method: Jacobi" << endl;
      cout << ask;
      cin >> error;
      jacobi j(error);
      P2D.solve(j);
    }
    else if (method == 2)
    {
      cout << "Method: Cholesky Factorization" << endl;
      cholesky c;
      P2D.solve(c);
    }
    else
    {
      throw std::invalid_argument("cannot find method specified");
    }
  }
  else
  {
    throw std::invalid_argument("mode input is invalid ");
  }
}
