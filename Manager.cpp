#include "Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Manager::Manager() {
    userid = "" ;
    password = "" ;
    name = "" ;
}

Manager::Manager(string userid, string password, string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
}

bool Manager::authenticate(string userid, string password) {
    Manager* manager = ManagerDBM().SelectManager(userid) ;
    if( manager == NULL ) {
        return false ;
    }
    if( manager -> getPassword() == password ) {
        return true ;
    }
    return false ;
}

string Manager::ManagerLogin() {
    
    string userid, password ;
    Manager manager ;
    
    for( int i = 0 ; i < 3 ; i++ ){
        cout << "-----------------------------------" << endl ;
        cout << "           LOGIN WINDOW            " << endl ;
        cout << "-----------------------------------" << endl ;
        
        cout << "[Input] Enter UserID Option: " ;
        cin >> userid ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        cout << "[Input] Enter Password Option: " ;
        cin >> password ;
        cin.clear(); 
        cin.ignore(10000, '\n');
        
        manager.setUserId(userid) ;
        manager.setPassword(password) ;

        if ( manager.authenticate(userid, password) ) {
            cout << "Login Successful!" << endl ;
            return userid ;
        }
        
        else {
            cout << "Login Failed!" << endl ;
            if( i == 2 ) {
                cout << "Maximum attempts reached!" << endl ;
                return "" ;
            }
        }
    }
}

void Manager::AddUser( int user_type ) {
    string userid, password, name, address, phone ;
    cout << "-----------------------------------" << endl ;
    cout << "             ADD USER              " << endl ;
    cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) cout << "Adding Customer!" << endl ;
    else if (user_type == 1 ) cout << "Adding Employee!" << endl ;
    else if (user_type == 2 ) cout << "Adding Manager!" << endl ;
    cout << "[Input] Enter UserID: " ;
    cin >> userid ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    cout << "[Input] Enter Password: " ;
    cin >> password ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    cout << "[Input] Enter Name: " ;
    cin >> name ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    if(user_type == 0){
        Customer* customer = new Customer(userid, password, name) ;
        customer -> setCustomerRecord(Customer().AvgCustomerRecord()) ;
        CustomerDBM().AddCustomer(customer) ;
    }
    else if(user_type == 1){
        Employee* employee = new Employee(userid, password, name) ;
        employee -> setEmployeeRecord(Employee().AvgEmployeeRecord()) ;
        EmployeeDBM().AddEmployee(employee) ;
    }
    else if(user_type == 2){
        Manager* manager = new Manager(userid, password, name) ;
        ManagerDBM().AddManager(manager) ;
    }
}

void Manager::DeleteUser( int user_type ) {
    string userid ;
    cout << "-----------------------------------" << endl ;
    cout << "            DELETE USER            " << endl ;
    cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) cout << "Deleting Customer!" << endl ;
    else if (user_type == 1 ) cout << "Deleting Employee!" << endl ;
    else if (user_type == 2 ) cout << "Deleting Manager!" << endl ;
    cout << "[Input] Enter UserID: " ;
    cin >> userid ;
    cin.clear(); 
    cin.ignore(10000, '\n'); 
    if( userid == this->getUserId() ){
        cout << "Cannot delete yourself!" << endl ;
        return ;
    }
    if (user_type == 0 ) CustomerDBM().DeleteCustomer(userid) ;
    else if (user_type == 1 ) EmployeeDBM().DeleteEmployee(userid) ;
    else if (user_type == 2 ) ManagerDBM().DeleteManager(userid) ;
    CarDBM().DeleteCarsUserID(userid) ;
}

