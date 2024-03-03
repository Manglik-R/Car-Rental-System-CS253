#include "Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Employee::Employee(string userid, string password, string name, float employee_record, double dues) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> employee_record = employee_record ;
    this -> dues = dues ;
    this -> num_cars_rented = 0 ;
}

Employee::Employee(string userid, string password, string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> employee_record = 0 ;
    this -> dues = 0 ;
    this -> num_cars_rented = 0 ;
}

Employee::Employee() {
    this -> userid = "" ;
    this -> password = "" ;
    this -> name = "" ;
    this -> employee_record = 0 ;
    this -> dues = 0 ;
    this -> num_cars_rented = 0 ;
}

float Employee::CalculateEmployeeRecord( int initial_condition , int final_condition , int days ) {
    float record = this->getEmployeeRecord() ;
    record += (initial_condition - final_condition) * 0.5 ;
    record -= days * 0.5 ;
    record += 1 ;
    if( record < 0 ) {
        record = 0 ;
    }
    if( record > 100 ) {
        record = 100 ;
    }
    return record ;
}

float Employee::getEmployeeRecord() {
    return employee_record ;
}

int Employee::getNumberOfCarsRented() {
    return num_cars_rented ;
}

void Employee::setDues(double dues) {
    this -> dues = dues ;
}

void Employee::setEmployeeRecord(float employee_record) {
    this -> employee_record = employee_record ;
}

void Employee::setNumberOfCarsRented(int num_cars_rented) {
    this -> num_cars_rented = num_cars_rented ;
}

double Employee::getDues() {
    return dues ;
}

float Employee::AvgEmployeeRecord() {
    vector<Employee*> employees = EmployeeDBM().ListEmployees() ;
    float sum = 0 ;
    if( employees.size() == 0 ) return 80 ;
    for( int i = 0 ; i < employees.size() ; i++ ) {
        sum += employees[i] -> getEmployeeRecord() ;
    }
    return sum / employees.size() ;
}

bool Employee::authenticate(string userid, string password) {
    Employee *employee = EmployeeDBM().SelectEmployee(userid) ;
    if( employee == NULL ) {
        return false ;
    }
    if( employee -> password == password ) {
        return true ;
    }
    return false ;
}

int Employee::MaxCars() {
    return (employee_record/30)+1 ;
}

