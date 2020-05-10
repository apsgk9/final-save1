#include "jacobi.h"

jacobi::jacobi(double input_threshold):
  error_threshold(input_threshold) 
{
  if (error_threshold < 0)
  {
    throw std::invalid_argument("error must be positive");
  }
}

vector<double> jacobi::operator()(const matrix<double>& a, const vector<double>& b) const
{
  if (a.rows() <= 0 || a.cols() <= 0)
  {
    throw std::invalid_argument("a matrix cannot have non positive rows/cols");
  }
  if (a.rows() != a.cols())
  {
    throw std::invalid_argument("a matrix must be a square");
  }
  if (a.cols() != b.size())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }

  int i, j, nValue;
  vector<double> x(b.size()), c(b.size());
  vector<double> x_previous(b.size());
  nValue = b.size(); 

  for (int i = 0; i < b.size(); i++)
  {
    c[i] = 0;
    x[i] = 0;
    x_previous[i] = 0;
  }
  double error = error_threshold+1;
  int iteration = 1;

  //----------------------
  int O1value = 0;
  int O2value = 0;
  int O3value = 0;
  //----------------------

  while (error >= error_threshold)
  {
    cout << "iteration: " << iteration << std::endl;
    iteration++;
    for (i = 0; i < nValue; i++)
    {
      O1value++;
      c[i] = b[i];
      //cout << "before c[" << i << "]: " << c[i] << endl;
      for (j = 0; j < nValue; j++)
      {
        O2value++;
        if (i != j)
        {
          c[i] = c[i] - a(i, j) * x[j];
        }
      }
      //cout << "after c[" << i << "]: " << c[i]<<endl;
    }
    for (i = 0; i < nValue; i++) 
    {
      O3value++;
      x[i] = c[i] / a(i, i);
    }

    //error
    for (int i = 0; i < x.size(); i++)
    {
      error += std::abs(x[i] - x_previous[i]);
    }
    error /= x.size();
    //cout << "error: " << error << endl;
    x_previous = x;
  }
  cout << "O1:" << O1value << " ||O2:" << O2value << " ||O2: " << O3value <<  std::endl;
  cout << "iterations: " << iteration << std::endl;

  return x;
}


vector<double> jacobi::operator()(const compactmatrix<double>& a, const vector<double>& b) const
{
  if (a.size_row() <= 0 || a.size_col() <= 0)
  {
    throw std::invalid_argument("a matrix cannot have non positive rows/cols");
  }
  if (a.size_row() != a.size_col())
  {
    throw std::invalid_argument("a matrix must be a square");
  }
  if (a.size_col() != b.size())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }

  int i, j;
  vector<double> x(b.size()), c(b.size());
  vector<double> x_previous(b.size());

  for (int i = 0; i < b.size(); i++)
  {
    c[i] = b[i];
    x[i] = 0;
    x_previous[i] = 0;
  }

  double error = error_threshold+1;
  int iteration = 1;
  //----------------------
  int O1value = 0;
  int O2value = 0;
  int O3value = 0;
  //----------------------
  while (error >= error_threshold)
  {
    iteration++;
    //go through all values of a
    //--------------------------ITERATION
    int index = 0;
    int row = 0;
    int rowsize = a.size_row();
    while (row < rowsize)
    {
      O1value++;
      //int index_rowstart = a.rowindex(row);
      int index_end = a.rowindex(row + 1);
      i = a.row(index);
      j = a.col(index);
      c[i] = b[i];

      while (index != index_end) //&& index < a.size())
      {
        O2value++;
        i = a.row(index);
        j = a.col(index);
        if (i != j)
        {
          c[i] = c[i] - a.value(index) * x[j];
        }
        index++;
        if (index >= a.size())
        {
          break;
        }
      }

      row++;
    }

    for (int index = 0; index < a.size_row(); index++)
    {
      x[index] = c[index] / a.diag(index);
      O3value++;
    }

    //error
    for (int i = 0; i < x.size(); i++)
    {
      error += std::abs(x[i] - x_previous[i]);
    }
    error /= x.size();
    //cout << "error: " << error << endl;
    x_previous = x;
  }
  cout << "O1:" << O1value << " ||O2:" << O2value << " ||O2: " << O3value << std::endl;
  cout << "iterations: " << iteration << std::endl;
  return x;
}