#include "Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;

Customer::Customer(string userid, string password, string name, float customer_record, double dues) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> customer_record = customer_record ;
    this -> dues = dues ;
    this -> num_cars_rented = 0 ;
}

Customer::Customer(string userid, string password, string name) {
    this -> userid = userid ;
    this -> password = password ;
    this -> name = name ;
    this -> customer_record = 0 ;
    this -> dues = 0 ;
    this -> num_cars_rented = 0 ;
}

float Customer::CalculateCustomerRecord( int initial_condition , int final_condition , int days ) {
    float record = this->getCustomerRecord() ;
    record -= (initial_condition - final_condition) * 0.5 ;
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


int Customer::getNumberOfCarsRented() {
    return num_cars_rented ;
}

void Customer::setDues(double dues) {
    this -> dues = dues ;
}

void Customer::setCustomerRecord(float customer_record) {
    this -> customer_record = customer_record ;
}

float Customer::getCustomerRecord() {
    return customer_record ;
}

double Customer::getDues() {
    return dues ;
}

string User::getUserId() {
    return userid ;
}

string User::getName() {
    return name ;
}

float Customer::AvgCustomerRecord() {
    vector<Customer*> customers = CustomerDBM().ListCustomers() ;
    float sum = 0 ;
    if(customers.size() == 0) return 80 ;
    for( int i = 0 ; i < customers.size() ; i++ ) {
        sum += customers[i] -> getCustomerRecord() ;
    }
    return sum / customers.size() ;
}

Customer::Customer() {
    userid = "" ;
    password = "" ;
    name = "" ;
    customer_record = 0 ;
    dues = 0 ;
    num_cars_rented = 0 ;
}

void User::setUserId(string userid) {
    this -> userid = userid ;
}

void User::setPassword(string password) {
    this -> password = password ;
}

string User::getPassword() {
    return password ;
}

bool Customer::authenticate(string userid, string password) {
    Customer* customer = CustomerDBM().SelectCustomer(userid) ;
    if( customer == NULL ) {
        return false ;
    }
    if( customer -> getPassword() == password ) {
        return true ;
    }
    return false ;
}

void Customer::setNumberOfCarsRented(int num_cars_rented) {
    this -> num_cars_rented = num_cars_rented ;
}

int Customer::MaxCars() {
    return (customer_record/30)+1 ;
}

string Customer::CustomerLogin() {
    
    string userid, password ;
    Customer customer ;
    
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
        
        customer.setUserId(userid) ;
        customer.setPassword(password) ;

        if ( customer.authenticate(userid, password) ) {
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

void Customer::ReturnRequest() {
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

    string temp ;
    int condition ;
    int flag = 0 ;
    for( int i = 0 ; i < 5 ; i++ ) {
        cout << "[Input] current condition of the car (0-10): " ;
        cin >> temp ;
        cin.clear();
        cin.ignore(10000, '\n');
        if(!isNumber(temp)) {
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
        this -> setCustomerRecord(this -> CalculateCustomerRecord( carcheck->getCondition() , condition , days ) ) ;
        CustomerDBM().UpdateCustomer(this) ;
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
        this -> setCustomerRecord(this -> CalculateCustomerRecord( carcheck->getCondition() , condition , 0 ) ) ;
        CustomerDBM().UpdateCustomer(this) ;
        carcheck -> setUser("") ;
        carcheck -> setRentDate("") ;
        carcheck -> setDueDate("") ;
        carcheck -> setCondition(condition) ;
        CarDBM().UpdateCar(carcheck) ;
        cout << "Car returned successfully!" << endl ;
        cout << "May you have a pleasant day.. :) " << endl ;
    }        
}

void Customer::clearDues() {
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
    string temp ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');

    if(!isDecimal(temp)) return ;
    double pay = stod(temp) ;

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
    CustomerDBM().UpdateCustomer(this) ;
    cout << "Payment Successful!" << endl ;
    cout << "May you have a pleasant day.. :) " << endl ;
}

void Customer::DisplayAllCustomers() {
    int flag = 0 ;
    vector<Customer*> customers = CustomerDBM().ListCustomers() ;
    cout << "-----------------------------------" << endl ;
    cout << "          ALL CUSTOMERS             " << endl ;
    cout << "-----------------------------------" << endl ;
    for( int i = 0 ; i < customers.size() ; i++ ) {
        flag ++ ;
        cout << "UserID: " << customers[i] -> getUserId() << endl ;
        cout << "Name: " << customers[i] -> getName() << endl ;
        cout << "Customer Record: " << customers[i] -> getCustomerRecord() << endl ;
        cout << "Dues: " << customers[i] -> getDues() << endl ;
        cout << "Number of Cars Rented: " << customers[i] -> getNumberOfCarsRented() << endl ;
        cout << "-----------------------------------" << endl ;
    }
    if( flag == 0 ) {
        cout << "No Customers found!" << endl ;
    }
    cout << "-----------------------------------" << endl ;
}
