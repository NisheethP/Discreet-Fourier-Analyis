#include "Functions.h"

void Functions::ClearScreen()
  {
  HANDLE                     hStdOut;
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  DWORD                      count;
  DWORD                      cellCount;
  COORD                      homeCoords = { 0, 0 };

  hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
  if (hStdOut == INVALID_HANDLE_VALUE) return;

  /* Get the number of cells in the current buffer */
  if (!GetConsoleScreenBufferInfo( hStdOut, &csbi )) return;
  cellCount = csbi.dwSize.X *csbi.dwSize.Y;

  /* Fill the entire buffer with spaces */
  if (!FillConsoleOutputCharacter(
    hStdOut,
    (TCHAR) ' ',
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Fill the entire buffer with the current colors and attributes */
  if (!FillConsoleOutputAttribute(
    hStdOut,
    csbi.wAttributes,
    cellCount,
    homeCoords,
    &count
    )) return;

  /* Move the cursor home */
  SetConsoleCursorPosition( hStdOut, homeCoords );
  }

int Functions::PressAnyKey(const char *prompt)
  {
  DWORD        mode;
  HANDLE       hstdin;
  INPUT_RECORD inrec;
  DWORD        count;
  char         default_prompt[] = "Press a key to continue...";

  /* Set the console mode to no-echo, raw input, */
  /* and no window or mouse events.              */
  hstdin = GetStdHandle( STD_INPUT_HANDLE );
  if (hstdin == INVALID_HANDLE_VALUE
  || !GetConsoleMode( hstdin, &mode )
  || !SetConsoleMode( hstdin, 0 ))
    return 0;

  if (!prompt) prompt = default_prompt;

  cout << prompt;
  
  FlushConsoleInputBuffer( hstdin );

  /* Get a single key RELEASE */
  do ReadConsoleInput( hstdin, &inrec, 1, &count );
  while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);

  /* Restore the original console mode */
  SetConsoleMode( hstdin, mode );

  return inrec.Event.KeyEvent.wVirtualKeyCode;
  }

void Functions::DrawLine(string String, int Len)
{
	int x = 0;
	cout << endl;
	for (int i = 0; i <Len; i++)
	{
		cout << String[x];
		if (x == (String.size()-1))
			x = -1;
		x++;
	}
	if (Len != 80)
		cout << endl;
}

int Functions::readkey()
  {
  HANDLE hstdin = GetStdHandle( STD_INPUT_HANDLE );
  DWORD  mode;
  GetConsoleMode( hstdin, &mode );
  SetConsoleMode( hstdin, 0 );

  INPUT_RECORD inrec;
  DWORD        count;

  do ReadConsoleInput( hstdin, &inrec, 1, &count );
  while ((inrec.EventType != KEY_EVENT) || inrec.Event.KeyEvent.bKeyDown);

  SetConsoleMode( hstdin, mode );

  return inrec.Event.KeyEvent.wVirtualKeyCode;
  }

HANDLE Global::hStdin = GetStdHandle(STD_INPUT_HANDLE); 
HANDLE Global::hStdout = GetStdHandle(STD_OUTPUT_HANDLE);


void Functions::SetColor(Color_t Fore)
{
	WORD fore;

	switch(Fore)
	{
	case 0:
		fore = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN;
		break;
	case 1:
		fore = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 2:
		fore = FOREGROUND_RED;
		break;
	case 3:
		fore = FOREGROUND_RED|FOREGROUND_INTENSITY;
		break;
	case 4:
		fore = FOREGROUND_BLUE;
		break;
	case 5:
		fore = FOREGROUND_BLUE|FOREGROUND_INTENSITY;
		break;
	case 6:
		fore = FOREGROUND_GREEN;
		break;
	case 7:
		fore = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 8:
		fore = FOREGROUND_BLUE|FOREGROUND_GREEN;
		break;
	case 9:
		fore = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 10:
		fore =  FOREGROUND_BLUE|FOREGROUND_RED;
		break;
	case 11:
		fore = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY;
		break;
	case 12:
		fore = FOREGROUND_RED|FOREGROUND_GREEN;
		break;
	case 13:
		fore = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	}

	SetConsoleTextAttribute(Global::hStdout,fore);
}

void Functions::SetColor(Color_t Fore, Color_t Back)
{
	WORD fore, back;

	switch(Fore)
	{
	case 0:
		fore = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN;
		break;
	case 1:
		fore = FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 2:
		fore = FOREGROUND_RED;
		break;
	case 3:
		fore = FOREGROUND_RED|FOREGROUND_INTENSITY;
		break;
	case 4:
		fore = FOREGROUND_BLUE;
		break;
	case 5:
		fore = FOREGROUND_BLUE|FOREGROUND_INTENSITY;
		break;
	case 6:
		fore = FOREGROUND_GREEN;
		break;
	case 7:
		fore = FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 8:
		fore = FOREGROUND_BLUE|FOREGROUND_GREEN;
		break;
	case 9:
		fore = FOREGROUND_BLUE|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	case 10:
		fore =  FOREGROUND_BLUE|FOREGROUND_RED;
		break;
	case 11:
		fore = FOREGROUND_BLUE|FOREGROUND_RED|FOREGROUND_INTENSITY;
		break;
	case 12:
		fore = FOREGROUND_RED|FOREGROUND_GREEN;
		break;
	case 13:
		fore = FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY;
		break;
	}

	switch(Back)
	{
	case 0:
		back = BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN;
		break;
	case 1:
		back = BACKGROUND_RED|BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
		break;
	case 2:
		back = BACKGROUND_RED;
		break;
	case 3:
		back = BACKGROUND_RED|BACKGROUND_INTENSITY;
		break;
	case 4:
		back = BACKGROUND_BLUE;
		break;
	case 5:
		back = BACKGROUND_BLUE|BACKGROUND_INTENSITY;
		break;
	case 6:
		back = BACKGROUND_GREEN;
		break;
	case 7:
		back = BACKGROUND_GREEN|BACKGROUND_INTENSITY;
		break;
	case 8:
		back = BACKGROUND_BLUE|BACKGROUND_GREEN;
		break;
	case 9:
		back = BACKGROUND_BLUE|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
		break;
	case 10:
		back =  BACKGROUND_BLUE|BACKGROUND_RED;
		break;
	case 11:
		back = BACKGROUND_BLUE|BACKGROUND_RED|BACKGROUND_INTENSITY;
		break;
	case 12:
		back = BACKGROUND_RED|BACKGROUND_GREEN;
		break;
	case 13:
		back = BACKGROUND_RED|BACKGROUND_GREEN|BACKGROUND_INTENSITY;
		break;
	}


	SetConsoleTextAttribute(Global::hStdout,fore|back);



	COORD cord;
	DWORD wrd;
	cord.X = 0;
	cord.Y = 0;

	FillConsoleOutputAttribute(Global::hStdout,fore|back,5e+15,cord,&wrd);
}

string Functions::encrypt(string &a,char key)
{
	for (int i = 0; i < a.size();i++)
	{
		a[i] ^= key;
	}
	return a;
}

string Functions::decrypt(string &a,char key)
{
	for (int i = 0; i < a.size();i++)
	{
		a[i] ^= key;
	}
	return a;
}

void Functions::gotoxy( int column = wherex(), int line = wherey())
{
	COORD coord;
	coord.X = column;
	coord.Y = line;
	SetConsoleCursorPosition(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		coord
		);
}

int Functions::wherex()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}

int Functions::wherey()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	if (!GetConsoleScreenBufferInfo(
		GetStdHandle( STD_OUTPUT_HANDLE ),
		&csbi
		))
		return -1;
	return csbi.dwCursorPosition.Y;
}