void Manager::UpdateUser( int user_type ) {
    string userid, password, name , temp ;
    int cars ;
    float Record , dues ;
    cout << "-----------------------------------" << endl ;
    cout << "          UPDATE USER              " << endl ;
    cout << "-----------------------------------" << endl ;
    if (user_type == 0 ) cout << "Updating Customer!" << endl ;
    else if (user_type == 1 ) cout << "Updating Employee!" << endl ;
    else if (user_type == 2 ) cout << "Updating Manager!" << endl ;
    cout << "[Input] Enter UserID: " ;
    cin >> userid ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    if( user_type == 0 && CustomerDBM().SelectCustomer(userid) == NULL ) {
        cout << "UserID does not exist!" << endl ;
        return ;
    }
    if( user_type == 1 && EmployeeDBM().SelectEmployee(userid) == NULL ) {
        cout << "UserID does not exist!" << endl ;
        return ;
    }
    if( user_type == 2 && ManagerDBM().SelectManager(userid) == NULL) {
        cout << "UserID does not exist!" << endl ;
        return ;
    }


    cout << "-----------------------------------" << endl ;
    cout << "      CURRENT USER DETAILS         " << endl ;
    cout << "-----------------------------------" << endl ;
    if( user_type == 0 ) {
        Customer* customer = CustomerDBM().SelectCustomer(userid) ;
        cout << "UserID: " << customer -> getUserId() << endl ;
        cout << "Password: " << customer -> getPassword() << endl ;
        cout << "Name: " << customer -> getName() << endl ;
        cout << "Record: " << customer -> getCustomerRecord() << endl ;
        cout << "Dues: " << customer -> getDues() << endl ;
        cout << "Number of Cars Rented: " << customer -> getNumberOfCarsRented() << endl ;
    }
    else if( user_type == 1 ) {
        Employee* employee = EmployeeDBM().SelectEmployee(userid) ;
        cout << "UserID: " << employee -> getUserId() << endl ;
        cout << "Password: " << employee -> getPassword() << endl ;
        cout << "Name: " << employee -> getName() << endl ;
        cout << "Record: " << employee -> getEmployeeRecord() << endl ;
        cout << "Dues: " << employee -> getDues() << endl ;
        cout << "Number of Cars Rented: " << employee -> getNumberOfCarsRented() << endl ;
    }
    else if( user_type == 2 ) {
        Manager* manager = ManagerDBM().SelectManager(userid) ;
        cout << "UserID: " << manager -> getUserId() << endl ;
        cout << "Password: " << manager -> getPassword() << endl ;
        cout << "Name: " << manager -> getName() << endl ;
    }
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter New Password: " ;
    cin >> password ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    cout << "[Input] Enter New Name: " ;
    cin >> name ;
    cin.clear(); 
    cin.ignore(10000, '\n');
    if(user_type == 0 || user_type == 1){
        cout << "[Input] Enter New User Record: " ;
        cin >> temp ;
        cin.clear();
        cin.ignore(10000, '\n');
        if(!isDecimal(temp)) return ;
        Record = stof(temp) ;
        if(Record < 0 || Record > 100) {
            cout << "Invalid Record!" << endl ;
            return ;
        }
        cout << "[Input] Enter New Dues: " ;
        cin >> temp ;
        cin.clear();
        cin.ignore(10000, '\n');
        if(!isDecimal(temp)) return ;
        dues = stof(temp) ;
        if(dues < 0) {
            cout << "Invalid Data!" << endl ;
            return ;
        }
        cout << "[Input] Enter new Number of Cars Rented: " ;
        cin >> temp ;
        cin.clear();
        cin.ignore(10000, '\n');
        if(!isNumber(temp)) return ;
        cars = stoi(temp) ;
    }
    if( user_type == 0 ){
        Customer* customer = new Customer(userid, password, name, Record, dues) ;
        customer -> setNumberOfCarsRented(cars) ;
        CustomerDBM().UpdateCustomer(customer) ;
        cout << "Customer Updated!" << endl ;
    }
    else if( user_type == 1 ){
        Employee* employee = new Employee(userid, password, name, Record, dues) ;
        employee -> setNumberOfCarsRented(cars) ;
        EmployeeDBM().UpdateEmployee(employee) ;
        cout << "Employee Updated!" << endl ;
    }
    else if( user_type == 3 ){
        Manager* manager = new Manager(userid, password, name) ;
        ManagerDBM().UpdateManager(manager) ;
        cout << "Manager Updated!" << endl ;
    }   
}

void Manager::AddCar() {
    string car_id, car_model , temp ;
    int condition ;
    cout << "-----------------------------------" << endl ;
    cout << "             ADD CAR               " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter Car ID: " ;
    cin >> car_id ;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "[Input] Enter Car Model: " ;
    cin >> car_model ;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "[Input] Enter Car Condition: " ;
    cin >> condition ;
    cin.clear();
    cin.ignore(10000, '\n');
    if(!isNumber(temp)) return ;
    condition = stoi(temp) ;
    cout << "[Input] Enter Rent per day: " ;
    float rent ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');
    if(!isDecimal(temp)) return ;
    rent = stof(temp) ;
    Car* car = new Car(car_id, car_model, condition) ;
    car->setRent(rent) ;
    car->setDueDate("") ;
    car->setRentDate("") ;
    car->setUser("") ;
    CarDBM().AddCar(car) ;
}

void Manager::DeleteCar() {
    string car_id ;
    cout << "-----------------------------------" << endl ;
    cout << "            DELETE CAR             " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter Car ID: " ;
    cin >> car_id ;
    cin.clear();
    cin.ignore(10000, '\n');
    if( CarDBM().SelectCar(car_id) -> getUser() != "" ) {
        cout << "Rented Car can not be deleted!" << endl ;
        return ;
    }        
    CarDBM().DeleteCar(car_id) ;
}

void Manager::UpdateCar() {
    string car_id, car_model, rent, due, user ,temp ;
    int condition ;
    cout << "-----------------------------------" << endl ;
    cout << "            UPDATE CAR             " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter Car ID: " ;
    cin >> car_id ;
    cin.clear();
    cin.ignore(10000, '\n');
    if( CarDBM().SelectCar(car_id) == NULL ) {
        cout << "Car ID does not exist!" << endl ;
        return ;
    }
    if( CarDBM().SelectCar(car_id) -> getUser() != "" ) {
        cout << "Rented Car can not be updated!" << endl ;
        return ;
    }   
    cout << "-----------------------------------" << endl ;
    cout << "       CURRENT CAR DETAILS         " << endl ;
    cout << "-----------------------------------" << endl ;
    Car* car = CarDBM().SelectCar(car_id) ;
    cout << "Car ID: " << car -> getCarId() << endl ;
    cout << "Model: " << car -> getModel() << endl ;
    cout << "Condition: " << car -> getCondition() << endl ;
    cout << "Rent per day in Rs.: " << car -> getRent() << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[Input] Enter New Car Model: " ;
    cin >> car_model ;
    cin.clear();
    cin.ignore(10000, '\n');
    cout << "[Input] Enter New Car Condition: " ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');
    if(!isNumber(temp)) return ;
    condition = stoi(temp) ;
    if(condition <0 || condition > 10) {
        cout << "Invalid Condition!" << endl ;
        return ;
    }
    Car* newcar = new Car(car_id, car_model, condition) ;
    float daypay ;
    cout << "[Input] Enter New Rent per day in Rs.: " ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');
    if(!isDecimal(temp)) return ;
    daypay = stof(temp) ;
    newcar->setRent(daypay) ;
    newcar->setRentDate(car->showRentDate()) ;
    newcar->setDueDate(car->showDueDate()) ;
    newcar->setUser(car->getUser()) ;
    CarDBM().UpdateCar(newcar) ;
    cout << "Car Updated!" << endl ;
}

