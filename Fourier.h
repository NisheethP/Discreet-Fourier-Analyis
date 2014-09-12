#pragma once

#ifndef _FOURIER_H_
#define _FOURIER_H_

#include "Functions.h"
#include <utility>

typedef vector<double> IntVector;
typedef vector<std::pair<double, double>> TablePair;
typedef std::pair<double, double> FuncPair;

enum ErrorCodes
{
	NonPeriodic,
	DivideByZero,
	RowTooLarge
};

class Fourier
{
	double dirTerm;
	IntVector cosTerms;
	IntVector sinTerms;

	const int MAX_HARMONICS;

public:
	
	Fourier();
	void setDirTerm(double x)  { dirTerm = x / 2; }
	void addCosTerm(double x)	{ cosTerms.push_back(x); }
	void addSinTerm(double x)	{ sinTerms.push_back(x); }

	double getDirTerm()		{ return dirTerm; }
	IntVector getCosTerms()	{ return cosTerms;			}
	IntVector getSinTerms() { return sinTerms;			}

	void evalDirTerm(TablePair &p_Data);
	void evalCosTerm(TablePair &p_Data);
	void evalSinTerm(TablePair &p_Data);

	void Evaluateterms(TablePair &p_Data);
};

#endif // !1




