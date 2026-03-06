#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Employee{
public:
    string name;
    int id;
    Employee(int i, string n):id(i), name(n) {

    }
};

class EmployeeDAO {
public:
    EmployeeDAO() = default;

    virtual void getEmployeeInfo(int id) = 0;
    virtual void createEmployee(Employee *e) = 0;
    virtual void showAllEmployees() = 0;
};

class EmployeeDAOImpl: public EmployeeDAO {
    vector<Employee*> employees;

    EmployeeDAOImpl() = default;
    void getEmployeeInfo(int id) {
        cout <<"From database using following id="<<id<<" Will fetch the employee info and return to the client\n";
    }

    void createEmployee(Employee *e) {
        cout <<"Following user info will be saved into the database:\n";
        cout <<"Employee Name="<<e->name <<" Employee Id="<<e->id<<endl;
        employees.push_back(e);
    }

    void showAllEmployees() {
        for (auto e : employees) {
            cout <<"Employee Name="<<e->name <<" Employee Id="<<e->id<<endl;
        }
    }
    friend class EmployeeDAOProxy;
};

class EmployeeDAOProxy: public EmployeeDAO {
    EmployeeDAOImpl *realObj;
    string userRole;
    public:
    EmployeeDAOProxy(string role):userRole(role) {
        realObj = new EmployeeDAOImpl();
    };

    void getEmployeeInfo(int id) {
        if (userRole == "Admin" || userRole == "User")
            realObj->getEmployeeInfo(id);
        else {
            cout <<"NO Access\n";
        }
    }

    void createEmployee(Employee *e) {
        if (userRole == "Admin") {
            realObj->createEmployee(e);
        }
        else {
            cout <<"No Access\n";
        }
    }

    void showAllEmployees() {
        if (userRole == "Admin" || userRole == "User")
            realObj->showAllEmployees();
        else {
            cout <<"NO Access\n";
        }
    }
};

int main() {
    Employee e1(1, "namen");
    Employee e2(2, "adi");
    Employee e3(3, "ad");

    EmployeeDAO* adminobj = new EmployeeDAOProxy("Admin");
    EmployeeDAO* userobj = new EmployeeDAOProxy("User");

    adminobj->createEmployee(&e1);
    adminobj->createEmployee(&e2);
    adminobj->createEmployee(&e3);
    adminobj->showAllEmployees();
    return 0;
}