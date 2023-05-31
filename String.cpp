#include <iostream>
#include <Windows.h>
#include "String.h"

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);

	String str("Hello");
	cout << str.get_str() << endl;

	str.append(" world!");
	cout << str.get_str() << endl;

	str.soft_remove_start(4);
	cout << str.get_str() << endl;

	return 0;
}