string Employee::EmployeeLogin() {
    string userid, password ;
    Employee employee ;
    
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
        
        employee.setUserId(userid) ;
        employee.setPassword(password) ;

        if ( employee.authenticate(userid, password) ) {
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

void Employee::DisplayAllEmployees(){
    int flag = 0 ;
    vector<Employee*> employees = EmployeeDBM().ListEmployees() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL EMPLOYEES             " << endl ;
    cout << "-----------------------------------" << endl ;
    if( employees.size()==0 ){
        cout << "No Employees found" << endl ;
        return ;
    }
    for( int i = 0 ; i < employees.size() ; i++ ) {
        flag++ ;
        cout << "UserID: " << employees[i] -> getUserId() << endl ;
        cout << "Name: " << employees[i] -> getName() << endl ;
        cout << "Employee Record: " << employees[i] -> getEmployeeRecord() << endl ;
        cout << "Dues: " << employees[i] -> getDues() << endl ;
        cout << "Number of Cars Rented: " << employees[i] -> getNumberOfCarsRented() << endl ;
        cout << "-----------------------------------" << endl ;
    }
    if( flag == 0 ) {
        cout << "No Employee available!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
} 

void Employee::ReturnRequest() {
    cout << "-----------------------------------" << endl ;
    cout << "          RETURN A CAR             " << endl ;
    cout << "-----------------------------------" << endl ;
    Car().DisplayRentedCars(userid) ;

    if( this -> getNumberOfCarsRented() == 0 ) return ;

    cout << "[Input] Enter CarID of car to be returned: " ;
    string carid ;
    cin >> carid ;
    cin.clear();
    cin.ignore(10000, '\n');

    Car *carcheck = CarDBM().SelectCar(carid) ; 

    if( carcheck == nullptr ) {
        cout << "No car with provided CarID available for you to return." << endl ;
        return ;
    }
    if( carcheck -> getUser() != userid ) {
        cout << "No car with provided CarID available for you to return." << endl ;
        return ;
    }
        
    time_t now = time(0) ;
    tm *ltm2 = localtime(&now);
    string today = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;

    int condition ;
    string temp ;
    int flag = 0 ;
    for( int i = 0 ; i < 5 ; i++ ) {
        cout << "[Input] current condition of the car (0-10): " ;
        cin >> temp ;
        cin.clear();
        cin.ignore(10000, '\n');
        if( !isNumber(temp) ) {
            flag++ ;
            continue ;
        }
        condition = stoi(temp) ;
        if( condition >= 0 && condition <= 10 ) {
            break ;
        }
        else {
            cout << "Invalid input!" << endl ;
            flag++ ;
        }
    }
    if(flag == 5) {
        cout << "Car Return Request Failed" << endl ;
        return ;
    }
    int days = DaysDiff(carcheck -> showDueDate(), today) ;
    if( days > 0 ) {
        float fine = carcheck->CalculateFine(days) ;
        cout << "Car returned late!" << endl ;
        cout << "Fine to be paid: Rs. " << fine << endl ;
        cout << "-----------------------------------" << endl ;
        if(!confirm()) return ;
        this -> setDues(this -> getDues() + fine) ;
        this -> setNumberOfCarsRented(this -> getNumberOfCarsRented() - 1) ;
        this -> setEmployeeRecord(this -> CalculateEmployeeRecord( carcheck->getCondition() , condition , days ) ) ;
        EmployeeDBM().UpdateEmployee(this) ;
        carcheck -> setUser("") ;
        carcheck -> setRentDate("") ;
        carcheck -> setDueDate("") ;
        carcheck -> setCondition(condition) ;
        CarDBM().UpdateCar(carcheck) ;
        cout << "Car returned successfully!" << endl ;
        cout << "May you have a pleasant day.. :) " << endl ;
    }

    else {
        cout << "-----------------------------------" << endl ;
        if(!confirm()) return ;
        this -> setNumberOfCarsRented(this -> getNumberOfCarsRented() - 1) ;
        this -> setEmployeeRecord(this -> CalculateEmployeeRecord( carcheck->getCondition() , condition , 0 ) ) ;
        EmployeeDBM().UpdateEmployee(this) ;
        carcheck -> setUser("") ;
        carcheck -> setRentDate("") ;
        carcheck -> setDueDate("") ;
        carcheck -> setCondition(condition) ;
        CarDBM().UpdateCar(carcheck) ;
        cout << "Car returned successfully!" << endl ;
        cout << "May you have a pleasant day.. :) " << endl ;
    }        
}

void Employee::clearDues() {
    cout << "-----------------------------------" << endl ;
    cout << "            CLEAR DUES             " << endl ;
    cout << "-----------------------------------" << endl ;
    cout << "[NOTE] Your Current Dues to be paid: Rs. " << this -> getDues() << endl ;
    cout << "-----------------------------------" << endl ;
    if( this -> getDues() == 0 ) {
        cout << "No Dues to be paid!" << endl ;
        return ;
    }
    cout << "[Input] How much would you like to pay? (Rs.): " ;
    double pay ;
    string temp ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');
    if( !isDecimal(temp) ) {
        return ;
    }
    pay = stod(temp) ;
    if( pay > this -> getDues() ) {
        cout << "Invalid input! Amount more than Dues." << endl ;
        cout << "Payment Cancelled!" << endl ;
        return ;
    }
    if( pay < 0 ) {
        cout << "Invalid input! Amount can not be negative" << endl ;
        cout << "Payment Cancelled!" << endl ;
        return ;
    }
    if(!confirm()) return ;
    this -> setDues(this -> getDues() - pay) ;
    EmployeeDBM().UpdateEmployee(this) ;
    cout << "Payment Successful!" << endl ;
    cout << "May you have a pleasant day.. :) " << endl ;
}
