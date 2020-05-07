#include "cholesky.h"

vector<double> cholesky::operator()(const matrix<double>& a, const vector<double>& b) const
{
  if (a.rows() <= 0 || a.cols()<=0)
  {
    throw std::invalid_argument("a matrix cannot have non positive rows/cols");
  }
  if (a.rows() != a.cols())
  {
    throw std::invalid_argument("a matrix must be a square");
  }
  if (a.cols() !=b.size())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }

  matrix<double> l(a.rows(), a.cols());
  int size = a.rows();

  for (int i = 0; i < a.rows(); i++)
  {
    for (int j = 0; j < a.cols(); j++)
    {
      l(i, j) = 0;
    }
  }
  Cholesky_Decomposition(a, l);
  //cout << l;

  //matrix<double> lt = l.transpose();
  vector<double> f(size);
  vector<double> final(size);
  for (int i = 0; i < size; i++)
  {
    f[i] = 0;
    final[i] = 0;
  }
  //try to skip the leading zeros
  //forward
  for (int i = 0; i < size; i++)
  {
    double s = 0;
    for (int j = 0; j < i; j++)
    {
      if (l(i, j) != 0)
      {
        s = s + l(i, j) * f[j];
      }
    }
    f[i] = (b[i] - s) / l(i, i);
  }

  //cout << "\nF:\n" << f;
  //backward //can use l again since in this case our a matrix is symmetric and compact
  for (int i = size - 1; i >= 0; i--) //ltranspose
  {
    double s = 0;
    for (int j = size - 1; j >= i; j--)
    {
      if (l(i, j) != 0)
      {
        s = s + l(i, j) * final[j];
      }
    }
    final[i] = (f[i] - s) / l(i, i);
  }
  //cout << "\nfinal:\n" << final;
  return final;
}
//------------------------------------

vector<double> cholesky::operator()(const compactmatrix<double>& a, const vector<double>& b) const
{
  if (a.size_row() <= 0 || a.size_col()<= 0)
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

  matrix<double> l(a.size_row(), a.size_col());
  int size = a.size_row();

  for (int i = 0; i < a.size_row(); i++)
  {
    for (int j = 0; j < a.size_col(); j++)
    {
      l(i, j) = 0;
    }
  }
  Cholesky_Decomposition(a, l);

  matrix<double> lt = l.transpose();
  vector<double> f(size);
  vector<double> final(size);
  for (int i = 0; i < size; i++)
  {
    f[i] = 0;
    final[i] = 0;
  }
  //forward
  for (int i = 0; i < size; i++)
  {
    double s = 0;
    for (int j = 0; j < i; j++)
    {
      s = s + l(i, j) * f[j];
    }
    f[i] = (b[i] - s) / l(i, i);
  }
  //cout << "\nF:\n" << f;
  //backward
  for (int i = size - 1; i >= 0; i--) //ltranspose
  {
    double s = 0;
    for (int j = size - 1; j >= i; j--)
    {
      s = s + lt(i, j) * final[j];
    }
    final[i] = (f[i] - s) / lt(i, i);
  }
  //cout << "\nfinal:\n" << final;
  return final;
}
//----------------------------

void cholesky::Cholesky_Decomposition(const matrix<double>& a, matrix<double>& lower) const
{
  if (lower.rows() != a.rows() || lower.cols() != a.cols())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }

  int n = a.rows();

  for (int i = 0; i < n; ++i)
  {
    for (int k = 0; k < i; ++k)
    {
      double value = a(i, k);
      if (value != 0)
      {
        //cout << "Value: " << value << "| " << i << " " << k << endl;
      }
      for (int j = 0; j < k; ++j)
      {
        value -= lower(i, j) * lower(k, j);
      }
      lower(i, k) = value / lower(k, k);
      if (value != 0)
      {
        //cout << "lower(i, k): " << lower(i, k) << "| " << i << " " << k << endl;
      }
    }

    //cout << endl << endl << lower;
    double value = a(i, i);
    for (int j = 0; j < i; ++j)
      value -= lower(i, j) * lower(i, j);
    lower(i, i) = std::sqrt(value);
  }

  // Displaying Lower Triangular and its Transpose 
  //cout << lower;
}


void cholesky::Cholesky_Decomposition(const compactmatrix<double>& a, matrix<double>& lower) const
{
  if (lower.rows() != a.size_row() || lower.cols() != a.size_col())
  {
    throw std::invalid_argument("a matrix coloumn must equal b vector size");
  }
  //int j;

  int index = -1;
  //int size_m = a.size();
  int row = 0;
  int rowsize = a.size_row();
  //cout << endl << endl;
  while (row < rowsize)
  {
    int index_rowstart = a.rowindex(row);
    //int index_end = a.rowindex(row + 1);
    index = index_rowstart;
    //skips initial coloumns of zeros
    for (int k = a.col(index); k < row; ++k)
    {
      double value = 0;
      if (k == a.col(index))
      {
        value = a.value(index);
        index++;
        //cout << "Value: " << value << "| " << row << " " << k << endl;
      }
      for (int j = 0; j < k; ++j)
      {
        value -= lower(row, j) * lower(k, j);
      }
      lower(row, k) = value / lower(k, k);
      //cout << "lower(i, k): " << lower(row, k) << "| " << row << " " << k << endl;
    }
    //FIRST PART END
    //2nd part
    //T value = a(i, i); do this
    double value = a.diag(row);
    for (int j = 0; j < row; ++j)
    {
      value -= lower(row, j) * lower(row, j);
    }
    lower(row, row) = std::sqrt(value);
    row++;
  }
  // Displaying Lower Triangular and its Transpose 
  //cout << lower;
}