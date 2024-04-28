#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>
#include <iomanip>
#include <Menu.h>

using namespace std;

void GraphData() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, 15);
	ifstream inFS;
	ifstream inNow;
	string item;
	int count;
	string bar = "|";
	string graph = "";
	inFS.open("frequency.dat");

	if (!inFS.is_open()) {
		cout << "Could not open file" << endl;
		return;
	}

	// prints the graph
	cout << "HISTOGRAM OF ITEMS PURCHASED" << endl;
	cout << "============================\n" << endl;
	int k = 10;

	do {
		inFS >> item;
		if (item == "end") {
			// makes sure func prints end otherwise will print last item 2x
			return;
		}

		inFS >> count;
		for (int i = 0; i < count; i++) {
			if (i == count - 1) {
				graph += "|";
			}
			else {
				graph += bar;
			}
		}

		SetConsoleTextAttribute(hConsole, k);
		cout << setw(12) << right << item << "|" << setw(13) << left << graph << " " << setw(2) << right << count << endl;
		graph = "";
		k++;
		if (k == 14) {
			k = 10;
		}
		SetConsoleTextAttribute(hConsole, 15);

	} while (inFS);
}

string SearchItem(Menu& newMenu) {
	// handles the search function to get strings pass to python
	system("cls");
	string item;
	newMenu.SetNewCursor(0, 0);
	cout << "Enter an item to search for: ";
	cin >> item;
	return item;

}

void DrawTitle(Menu& mainMenu) {
	// draws a splash screen
	string splash[6];
	splash[0] = "    ______                                         ______                                      ";
	splash[1] = "   /  ____| _____  ______ ____     ____  _______  /  ____| _______ _____  _____ _____ _______  ";
	splash[2] = "   |  |    /  _  \\| '|__| '__\\  /    \ | '|__| |  |    _ | '|__|/     \/  __|/     \| '|__|  ";
	splash[3] = "   |  |___|  (_) | |  |  |  | | ||  _/__||  |    |  |___{ ||  |   | (_) || |___| _/__||  |     ";
	splash[4] = "    \\____\\_____/ |__|  |__| |_| \___/  |__|    \\_______||__|   \_____/\____/\___/  |__|     ";
	splash[5] = "                                                                                               ";

	// draws the left margin
	mainMenu.SetNewCursor(1, 0);
	cout << "|=========================================|\n" << endl;

	int row = 1;
	for (int i = 0; i < 6; i++) {
		mainMenu.SetNewCursor(row, 30);
		cout << splash[i] << endl;
		row++;
	}

	for (int i = 0; i < 25; i++) {
		mainMenu.SetNewCursor(i, 0);
		cout << "|";
		mainMenu.setNewCursor(i, 30);
		cout << "|";
	}

	mainMenu.SetNewCursor(25, 0);
	cout << "|=======================================|\n" << endl;

}

void ClearColumn(Menu& newMenu) {
	// clears the left column
	// avoids clearing sholw screen & reduce flashing
	string blank = "";
	for (int i = 0; i < 31; i++) {
		blank += " ";
	}

	for (int i = 0; i < 30; i++) {
		newMenu.SetNewCursor(i, 0);
		cout << blank;
	}
}

int MainMenu(Menu& newMenu, vector<string>& menuItems) {
	// handles main menu selections
	DrawTitle(newMenu);
	int selection = 0;
	newMenu.RunMenu(menuItems, selection);
	return selection;
}

void CallProcedure(string pName) {
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

int callIntFunc(string proc, string param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[proc.length() + 1];
	std::strcpy(paramval, param.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// initializes python interpretation
	Py_Initialize();
	// build the name object
	pName = PyUnicode_FromString((char*)"CornerGrocer");
	// loads the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference
	pDict = PyModule_GetDict(pModule);
	// pFunc is a borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// clean up 
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// finish python interpreter
	Py_Finalize();

	// clean
	delete[] procname;
	delete[] paramval;

	return _PyLong_AsInt(presult);
}

int callIntFunc(string proc, int param) {
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// initialize python interpreter
	Py_Initialize();
	// builds name object
	pName = PyUnicode_FromString((char*)"CornerGrocer");
	// loads module object
	pModule = PyIMport_Import(pName);
	// borrowed reference
	pDict = PyModule_GetDict(pModule);
	// borrowed reference
	pFunc = PyDict_GetItemString(pDict, procname);

	if (PyCallable_Check(pFunc)) {
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else {
		PyErr_Print();
	}

	Py_DECREF(pValue);
	// clean up 
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// finish python interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}

void main() {
	Menu mainMenu;
	int selection = 0;
	// modifies menu
	vector<string> menuItems = { "List all Items", "Search for an Item", "Print Graph", "Quit" };
	mainMenu.MenuModifier(menuItems);
	string instr[3] = { "select an item using", "the arrow keys and", "press 'enter' . . ." };
	mainMenu.HideCursorBlink();

	// show instructions
	int row = 8;
	for (int i = 0; i < 3; i++) {
		mainMenu.SetNewCursor(row, 3);
		cout << instr[i];
		row++;
	}

	bool run = true;

	// creates .dat file so that menu option 3 can be called
	CallProcedures("WritingItems");

	while (run) {
		selection = mainMenu(mainMenu, menuItems);
		switch (selection) {
			case 1: {
				ClearColumn(mainMenu);
				mainMenu.SetNewCursor(0, 0);
				CallProcedure("ListItems");
				cout << "\n";
				break;
			}
			case 2: {
				string s = SearchItem(mainMenu);
				system("cls");
				if (s == "999") {
					break;
				}
				int count = callIntFunc("SingleItem", s);
				if (count == 0) {
					cout << "No such item exists, try again" << endl;
				}
				else {
					cout << "The number of " << s << " sold today: " << cout << "\n\n";
				}

				system("pause");
				system("cls");
				int row = 8;
				for (int i = 0; i < 3; i++) {
					mainMenu.SetNewCursor(row, 3);
					cout << instr[i];
					row++;
				}
				break;
			}
			case 3: {
				// rewrites .dat file in case of updates
				CallProcedure("WriteItems");
				ClearColumn(mainMenu);
				mainMenu.SetNewCursor(0, 0);
				GraphData();
				break;
			}
			case 4: {
				system("cls");
				run = false;
				break;
			}
			default: {
				break;
			}
		} // end switch 
	}// end while 
}// end main