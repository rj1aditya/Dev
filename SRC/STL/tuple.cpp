#include<iostream>
#include<string>
#include<utility> // used for pair 
#include<tuple>
using namespace std;

class Student
{
	string name;
	int age;
	public:
	Student( string na = "aditya", int age = 100 ): name(na), age(age)
	{}
	
	void getDetails()
	{
		cout<<"name of student is: "<< name;
		cout<<" Age: "<< age;
	}
	
	friend ostream& operator<<(ostream &out, const Student &stu);
};

	ostream& operator<<(ostream &out, const Student &stu)
	{
		out<<"name of student is: "<< stu.name;
		out<<", Age: "<< stu.age<<" ,";
		return out;
	}
	
int main()
{
	tuple<Student, double, char> t1;
	Student stu("Aditya", 27);
	t1 = make_tuple( stu, 84.4,'A' );
	
	cout<<"student details is:"<<endl;
	cout<<get<0>(t1);
	cout<<"Percentage achieved: "<<get<1>(t1)<<endl;
	cout<<"Grade: "<<get<2>(t1)<<endl;
}