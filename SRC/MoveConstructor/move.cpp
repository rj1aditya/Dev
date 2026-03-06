#include<iostream>
#include<vector>
#include<string>
//#include<utility>
using namespace std;
template <typename T>
class Array
{
	private:
		T* elements; 						// Array of type T
		size_t size; 						// Number of array elements
	public:
		explicit Array(size_t arraySize); 	// Constructor
		Array(const Array& array); 			// Copy constructor
		~Array() 							// Destructor
		{
			//cout<<"destru"<<endl;
			//cout<<*elements<<endl;
			delete []elements;
		}
		Array& operator=(const Array& rhs); // Copy assignment operator
		T& operator[](size_t index); 		// Subscript operator
		const T& operator[](size_t index) const; 		 // Subscript operator-const arrays
		size_t getSize() const noexcept { return size; } // Accessor for size
		void swap(Array& other) noexcept; 				// noexcept swap function
		Array(Array&& array); // Move constructor
		Array& operator=(Array&& rhs);
};

template <typename T>
Array<T>::Array( size_t arraySize )
{
	size = arraySize;
	elements = new string[arraySize];
}

// Move constructor

template <typename T>
Array<T>::Array(Array&& moved): size{moved.size}, elements{moved.elements}
{
	std::cout << "Array of " << size << " elements moved" << std::endl;
	moved.elements = nullptr; // Otherwise destructor of moved would delete[] elements!
}

// Copy constructor
template <typename T>
inline Array<T>::Array(const Array& array): Array{array.size}
{
	//std::cout << "Array of " << size << " elements copied" << std::endl;
	for (size_t i {}; i < size; ++i)
		elements[i] = array.elements[i];
	cout<<endl<<"copy cons";
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

// Construct an Array<> of a given size, filled with some arbitrary string data
Array<std::string> buildStringArray(const size_t size)
{
	Array<std::string> result{ size };
	for (size_t i = 0; i < size; ++i)
		result[i] = "You should learn from your competitor, but never copy. Copy and you die.";

	return result;
}


//copy assignment operator
template <typename T>
Array<T>& Array<T>::operator=(const Array& rhs)
{
	std::cout << "Array of " << rhs.size << " elements copied (assignment)" << std::endl;
	if (this != &rhs) // prevent trouble with self-assignments
	{
		delete[] elements; // delete[] all existing elements
		elements = rhs.elements; // copy the elements pointer and the size
		size = rhs.size;
	}
	return *this; // return lhs
}

// Move assignment operator
template <typename T>
Array<T>& Array<T>::operator=(Array&& rhs)
{
	std::cout << "Array of " << rhs.size << " elements moved (assignment)" << std::endl;
	if (this != &rhs) // prevent trouble with self-assignments
	{
		delete[] elements; // delete[] all existing elements
		elements = rhs.elements; // copy the elements pointer and the size
		size = rhs.size;
		rhs.elements = nullptr; // make sure rhs does not delete[] elements
	}
	return *this; // return lhs
}

int main()
{
	const size_t numArrays{ 10 }; // Fill 10 Arrays with 1,000 strings
	const size_t numStringsPerArray{ 1000 };
	std::vector<Array<std::string>> vectorOfArrays;
	vectorOfArrays.reserve(numArrays); // Inform the vector<> how many Arrays we'll be adding
	for (size_t i = 0; i < numArrays; ++i)
	{
		vectorOfArrays.push_back(buildStringArray(numStringsPerArray));
		//cout<<endl<<2;
	}
	Array<string> obj(10);
	Array<string> obj1(100);
	obj1 = move(obj);
}