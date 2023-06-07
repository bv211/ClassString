#include <iostream>
#include <Windows.h>
#include "String.h"

using namespace std;

int main()
{
	setlocale(0, "");
	SetConsoleCP(1251);

	String str("Hello");
	String str1("Hello");
	cout << str.get_str() << endl;

	str.replace(str1);
	cout << str << endl;

	return 0;
}