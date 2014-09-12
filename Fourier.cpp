#include "Fourier.h"

const long double PI = 3.1415926;



void isFuncPeriodic(TablePair &p_Data)
{
	double dif[2] = { 0, 0 };
	if (p_Data.size() > 2)
	{
	}

	else
	{
		for (TablePair::iterator i = p_Data.begin() + 1; i < p_Data.end() - 1; ++i)
		{
			dif[0] = i->first - (i - 1)->first;
			dif[1] = (i + 1)->first - i->first;

			if (dif[0] != dif[1])
				throw NonPeriodic;
		}
	}
}

double getPeriod(TablePair p_Data)
{
	isFuncPeriodic(p_Data);
	double period;
	int Size = p_Data.size();

	if (p_Data[0].second == p_Data[Size - 1].second)
	{
		period = p_Data[Size-1].first;
	}
	else
	{
		double diff = 0;
		diff = p_Data[Size-1].first - p_Data[Size-2].first;
		
		period = p_Data[Size-1].first + diff;

		if (period == 0)
			throw DivideByZero;
	}

	return period;

}

Fourier::Fourier() : MAX_HARMONICS(10)
{
	dirTerm = 0;
}

void Fourier::evalDirTerm(TablePair &p_Data)
{
	isFuncPeriodic(p_Data);

	int numTerms = 1;

	int Size = p_Data.size();

	if (p_Data[0].second== p_Data[Size-1].second)
		numTerms = p_Data.size() - 1;
	else
		numTerms = p_Data.size();

	double Sum = 0;

	for (TablePair::iterator i = p_Data.begin(); i < p_Data.end(); ++i)
	{
		Sum += i->second;
	}

	double Mean = Sum / numTerms;

	dirTerm = 2 * Mean;
}

void Fourier::evalSinTerm(TablePair &p_Data)
{
	isFuncPeriodic(p_Data);

	double period = getPeriod(p_Data);

	int numTerms = 1;
	int Size = p_Data.size();

	if (p_Data[0].second == p_Data[Size - 1].second)
		numTerms = p_Data.size() - 1;
	else
		numTerms = p_Data.size();

	double Sum = 0;

	for (int n = 0; n < MAX_HARMONICS; n++)
	{
		for (TablePair::iterator i = p_Data.begin(); i < p_Data.end(); ++i)
		{
			double coef;
			coef = (n*PI) / period;

			Sum += (i->second)*(std::sin(coef*(i->first)));

			n++;

		}

		double Mean = Sum / numTerms;
		sinTerms.push_back(2 * Mean);
	}	
}

void Fourier::evalCosTerm(TablePair &p_Data)
{
	isFuncPeriodic(p_Data);

	double period = getPeriod(p_Data);

	int numTerms = 1;
	int Size = p_Data.size();

	if (p_Data[0].second == p_Data[Size - 1].second)
		numTerms = p_Data.size() - 1;
	else
		numTerms = p_Data.size();

	double Sum = 0;

	for (int n = 0; n < MAX_HARMONICS; n++)
	{
		for (TablePair::iterator i = p_Data.begin(); i < p_Data.end(); ++i)
		{
			double coef;
			coef = (n*PI) / period;

			Sum += (i->second)*(std::cos(coef*(i->first)));

			n++;

		}

		double Mean = Sum / numTerms;
		cosTerms.push_back(2 * Mean);
	}
}

void Fourier::Evaluateterms(TablePair &p_Data)
{
	try
	{
		evalDirTerm(p_Data);
		evalCosTerm(p_Data);
		evalSinTerm(p_Data);
	}
	
	catch (ErrorCodes excpt)
	{
		if (excpt == NonPeriodic)
		{
			cout << "\nThe input data is non periodic. Can't gnerate Fourier Series.";
		}

		if (excpt == DivideByZero)
		{
			cout << "\nAttempt to divide by zero.";
		}
	}
}