#include "Fourier.h"
#include "Functions.h"
#include <conio.h>
#include <utility>

enum TermNum {first, second};

const double MIN = -5000.29916;

class Coord
{
public:
	int x;
	int y;
	Coord()
	{
		x = 0;
		y = 0;
	};
	Coord(int X, int Y)
	{
		x = X;
		y = Y;
	}

	bool operator== (Coord p_Coord)
	{
		return (p_Coord.x == this->x) && (p_Coord.y == this->y);
	}

	bool operator!= (Coord p_Coord)
	{
		return (p_Coord.x != this->x) && (p_Coord.y != this->y);
	}
};

void hilight(Coord crd, int length);
void delight(Coord crd, int length);
int HiCoordToTabRow(Coord hiCoord, const Coord INIT_HI_COORD);
void drawTable(int entries, const Coord INIT_COORD, TablePair data);
int getNumLength(TablePair data, int row, TermNum term);

int main()
{
	TablePair data;
	Fourier Series;

	int entries = 0;

	while (true)
	{		
		ClearScreen();
		cout << "\n\n\t\tPlease input number of terms: ";
		cin >> entries;

		if (entries <= 0)
			Functions::PressAnyKey("Please enter positive integer for number of terms!");
		else
			break;
	}

	for (int i = 0; i < entries; ++i)
	{
		data.push_back(FuncPair(MIN, MIN));
	}

	const Coord INIT_COORDS = Coord(5, 12);
	const Coord INIT_HI_COORDS = Coord(INIT_COORDS.x + 5, INIT_COORDS.y);
	Coord HiCoords = INIT_HI_COORDS;

	bool isTakingInput = true;

	do
	{
		ClearScreen();

		drawTable(entries, INIT_COORDS, data);
			
		const Coord DELTA_COORD = Coord(20,1);
		int row = HiCoordToTabRow(HiCoords, INIT_HI_COORDS);
		
		string *numString = new string(std::to_string(1.0));
		
		int length = numString->length() + 3;				
		
		delete numString;

		hilight(HiCoords, length);

		char inp = _getch();

		switch (inp)
		{
			case 'w':
				if (HiCoords.y != INIT_HI_COORDS.y)
				{
					delight(HiCoords, length);
					HiCoords.y -= DELTA_COORD.y;
				}
				break;
			
			case 's':
				if (HiCoords.y != INIT_HI_COORDS.y + entries-1)
				{
					delight(HiCoords, length);
					HiCoords.y += DELTA_COORD.y;
				}
				break;
			
			case 'a':
				if (HiCoords.x != INIT_HI_COORDS.x)
				{
					delight(HiCoords, length);
					HiCoords.x -= DELTA_COORD.x;
				}
				break;
			
			case 'd':
				if (HiCoords.x != INIT_HI_COORDS.x + 20)
				{
					delight(HiCoords, length);
					HiCoords.x += DELTA_COORD.x;
				}
				break;
			case 13:
			{
				double val_Inp;
				
				gotoxy(INIT_COORDS.x, INIT_HI_COORDS.y + entries + 1);
				cout << "Enter Term: ";
				cin >> val_Inp;

				row = HiCoordToTabRow(HiCoords,INIT_HI_COORDS);

				if (HiCoords.x == INIT_HI_COORDS.x)
					data[row].first = val_Inp;


				else if (HiCoords.x == INIT_HI_COORDS.x + DELTA_COORD.x)
					data[row].second = val_Inp;
			}
				break;

			case 'p':
				isTakingInput = false;
				break;
		}
	} while (isTakingInput);

	Series.Evaluateterms(data);

	Functions::PressAnyKey();
	return 0;
}

void hilight(Coord crd, int length)
{
	WORD fore = FOREGROUND_BLUE | FOREGROUND_INTENSITY;
	WORD back = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore | back, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}

void delight(Coord crd, int length)
{
	WORD fore = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY;

	COORD cord;
	DWORD wrd;
	cord.X = crd.x;
	cord.Y = crd.y;

	FillConsoleOutputAttribute(Global::hStdout, fore, length, cord, &wrd);

	//cout << endl;
	//cout << wrd;
}

void drawTable(int entries, const Coord INIT_COORD, TablePair data)
{

	gotoxy(15, 10);
	cout << "X";

	gotoxy(25, 10);
	cout << "|";

	gotoxy(35, 10);
	cout << "f(X)";

	gotoxy(7, 11);
	for (int i = 7; i <= 42; ++i)
	{
		if (i == 25)
			cout << "+";
		else
			cout << "-";
	}

	gotoxy(6, 11);
	cout << "+";

	for (int i = 0; i < entries + 2; ++i)
	{
		gotoxy(6, 10 + i);
		if ((10 + i) != 11)

			cout << "|";
	}

	for (int i = 0; i < entries; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			Coord curCoord = Coord(0, 0);
			curCoord.x = INIT_COORD.x + j * 10;
			curCoord.y = INIT_COORD.y + i;

			gotoxy(curCoord.x, curCoord.y);

			switch (j)
			{
			case 0:
				cout << i + 1;
				break;

			case 1:
				if (data[i].first == MIN)
					cout << " ";
				else
				{
					gotoxy(curCoord.x - 3, curCoord.y);
					cout << data[i].first;
				}
				break;

			case 2:
				cout << "|";
				break;

			case 3:
				if (data[i].second == MIN)
					cout << " ";
				else
				{
					gotoxy(curCoord.x - 3, curCoord.y);
					cout << data[i].second;
				}
				break;
			}
		}
	}
}

int HiCoordToTabRow(Coord hiCoord, const Coord INIT_HI_COORD)
{
	return hiCoord.y - INIT_HI_COORD.y;
}