#include "Poisson.h"


Poisson::Poisson(const string input_file, const string output_file, double forcing_function) :
file_input(input_file), file_output(output_file), image(retrieve(file_input)),
A(createPoissonAMatrix(image)), compact_A(A),
b(createBvector(forcing_function))
{}

vector<double> Poisson::createBvector(double input_ff)
{
  vector<double> b_temp(A.rows());
  for (int i = 0; i < A.rows(); i++)
  {
    b_temp[i] = input_ff;
  }
  return b_temp;
}

matrix<double> Poisson::createPoissonAMatrix(matrix<bool> givenMatrix)
{
  int n;
  int rows = givenMatrix.rows();
  int cols = givenMatrix.cols();
  if (rows != cols)
  {
    n = std::sqrt(rows * cols);
  }
  else
  {
    n = rows;
  }
  //int size = std::pow((n - 1), 2);
  int size = rows * cols;
  double adjacentValue = -0.25;
  double iValue = 1.0;
  matrix<double> mat(size, size);

  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++) //check diag
    {
      if (j == i)
      {
        mat(i, j) = iValue;
      }
      else
      {
        mat(i, j) = 0.0;
      }
    }
  }

  //updownleftright
  int ydir[4] = { 1,-1,0, 0 };
  int xdir[4] = { 0, 0,-1,1 };
  auto canplace = [=](int&& x, int&& y)
  {
    //isnotoutofBounds
    bool result = (x < 0 || x > cols - 1 || y<0 || y>rows - 1) ? false : true;

    if (result)
    {
      bool hasnoKnownValue = (givenMatrix(y, x) != 0) ? true : false;
      //if has known value put it to bool
      return hasnoKnownValue;
    }
    //cout << "\nResult: " << x << "|" << y << "|" << result;
    return result;
  };

  int matrow = 0;
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) //check diag
    {
      //up
      if (canplace(xdir[0] + j, ydir[0] + i))
      {
        mat(matrow, matrow + (cols)) = adjacentValue;
      }
      //down
      if (canplace(xdir[1] + j, ydir[1] + i))
      {
        mat(matrow, matrow - (cols)) = adjacentValue;
      }
      //left
      if (canplace(xdir[2] + j, ydir[2] + i))
      {
        mat(matrow, matrow - 1) = adjacentValue;
      }
      //right
      if (canplace(xdir[3] + j, ydir[3] + i))
      {
        mat(matrow, matrow + 1) = adjacentValue;
      }
      matrow++;
    }
  }
  return mat;
}

inline void Poisson::solve(solverInterface<double>& s)
{
  answer = s(A, b);
  printtofile(file_output);
  cout << "Outputting File: " << file_output;
}

inline void Poisson::fastsolve(solverInterface<double>& s)
{
  answer = s(compact_A, b);
  printtofile(file_output);
  cout << "Outputting File: " << file_output;
}



void Poisson::printtofile(string file)
{
  //string fileHeatMap = "heat.csv";
  string fileHeatMap = file;
  std::ofstream fout(fileHeatMap);

  //int rows = 100;
  //int cols = 100;
  int rows = image.rows();
  int cols = image.cols();
  int n = std::sqrt(rows * cols);

  for (int i = 0; i < rows * cols; i++)
  {
    if (i % cols == 0 && i != 0)
    {
      fout << "\n";
    }
    fout << answer[i];

    if (i != ((rows * cols) - 1))
    {
      fout << ",";
    }
  }
}

matrix<bool> Poisson::retrieve(string textfile)
{
  std::ifstream finput("output.txt");

  string temp_input;
  int numlines = 0;
  std::getline(finput, temp_input);
  //run until non empty line has been found.
  while (temp_input.length() == 0)
  {
    std::getline(finput, temp_input);
  }
  vector<string> temp_vector;

  //Get coloumn of string
  std::istringstream tokenStream(temp_input);
  std::istream_iterator<char> eos;              // end-of-stream iterator
  std::istream_iterator<char> iit(tokenStream);   // stdin iterator
  int input_coloumn = 0;
  while (iit != eos)
  {
    input_coloumn++;
    ++iit;
  }
  //-----------------

  while (temp_input.length() != 0)
  {
    numlines++;
    temp_vector.resize(numlines);
    temp_vector[numlines - 1] = temp_input;
    std::getline(finput, temp_input);
  }

  matrix <bool> new_m(numlines, input_coloumn);

  for (int i = 0; i < numlines; i++)
  {
    tokenStream = std::istringstream(temp_vector[i]);//reset stream
    iit = std::istream_iterator<char>(tokenStream);
    for (int j = 0; j < input_coloumn; j++)
    {
      if (*iit == 'B')
      {
        new_m(i, j) = true;
      }
      else
      {
        new_m(i, j) = false;
      }

      ++iit;
    }
  }
  finput.close();
  return new_m;
}