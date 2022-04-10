#include<iostream>
#include<vector>
#include<string>
using namespace std;
template <typename T>
class Array
{
	private:
		T* elements; 						// Array of type T
		size_t size; 						// Number of array elements
	public:
		explicit Array(size_t arraySize);
		// Constructor
		Array(const Array& array); 			// Copy constructor
		//~Array();
		// noexcept swap function
		T& operator[](size_t index); 		// Subscript operator
		const T& operator[](size_t index) const; 		 // Subscript operator-const arrays
		void display();
};

template <typename T>
void Array<T>::display()
{
	for( int i = 0; i < size; i++ )
		cout<<elements[i]<<endl;
}

template <typename T>
Array<T>::Array( size_t arraySize )
{
	size = arraySize;
	elements = new string[arraySize];
}

// Copy constructor
template <typename T>
inline Array<T>::Array(const Array& array): Array{array.size}
{
	std::cout << "Array of " << size << " elements copied" << std::endl;
	for (size_t i {}; i < size; ++i)
		elements[i] = array.elements[i];
	
	cout<<endl<<"Copy cons called1";
}


// Construct an Array<> of a given size, filled with some arbitrary string data
Array<std::string> buildStringArray(const size_t size)
{
	Array<std::string> result{ size };
	for (size_t i = 0; i < size; ++i)
		result[i] = "You should learn from your competitor, but never copy. Copy and you die.";

	return result;
}

template <typename T>
T& Array<T>::operator[](size_t index)
{
	if (index >= size)
		throw std::out_of_range {"Index too large: " + std::to_string(index)};
	return elements[index];
}

template <typename T>
const T& Array<T>::operator[](size_t index) const
{
	if (index >= size)
		throw std::out_of_range {"Index too large: " + std::to_string(index)};
	return elements[index];
}

int main()
{
	const size_t numArrays{ 10 }; // Fill 10 Arrays with 1,000 strings
	const size_t numStringsPerArray{ 1 };
	std::vector<Array<std::string>> vectorOfArrays;
	vectorOfArrays.reserve(numArrays); // Inform the vector<> how many Arrays we'll be adding
	for (size_t i = 0; i < numArrays; ++i)
	{
		vectorOfArrays.push_back(buildStringArray(numStringsPerArray));
		cout<<2<<endl;
	}
	for( vector<Array<std::string>>::iterator it = vectorOfArrays.begin(); it != vectorOfArrays.end(); it++ )
	{
		//it->display();
		//cout<<endl<<endl<<endl;
	}
}