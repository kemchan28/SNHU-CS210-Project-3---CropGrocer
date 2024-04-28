#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include "Menu.h"

using namespace std;

int Menu::CheckKeyPress() {
	if ((GetAsyncKeyState(0x51) & 0x01)) {		//'q' key for quit
		return 1;
	}
	else if ((GetAsyncKeyState(0x0D) & 0x01)) {	// enter
		return 2;
	}
	else if ((GetAsyncKeyState(0x28) & 0x01)) {	// down arrow
		return 3;
	}
	else if ((GetAsyncKeyState(0x26) & 0x01)) {	// up arrow
		return 4;
	}
	else {										// continue
		return 0;
	}
}

void Menu::DrawMenu(string[], int itemsLength, itn selection) {
	int selected = 240;
	int unselected = 15;

	for Iint i = 0; i < itemsLength; i++){
		SetNewCursor(i * 2, 2);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unselected);

		if (i == selection - 1) {
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), selected);
		}
		cout << items[i] << endl;
		SetNewCursor(6, 20);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), unselected);
	}
}

void Menu::RunMenu(vector <string> menu, int& selection) {
	bool i = true;
	int j = 0;
	DrawMenu(menu, selection);
	while (i) {
		j = CHeckKeyPress();
		if (j == 3) {				// down
			selection++;
			if (selection > menu.size()) {
				selection = 1;
			}
		}
		else if (j == 4) {			// up
			selection--;
			if (selection < 1) {
				selection = menu.size();
			}
		}
		else if (j == 1) {			// quit
			i = false;
		}
		else if (j == 2) {			// enter
			return;
		}
		DrawMenu(menu, selection);
	}
}

void Menu::SetNewCursor(int row, int col) {
	static const HANDLE hOut = GetStdHandle(STD_OUPUT_HANDLE);
	cout.flush();
	COORD coord = { (SHORT)col, (SHORT)row };
	SetConsoleCursorPosition(hOut, coord);

}

void Menu::HideCursorBlink() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);

}

void Menu::MenuModifier(vector<string>& menu) {
	int max = 0;
	int min = 0;
	int spaces = 0;
	string temp = "";
	string space = "";

	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() > max) {
			max = menu.at(i).length();
		}
	}
	max += 10;
	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() % 2 != 0) {
			menu.at(i) += " ";
		}

		min = max - menu.at(i).length();
		min /= 2;
		for (int j = 0; j < min; j++) {
			space = " ";
		}

		menu.at(i) = space + menu.at(i) + space;
		space = "";
	}

	for (int i = 0; i < menu.size(); i++) {
		if (menu.at(i).length() < max) {
			menu.at(i) + " ";
		}
	}
}

void Menu::SetWindowSize(int w, int h) {
	HWND console = GetConsoleWindow();
	RECT ConsoleRect;
	GetWindowRect(console, &ConsoleRect);
	MoveWindow(console, ConsoleRect.left, ConsoleRect.top, w, h, TRUE);

}

int Menu::GetWindowWidth() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	int columns;
	int rows;

	GetConsoleSCreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
	columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

	return columns;
}