#include "Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

CarDBM::CarDBM() {
    vector<string> data = readFromFile("./DB/car.csv", 7) ;
    vector<Car*> cars = {} ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=7){
        Car* car = new Car(data[i], data[i+1], stoi(data[i+2]) ) ;
        car -> setRent(stof(data[i+3])) ;
        car -> setRentDate(data[i+4]) ;
        car -> setDueDate(data[i+5]) ;
        car -> setUser(data[i+6]) ;
        cars.push_back(car) ;
    }
    this -> cars = cars ;
}

CarDBM::~CarDBM() {
    vector<string> data = {} ;
    for(int i = 0 ; i < cars.size() ; i++ ) {
        data.push_back(cars[i] -> getCarId()) ;
        data.push_back(cars[i] -> getModel()) ;
        data.push_back(to_string(cars[i] -> getCondition())) ;
        data.push_back(to_string(cars[i] -> getRent())) ;
        data.push_back(cars[i] -> showRentDate()) ;
        data.push_back(cars[i] -> showDueDate()) ;
        data.push_back(cars[i] -> getUser()) ;
    }
    writeToFile("./DB/car.csv", data, 7) ;
}

void CarDBM::UpdateCar(Car* car) {
    for (int i = 0 ; i < cars.size() ; i++ ) {
        if( cars[i] -> getCarId() == car -> getCarId() ) {
            cars[i] = car ;
            return ;
        }
    }
}

Car* CarDBM::SelectCar(string carid) {
    for(int i = 0 ; i < cars.size() ; i++ ) {
        if( cars[i] -> getCarId() == carid ) {
            return cars[i] ;
        }
    }
    return NULL ;
}

vector<Car*> CarDBM::ListCars() {
    return cars ;
}

void CarDBM::AddCar(Car* car) {
    Car* temp = SelectCar(car -> getCarId()) ;
    if( temp != NULL ) {
        cout << "CarID already exists!" << endl ;
        return ;
    }
    cars.push_back(car) ;
    cout << "Car added successfully!" << endl ;
}

void CarDBM::DeleteCar(string carid) {
    for (int i = 0 ; i < cars.size() ; i++ ) {
        if( cars[i] -> getCarId() == carid ) {
            cars.erase(cars.begin() + i) ;
            cout << "Car deleted successfully!" << endl ;
            return ;
        }
    }
    cout << "CarID does not exist!" << endl ;
}

void CarDBM::DeleteCarsUserID(string userid) {
    for (int i = 0 ; i < cars.size() ; i++ ) {
        if( cars[i] -> getUser() == userid ) {
            cars[i] -> setUser("") ;
            cars[i] -> setRentDate("") ;
            cars[i] -> setDueDate("") ;
        }
    }
}

CustomerDBM::CustomerDBM() {
    vector<string> data = readFromFile("./DB/customer.csv", 6) ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Customer* customer = new Customer(data[i], data[i+1], data[i+2], stof(data[i+3]), stod(data[i+4])) ;
        customer -> setNumberOfCarsRented(stoi(data[i+5])) ;
        customers.push_back(customer) ;
    }
    this -> customers = customers ;
}

CustomerDBM::~CustomerDBM() {
    vector<string> data ;
    for( int i = 0 ; i < customers.size() ; i++ ) {
        data.push_back(customers[i] -> getUserId()) ;
        data.push_back(customers[i] -> getPassword()) ;
        data.push_back(customers[i] -> getName()) ;
        data.push_back(to_string(customers[i] -> getCustomerRecord())) ;
        data.push_back(to_string(customers[i] -> getDues())) ;
        data.push_back(to_string(customers[i] -> getNumberOfCarsRented())) ;
    }
    writeToFile("./DB/customer.csv", data, 6) ;
}

void CustomerDBM::UpdateCustomer(Customer* customer) {
    for(int i = 0 ; i < customers.size() ; i++ ){
        if( customers[i] -> getUserId() == customer -> getUserId() ) {
            customers[i] = customer ;
            return ;
        }
    }
}

Customer* CustomerDBM::SelectCustomer(string userid) {
    for(int i = 0 ; i < customers.size() ; i++ ){
        if( customers[i] -> getUserId() == userid ) {
            return customers[i] ;
        }
    }
    return NULL ;
}

vector<Customer*> CustomerDBM::ListCustomers() {
    return customers ;
}

