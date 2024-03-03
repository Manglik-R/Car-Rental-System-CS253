#include "Model.hpp"
#include <iostream>
#include <ctime>
#include <sstream>

using namespace std ;


double Car::CalculateDues(int days) {
    double price = 0 ;
    price = days*(this->getRent()) ;
    return price ;
}

double Car::CalculateFine(int days) {
    double fine = 0 ;
    fine = 1000 + days*(this->getRent()) ;
    return fine ;
}

Car::Car(){
    car_id = "" ;
    model = "" ;
    user = "" ;
}

Car::Car(string car_id, string model, int condition) {
    this -> car_id = car_id ;
    this -> model = model ;
    this -> condition = condition ;
}

void Car::DisplayRentedCars(string userid) {
    int flag = 0 ;
    vector<Car*> CarList = CarDBM().ListCars() ;
    cout << "-----------------------------------" << endl ;
    cout << "            CARS RENTED            " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < CarList.size() ; i++ ) {
        if( CarList[i] -> getUser() == userid ) {
            flag = 1 ;
            cout << "CarID: " << CarList[i] -> getCarId() << endl ;
            cout << "Model: " << CarList[i] -> getModel() << endl ;
            cout << "Rent Date : " << CarList[i]->showRentDate() << endl;
            cout << "Due Date : " << CarList[i] -> showDueDate() << endl;
            cout << endl ;            
        }
    }
    if( flag == 0 ) {
        cout << "No cars rented!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}

bool Car::DisplayAvailableCars() {
    int flag = 0 ;
    vector<Car*> CarList = CarDBM().ListCars() ;
    cout << "-----------------------------------" << endl ;
    cout << "          CARS AVAILABLE           " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < CarList.size() ; i++ ) {
        if( !CarList[i] -> isRented() ) {
            flag ++ ;
            cout << "CarID: " << CarList[i] -> getCarId() << endl ;
            cout << "Model: " << CarList[i] -> getModel() << endl ;
            cout << "Condition: " << CarList[i] -> getCondition() << endl ;
            cout << "Rent per day: " << CarList[i] -> getRent() << endl ;
            cout << endl ;
        }
    }
    if( flag == 0 ) {
        cout << "No cars available for rent!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
    return flag ;
}

void Car::setDueDate(string due_date) {
    this -> due_date = due_date ;
}

void Car::setRentDate(string rent_date) {
    this -> rent_date = rent_date ;
}

void Car::setUser(string user) {
    this -> user = user ;
}

void Car::setCondition(int condition) {
    this -> condition = condition ;
}

void Car::setModel(string model) {
    this -> model = model ;
}

void Car::setCarId(string car_id) {
    this -> car_id = car_id ;
}

string Car::getUser() {
    return user ;
}

string Car::getCarId() {
    return car_id ;
}

string Car::getModel() {
    return model ;
}

void Car::setRent(float rent) {
    this -> rent = rent ;
}

float Car::getRent() {
    return rent ;
}

int Car::getCondition() {
    return condition ;
}

string Car::showRentDate() {
    return rent_date ;
}

string Car::showDueDate() {
    return due_date ;
}

bool Car::isRented() {
    if( user == "" ) {
        return false ;
    }
    return true ;
}

bool Car::RentCar(string userid, int user_type) {

    cout << "[Input] Enter Numbers of days for which you want to rent (Can not be more than 200 days): " ;
    string temp ;
    cin >> temp ;
    cin.clear();
    cin.ignore(10000, '\n');

    if(!isNumber(temp)) {
        return false ;
    }
    int days = stoi(temp) ;
    if( days > 200 || days < 1 ) {
        cout << "Invalid Number of days Input !" << endl ;
        return false ;
    }

    time_t now = time(0) + 19800 ; 
    tm *ltm = localtime(&now);
    string rent_date = to_string(ltm->tm_mday) + "-" + to_string(1 + ltm->tm_mon) + "-" + to_string(1900 + ltm->tm_year) ;

    time_t now2 = time(0) + 19800 + days*24*60*60 ;
    tm *ltm2 = localtime(&now2);
    string due_date = to_string(ltm2->tm_mday) + "-" + to_string(1 + ltm2->tm_mon) + "-" + to_string(1900 + ltm2->tm_year) ;

    double price = this->CalculateDues(days) ;
    if(user_type == 1) price = price*0.85 ;

    cout << "-----------------------------------" << endl ;
    cout << "[NOTE] Total Amount Charged would be: Rs. " << price << endl ;
    cout << "-----------------------------------" << endl ;
    if(!confirm()) return false ;    
    this-> rent_date = rent_date ;
    this -> due_date = due_date ;
    this -> user = userid ;
    
    CarDBM().UpdateCar(this) ;

    if( user_type == 0 ) {
        Customer* customer = CustomerDBM().SelectCustomer(userid) ;
        customer -> setNumberOfCarsRented(customer -> getNumberOfCarsRented() + 1) ;
        customer -> setDues(customer -> getDues() + price) ;
        CustomerDBM().UpdateCustomer(customer) ;
    }
    else if( user_type == 1 ) {
        Employee* employee = EmployeeDBM().SelectEmployee(userid) ;
        employee -> setNumberOfCarsRented(employee -> getNumberOfCarsRented() + 1) ;
        employee -> setDues(employee -> getDues() + price) ;
        EmployeeDBM().UpdateEmployee(employee) ;
    }
    cout << "Car rented successfully!" << endl ;
    cout << "May you have a pleasant day.. :) " << endl ;
    return true ;
}

void Car::DisplayAllRentedCars() {
    int flag = 0 ;
    vector<Car*> CarList = CarDBM().ListCars() ;
    cout << "-----------------------------------" << endl ;
    cout << "        ALL RENTED CARS            " << endl ;
    cout << "-----------------------------------" << endl ;
    cout <<  endl ;
    for( int i = 0 ; i < CarList.size() ; i++ ) {
        if( CarList[i] -> isRented() ) {
            flag ++ ;
            cout << "CarID : " << CarList[i] -> getCarId() << endl ;
            cout << "Model : " << CarList[i] -> getModel() << endl ;
            cout << "Condition when rented : " << CarList[i] -> getCondition() << endl ;
            cout << "Rent Date : " << CarList[i]->showRentDate() << endl;
            cout << "Due Date : " << CarList[i] -> showDueDate() << endl;
            cout << "UserID of who rented : " << CarList[i] -> getUser() << endl ;
            cout << "Rent per day : " << CarList[i] -> getRent() << endl ;
            cout << endl ;
        }
    }
    if( flag == 0 ) {
        cout << "No cars rented!" << endl ;
        cout << endl ;
    }
    cout << "-----------------------------------" << endl ;
}

