#include "compactmatrix.h"

template<typename T>
compactmatrix<T>::compactmatrix(const matrix<T>& i_matrix)
{
  int col_size = i_matrix.cols();
  int row_size = i_matrix.rows();
  rowsize = row_size;
  colsize = col_size;
  m_size = 0;
  //find size
  for (int i = 0; i < row_size; i++)
  {
    for (int j = 0; j < col_size; j++)
    {
      if (i_matrix(i,j) != 0)
      {
        m_size++;
      }
    }
  }

  data = matrix<T>(m_size,3);//TODO use move here
  rowstarts = vector<int>(m_size);
  data_diag = vector<T>(row_size);

  int index = 0;
  for (int i = 0; i < row_size; i++)
  {
    rowstarts[i] = index;
    for (int j = 0; j < col_size; j++)
    {
      if (i_matrix(i,j) != 0)
      {
        data(index,0) = i; 
        data(index,1) = j; 
        data(index,2) = i_matrix(i,j); //value
        index++;
      }
    }
  }
  for (int i = 0; i < row_size; i++)
  {
    data_diag[i]= i_matrix(i, i);
  }
}

template<typename T>
int compactmatrix<T>::size()
{
  return m_size;
}

template<typename T>
int compactmatrix<T>::size() const
{
  return m_size;
}


template<typename T>
inline T compactmatrix<T>::value(int a)
{
  return data(a, 2);
}
template<typename T>
inline T compactmatrix<T>::col(int a)
{
  return data(a, 1);
}
template<typename T>
inline T compactmatrix<T>::row(int a)
{
  return data(a, 0);
}


template<typename T>
inline T compactmatrix<T>::value(int a) const
{
  return data(a, 2);
}
template<typename T>
inline T compactmatrix<T>::col(int a) const
{
  return data(a, 1);
}
template<typename T>
inline T compactmatrix<T>::row(int a) const
{
  return data(a, 0);
}


template<typename T>
inline int compactmatrix<T>::size_row()
{
  return rowsize;
}

template<typename T>
inline int compactmatrix<T>::size_col()
{
  return colsize;
}

template<typename T>
inline int compactmatrix<T>::size_row() const
{
  return rowsize;
}

template<typename T>
inline int compactmatrix<T>::size_col() const
{
  return colsize;
}

template<typename T>
int compactmatrix<T>::rowindex(int a) const
{
  return rowstarts[a];
}

template<typename T>
int compactmatrix<T>::rowindex(int a)
{
  return rowstarts[a];
}
template<typename T>
T compactmatrix<T>::diag(int a)
{
  return data_diag[a];
}

template<typename T>
T compactmatrix<T>::diag(int a) const
{
  return data_diag[a];
}

template<typename T>
ostream& operator << (ostream& os, const compactmatrix<T>& Obj)
{
  cout.precision(8); // as requested
  for (int i = 0; i < Obj.m_size; i++)
  {

    os << "Row: " <<Obj.data(i,0)<<" ";
    os << "Col: " <<Obj.data(i,1)<<" ";
    os << "Val: " <<Obj.data(i,2);

    if (i != Obj.m_size - 1)
    {
      os << "\n";
    }
  }
  return os;
}