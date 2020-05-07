#include "gaussseidel.h"


gaussseidel::gaussseidel(double input_threshold):
error_threshold(input_threshold) 
{
  if (error_threshold < 0)
  {
    throw std::invalid_argument("error must be positive");
  }
}

vector<double> gaussseidel::operator()(const matrix<double>& a,
  const vector<double>& b) const
{
  if (a.rows() <= 0 || a.cols() <= 0)
  {
    throw std::invalid_argument("a matrix cannot have non positive rows/cols");
  }
  if (a.cols() != b.size())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }
  int i, j, nValue;
  vector<double> m(b.size()), x(b.size());
  vector<double> x_previous(b.size());
  nValue = b.size(); //value of n

  for (int i = 0; i < b.size(); i++)
  {
    m[i] = 0;
    x[i] = 0;
    x_previous[i] = 0;
  }

  double error = 100;
  //int iteration = 1;
  while (error >= 0.02) //p is size
  {
    //cout << "iteration: " << iteration << endl;
    //iteration++;

    for (i = 0; i < nValue; i++) {
      x[i] = (b[i] / a(i, i));
      for (j = 0; j < nValue; j++) {
        if (j != i)
        {
          x[i] = x[i] - ((a(i, j) / a(i, i)) * m[j]);
          m[i] = x[i];
        }
      }
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

  //cout << "iterations: " << iteration << std::endl;
  return x;
}

vector<double> gaussseidel::operator()(const compactmatrix<double>& a, const vector<double>& b) const
{
  if (a.size_row() <= 0 || a.size_col() <= 0)
  {
    throw std::invalid_argument("a matrix cannot have non positive rows/cols");
  }
  if (a.size_col() != b.size())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }


  int i, j;
  vector<double> m(b.size()), x(b.size());
  vector<double> x_previous(b.size());

  for (int i = 0; i < b.size(); i++)
  {
    m[i] = 0;
    x[i] = 0;
    x_previous[i] = 0;
  }
  //int b[3] = { 4,-6,7 };
  double error = 100;
  //int iteration = 1;
  while (error >= 0.02)
  {
    //cout << "iteration: " << iteration << endl;
    //iteration++;
    //go through all values of a
    //for (int index = 0; index < a.size(); index++)
    //--------------------------ITERATION
    int index = 0;
    int row = 0;
    int rowsize = a.size_row();
    while (row < rowsize)
    {
      //int index_rowstart = a.rowindex(row);
      int index_end = a.rowindex(row + 1);
      i = a.row(index);
      x[i] = (b[i] / a.diag(row));

      while (index != index_end && index < a.size())
      {
        //cout << i << ":" << j << endl;

        i = a.row(index);
        j = a.col(index);
        if (i != j)
        {
          x[i] = x[i] - ((a.value(index) / a.diag(row)) * m[j]);
          m[i] = x[i];
        }
        index++;
      }
      row++;
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
  //cout << "iterations: " << iteration << std::endl;
  return x;
}
