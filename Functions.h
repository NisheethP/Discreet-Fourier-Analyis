#pragma once
#ifndef _FUNCTIONS_H_INCLUDED_
#define _FUNCTIONS_H_INCLUDED_

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <exception>
#include <ctime>
#include <cctype>
#include <Windows.h>
#include <algorithm>
#include <map>

using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;
using std::map;

namespace Functions
{
	enum Color_t 
	{
		Gray, White ,DarkRed,Red,DarkBlue, Blue, DarkGreen,Green,DarkCyan,Cyan,DarkMagenta,Magenta,DarkYellow,Yellow, None
	};

	void ClearScreen();

	template <typename T>
	void Swap(T& a, T& b)
	{
		T c;
		c = b;
		b = a;
		a = c;
	}
	
	int PressAnyKey(const char *prompt = "\n\nPress any key to continue . . .");
	void DrawLine(string String, int Len = 80);
	int readkey();
	
	void SetColor(Color_t Fore = White);

	void SetColor(Color_t Fore, Color_t Back);

	string encrypt(string&, char key = rand()%121+1);
	string decrypt(string&, char key);

	void gotoxy(int column, int line);
	int wherex();
	int wherey();
	bool isPressed(int vkey);
}

struct Global
{
	static HANDLE hStdin;
	static HANDLE hStdout;
};

template <typename T>
class Array2D
{
public:
  // constructor
  Array2D(unsigned wd,unsigned ht)
    : nWd(wd), nHt(ht), pAr(0)
  {
    if(wd > 0 && ht > 0)
      pAr = new T[wd * ht];
  }

  // destructor
  ~Array2D()
  {
    delete[] pAr;
  }

  // indexing (parenthesis operator)
  //  two of them (for const correctness)

  const T& operator () (unsigned x,unsigned y) const
  {  return pAr[ y*nWd + x ];   }

  T& operator () (unsigned x,unsigned y)
  {  return pAr[ y*nWd + x ];   }

  // get dims
  unsigned GetWd() const { return nWd; }
  unsigned GetHt() const { return nHt; }


  // private data members
private:
  unsigned nWd;
  unsigned nHt;
  T*       pAr;

  // to prevent unwanted copying:
  Array2D(const Array2D<T>&);
  Array2D& operator = (const Array2D<T>&);
};


using Functions::ClearScreen;
//using Functions::PressAnyKey;
using Functions::DrawLine;
using Functions::SetColor;
using Functions::Color_t;
using Functions::readkey;
using Functions::gotoxy;
using Functions::wherex;
using Functions::wherey;


using Functions::Blue;
using Functions::Cyan;
using Functions::DarkBlue;
using Functions::DarkCyan;
using Functions::DarkGreen;
using Functions::DarkMagenta;
using Functions::DarkRed;
using Functions::DarkYellow;
using Functions::Gray;
using Functions::Green;
using Functions::Magenta;
using Functions::Red;
using Functions::White;
using Functions::Yellow;
#endif