void CustomerDBM::AddCustomer(Customer* customer) {
    Customer* check = SelectCustomer(customer->getUserId()) ;
    if( check != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    customers.push_back(customer) ;
    cout << "Customer added successfully!" << endl ;
}

void CustomerDBM::DeleteCustomer(string userid) {
    for(int i = 0 ; i < customers.size() ; i++ ){
        if( customers[i] -> getUserId() == userid ) {
            customers.erase(customers.begin() + i) ;
            cout << "Customer deleted successfully!" << endl ;
            return ;
        }
    }
    cout << "UserID does not exist!" << endl ;
}

EmployeeDBM::EmployeeDBM() {
    vector<string> data = readFromFile("./DB/employee.csv", 6) ;
    vector<Employee*> employees ;
    if ( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=6){
        Employee* employee = new Employee(data[i], data[i+1], data[i+2], stof(data[i+3]), stod(data[i+4])) ;
        employee -> setNumberOfCarsRented(stoi(data[i+5])) ;
        employees.push_back(employee) ;
    }
    this -> employees = employees ;
}

EmployeeDBM::~EmployeeDBM() {
    vector<string> data ;
    for( int i = 0 ; i < employees.size() ; i++ ) {
        data.push_back(employees[i] -> getUserId()) ;
        data.push_back(employees[i] -> getPassword()) ;
        data.push_back(employees[i] -> getName()) ;
        data.push_back(to_string(employees[i] -> getEmployeeRecord())) ;
        data.push_back(to_string(employees[i] -> getDues())) ;
        data.push_back(to_string(employees[i] -> getNumberOfCarsRented())) ;
    }
    writeToFile("./DB/employee.csv", data, 6) ;
}

void EmployeeDBM::UpdateEmployee(Employee* employee){
    for( int i = 0 ; i < employees.size() ; i++ ) {
        if( employees[i] -> getUserId() == employee -> getUserId() ) {
            employees[i] = employee ;
            return ;
        }
    }
}

Employee* EmployeeDBM::SelectEmployee(string userid) {
    for(int i = 0 ; i < employees.size() ; i+=6){
        if( employees[i] -> getUserId() == userid ) {
            return employees[i] ;
        }
    }
    return NULL ;
}

vector<Employee*> EmployeeDBM::ListEmployees() {
    return employees ;
}

void EmployeeDBM::AddEmployee(Employee* employee) {
    Employee* check = SelectEmployee(employee->getUserId()) ;
    if( check != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    employees.push_back(employee) ;
    cout << "Employee Added!" << endl ;
}

void EmployeeDBM::DeleteEmployee(string userid) {
    for( int i = 0 ; i < employees.size() ; i++ ) {
        if( employees[i] -> getUserId() == userid ) {
            employees.erase(employees.begin() + i) ;
            cout << "Employee Deleted!" << endl ;
            return ;
        }
    }
    cout << "Employee not found!" << endl ;
}

ManagerDBM::ManagerDBM() {
    vector<string> data = readFromFile("./DB/manager.csv", 3) ;
    vector<Manager*> managers = {} ;
    if( data.size() == 1 ) return ;
    for(int i = 0 ; i < data.size() ; i+=3){
        Manager* manager = new Manager(data[i], data[i+1], data[i+2]) ;
        managers.push_back(manager) ;
    }
    this -> managers = managers ;
}

ManagerDBM::~ManagerDBM() {
    vector<string> data = {} ;
    for(int i = 0 ; i < managers.size() ; i++ ) {
        data.push_back(managers[i] -> getUserId()) ;
        data.push_back(managers[i] -> getPassword()) ;
        data.push_back(managers[i] -> getName()) ;
    }
    writeToFile("./DB/manager.csv", data, 3) ;
}

void ManagerDBM::UpdateManager(Manager* manager) {
    for (int i = 0 ; i < managers.size() ; i++ ) {
        if( managers[i] -> getUserId() == manager -> getUserId() ) {
            managers[i] = manager ;
            return ;
        }
    }
}

Manager* ManagerDBM::SelectManager(string userid) {
    for(int i = 0 ; i < managers.size() ; i++ ) {
        if( managers[i] -> getUserId() == userid ) {
            return managers[i] ;
        }
    }
    return NULL ;
}

vector<Manager*> ManagerDBM::ListManagers() {
    return managers ;
}

void ManagerDBM::AddManager(Manager* manager) {
    Manager* temp = SelectManager(manager -> getUserId()) ;
    if( temp != NULL ) {
        cout << "UserID already exists!" << endl ;
        return ;
    }
    managers.push_back(manager) ;
    cout << "Manager Added!" << endl ;
}

void ManagerDBM::DeleteManager(string userid) {
    for(int i = 0 ; i < managers.size() ; i++ ) {
        if( managers[i] -> getUserId() == userid ) {
            managers.erase(managers.begin() + i) ;
            cout << "Manager Deleted!" << endl ;
            return ;
        }
    }
    cout << "UserID does not exist!" << endl ;
}
