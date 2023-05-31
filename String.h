#pragma once
#include <iostream>

class String {
	char* _str;

public:
	String() : String("") {}

	String(const char* str) :
		_str(new char[strlen(str) + 1] {}) {
		auto len = strlen(str) + 1;
		strcpy_s(_str, len, str);
	}

	String(const String& str_copy) :
		String(str_copy._str) {}

	~String() {
		delete[] _str;
	}

	char* get_str() {
		return _str;
	}

	void append(const char* str) {
		auto len_source = strlen(str) + 1;
		auto len_destination = get_length() + 1;
		auto new_size = len_source + len_destination - 1;
		auto* tmp = _str;

		_str = new char[new_size] {};
		strcpy_s(_str, len_source, tmp);
		strcat_s(_str, new_size, str);

		delete[] tmp;
	}

	int get_length() { return strlen(_str); }

	errno_t soft_remove_end(int value) {
		if (!is_correct_index(value))
			return -1;

		*(_str + get_length() - value) = '\0';
		return 0;
	}

	errno_t soft_remove_start(int value) {
		if (!is_correct_index(value))
			return -1;

		auto len = get_length();
		strcpy_s(_str, len - value + 1, _str + value);
		*(_str + len - value) = '\0';
		return 0;
	}

private:
	bool is_correct_index(const int& index) {
		auto len = get_length();
		return !(index > len || index < 0);
	}
};
