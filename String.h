#pragma once
#include <iostream>

using namespace std;

class String {
	char* _str;
	size_t _size{ 0 };

public:
	String() : String("") {}

	String(const char* str) : _str(new char[strlen(str) + 1] {}) {
		auto len = strlen(str) + 1;
		strcpy_s(_str, len, str);
		set_length();
	}

	String(const String& str_copy) :
		String(str_copy.get_str()) {}

	~String() {
		delete[] _str;
	}

	char* get_str() const {
		return _str;
	}

	void append(const char* str) {
		auto len_source = strlen(str) + 1;
		auto len_destination = get_length() + 1;
		auto new_size = len_source + len_destination - 1;
		auto* tmp = _str;

		_str = new char[new_size] {};
		strcpy_s(_str, len_destination, tmp);
		strcat_s(_str, new_size, str);

		delete[] tmp;
		set_length();
	}

	size_t get_length() const {
		return _size;
	}

	errno_t replace(const char* str) {
		auto len = strlen(str) + 1;
		if (len - 1 > _size) {
			delete[] _str;
			_str = new char[len];
		}

		strcpy_s(_str, len, str);
		return 0;
	}

	errno_t replace(const String& str) {
		if (this == &str)
			return 1;

		return replace(str.get_str());
	}

	errno_t soft_remove_end(int value) {
		if (!is_correct_index(value))
			return -1;

		*(_str + get_length() - value) = '\0';
		set_length();
		return 0;
	}

	errno_t soft_remove_start(int value) {
		if (!is_correct_index(value))
			return -1;

		auto len = get_length();
		strcpy_s(_str, len - value + 1, _str + value);
		*(_str + len - value) = '\0';
		set_length();

		return 0;
	}

	String operator= (const String& str) {
		replace(str);
		return *this;
	}

	String operator+= (const String& str) {
		append(str.get_str());
		return *this;
	}

	String operator+= (const char* str) {
		append(str);
		return *this;
	}

	char operator[] (int index) const {
		if (index < 0 || index >= get_length())
			exit(1);

		return this->_str[index];
	}

	char& operator[] (int index) {
		if (index < 0 || index >= get_length())
			exit(1);

		return this->_str[index];
	}

	friend ostream& operator<< (ostream& out, const String& str) {
		out << str.get_str();
		return out;
	}

	friend istream& operator>> (istream& in, String& str) {
		const int size = 256;
		char buffer[size]{};

		gets_s(buffer, size);
		str = buffer;

		return in;
	}

private:
	bool is_correct_index(const int& index) const {
		return !(index > get_length() || index < 0);
	}

	void set_length() {
		_size = strlen(_str);
	}
};