#include<iostream> 
using namespace std; 
class Person { 
public: 
	Person(int x) { cout << "Person::Person(int ) called" << endl; } 
	Person()	 { cout << "Person::Person() called" << endl; } 
	virtual void getAge() = 0;
	virtual void getName() = 0;//{cout<<"I should not have to come here"<<endl<<endl;}
}; 

class Faculty : virtual public Person { 
public: 
	Faculty(int x):Person(x) { 
	cout<<"Faculty::Faculty(int ) called"<< endl; 
	} 
	Faculty()
	{
		cout<<"Faculty class construct"<<endl;
	}
	
	void getAge()
	{
		cout<<"Faculty: I donno your age"<<endl<<endl;
		//getName();
	}
		void getName()
	{
		cout<<"Faculty: I donno your name"<<endl<<endl;
		//getAge();
	}
}; 

class Student : virtual public Person { 
public: 
	Student(int x):Person(x) { 
		cout<<"Student::Student(int ) called"<< endl; 
	} 
	Student()
	{
		cout<<"Student class construct"<<endl;
	}
	
	void getAge()
	{
		cout<<"Student: I donno your age"<<endl<<endl;
		//getName();
	}
		void getName()
	{
		cout<<"Student: I donno your name"<<endl<<endl;
		//getAge();
	}	
}; 

class TA : virtual public Faculty, virtual public Student { 
public: 
	TA(int x):Student(x), Faculty(x) { 
		cout<<"TA::TA(int ) called"<< endl; 
	} 
	TA()
	{
		cout<<"TA class constructor"<<endl;
	}
}; 

int main() { 
	TA *ptr = new TA;
	Student *s = ptr;
	Faculty *f = ptr;
	
	ptr->getName();
	s->getName();
	f->getName();
	//Student s;
} 
