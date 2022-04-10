#include<iostream>
#include<string>
#include<utility> // used for pair 

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
	pair<Student, int> p1;
	Student stu("Aditya", 27);
	p1 = make_pair( stu, 84 );
	
	cout<<"student details is:"<<endl;
	cout<<p1.first;
	cout<<"Percentage achieved: "<<p1.second<<endl;
}