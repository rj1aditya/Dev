#include <iostream>
#include <string>
#include <string_view>

class ArrayException
{
private:
	std::string m_error;

public:
	ArrayException(std::string error)
		: m_error{ error }
	{
	}

	std::string_view getError() const { return m_error; }
//	const char* getError() const { return m_error.c_str(); } // C++14 or earlier, use this instead
};

class IntArray
{
private:

	int m_data[3]{}; // assume array is length 3 for simplicity
public:
	IntArray() {}

	int getLength() const { return 3; }

	int& operator[](const int index)
	{
		if (index < 0 || index >= getLength())
			throw ArrayException{ "Invalid index" };

		return m_data[index];
	}

};

int main()
{
	IntArray array;

	try
	{
		int value{ array[5] }; // out of range subscript
	}
	catch (const ArrayException& exception)
	{
		std::cerr << "An array exception occurred (" << exception.getError() << ")\n";
	}
}