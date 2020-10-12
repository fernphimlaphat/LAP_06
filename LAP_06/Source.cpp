#include<stdio.h>
#include<windows.h>
#include<conio.h>
#include<time.h>

char cursor(int x, int y) {
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2];
	COORD c = { x,y };
	DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];
}

void setcolor(int bg, int fg) {
	//bg background , fg foreground สีตัวอักษร
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE); //color = output
	SetConsoleTextAttribute(color, bg * 16 + fg); //(output ,เป็นอะไร)
}

void draw(int x, int y) {

	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" <-0-> ");
}

void drawPoint(int point) {
	setcolor(10,16);
	int x = 100, y = 0;
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("LastHighScore  = %d",point);
}


void drawAmmo(int x, int y)
{
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("O");

}
void deleteXY(int x, int y) {
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("       ");

}

void deleteX(int x, int y) {
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf(" ");

}

void deletecolor(int bg, int fg) {
	bg = 0, fg = 0;
	HANDLE color = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(color, bg * 16 + fg);
}
void setcursor(bool visible) {
	//cusur หายไป
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO Ipcursur;
	Ipcursur.bVisible = visible;
	Ipcursur.dwSize = 20;
	SetConsoleCursorInfo(console, &Ipcursur);

}

void auto_left(int x, int y)
{
	setcolor(6, 4);
	draw(x, y);
	Sleep(100);
	deletecolor(0, 0);
	deleteXY(x, y);
}

void auto_right(int x, int y)
{

	setcolor(6, 4);
	draw(x, y);

	deletecolor(0, 0);
	deleteXY(x + 8, y);

	Sleep(100);

	deletecolor(0, 0);
	deleteXY(x, y);
}

void Ammo(int x, int i)
{
	setcolor(5, 3);
	drawAmmo(x, i);
	cursor(x,i);
	deletecolor(0, 0);
	deleteX(x, i+1);


}

void blackAmmo(int x, int i)
{
	setcolor(0, 0);
	drawAmmo(x, i);
	cursor(x, i);
}

void drawEnermy(int x, int y) {

	setcolor(9, 15);
	COORD xy = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
	printf("*");
	cursor(x, y);
}

void spawEnermy()
{
	int i, x1 = 71, y1 = 6, x, y;
	srand(time(NULL));
	for (i = 1; i <= 3; i++)
	{
		x = rand() % x1;
		y = rand() % y1;
		drawEnermy(x + 10, y + 2);
	}
}

void enermy()
{
	int i, x1 = 71, y1 = 6, x, y;
	srand(time(NULL));
	for (i = 1; i <= 100; i++)
	{
		x = rand() % x1;
		y = rand() % y1;
		drawEnermy(x + 10, y + 2);
	}
}

void MoveAmmo(int x, int y, int i,int p)
{
	int j;
	char m = ' ';
	
		for ( j = 1; j <= 5; j++)
		{
			Beep(700, 100);
			for (i = y; i >= 0; i--)
			{
				Ammo(x + 3, i - 2);
				cursor(x + 3, i - 2);
				deleteXY(x + 2, y);
				auto_left(x, y);

				if (cursor(x + 3, i - 3) == '*')
				{
					Beep(700, 100);
					blackAmmo(x + 3, i - 3);
					blackAmmo(x + 3, i - 2);
					p = p + 1;
					drawPoint(p);

					break;
					
				}

				if (_kbhit()) {
					m = _getch(); if (m == 's') { blackAmmo(x + 3, i - 2); break; }
					else { blackAmmo(x + 3, i - 2); break; }
				}

			}
		}
	spawEnermy();
}



void Ship()
{
	setcursor(0);
	int x = 20, y = 20, i = y;
	setcolor(6, 4);
	draw(x, y);
	char m = ' ';
	enermy();
	int p = 0;
	drawPoint(p);

	do
	{
		if (_kbhit)
		{
			m = _getch();
			if (m == 'a') {


				for (x; x >= 0; x--)
				{

					auto_left(x, y);

					if (x == 0)
					{
						setcolor(6, 4);
						draw(x, y);
					}

					if (_kbhit())
					{
						m = _getch();
						if (m == 's') { setcolor(6, 4); draw(x, y);  break; }
						else if (m == ' ')
						{
							MoveAmmo(x, y, i,p);
						}
						if (x == 0)
						{
							setcolor(6, 4);
							draw(x, y);
						}
					}
				}
			}


			else if (m == 'd')
			{
				for (x; x <= 80; x++)
				{
					auto_right(x, y);
					if (x == 80)
					{
						setcolor(6, 4);
						draw(x + 1, y);
					}

					if (_kbhit())
					{
						m = _getch();
						if (m == 's')
						{
							setcolor(6, 4); draw(x, y); break;
						}

						else if (m == ' ')
						{
							MoveAmmo(x, y, i,p);

							if (x == 80)
							{
								setcolor(6, 4);
								draw(x, y);
							}
						}
					}

				}
			}

			else if (m == ' ')
			{
				Beep(700, 100);
				MoveAmmo(x, y, i,p);
				setcolor(6, 4);
				draw(x, y);
			}
		
	}

		} while (m != 'x');

	
}

int main() {
	Ship();
	//drawEnermy(20,5);
	//enermy();
}