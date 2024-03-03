#include "DB_Manager.cpp"
#include "Customer.cpp"
#include "Employee.cpp"
#include "Car.cpp"
#include "Manager.cpp"
#include <fstream>
#include <iostream>
using namespace std ;

// A function to count the number of leap years to show correct number of days between two given dates
int countLeapYears(Date d) { 
    int years = d.y; 
    if (d.m <= 2) 
        years--;  
    return (years/4)  - (years/100) + (years/400) ; 
}

// A function to check if the input is a valid decimal number.. used to validate user input
bool isDecimal(string temp) {
    int flag = 0 ;
    for ( int i = 0 ; i < temp.length() ; i++ ) {
        if ( isdigit(temp[i]) == false && temp[i] != '.' ) {
            cout << "Invalid input!" << endl ;
            cout << "Process Cancelled!" << endl ;
            return false ;
        }
        if ( temp[i] == '.' ) {
            flag ++ ;
            if(flag>1) {
                cout << "Invalid input!" << endl ;
                cout << "Process Cancelled!" << endl ;
                return false;
            }
        }
    }
    return true ;
}

// A function to check if the input is a valid number.. used to validate user input
bool isNumber(string temp) {
    for ( int i = 0 ; i < temp.length() ; i++ ) {
        if ( isdigit(temp[i]) == false ) {
            cout << "Invalid input!" << endl ;
            cout << "Process Cancelled!" << endl ;
            return false ;
        }
    }
    return true ;
}

// Next two function acts an interface between the program and the database

// It reads data from a file and returns a vector of strings depending on number of columns
vector<string> readFromFile(string filename, int columns) {
    fstream file ;
    file.open(filename, ios::in) ;
    if( file.is_open() ) {
        string line ;
        vector<string> data ;
        int flag = 0 ;
        while( getline(file, line, ',') ) {
            data.push_back(line) ;
            flag ++ ;
            if(flag == columns){
                getline(file, line) ;
                flag = 0 ;
            }
        }
        file.close() ;
        return data ;
    }
    else {
        cout << "Error: File not found!" << endl ;
        return {} ;
    }
}
// This function all acts as an interface between the program and the database... writing a vector of strings to a file
void writeToFile(string filename, vector<string> data, int columns) {
    fstream file ;
    file.open(filename, ios::out) ;
    if( file.is_open() ) {
        for(int i = 0; i < data.size(); i++) {
            file << data[i] ;
            if( (i+1) % columns == 0 ) {
                file << "," << endl ;
            }
            else {
                file << "," ;
            }
        }
        file.close() ;
    }
    else {
        cout << "Error: File not found!" << endl ;
    }
}

// To calculate the number of days between two given dates  
// Used in the customer menu to calculate the number of days between the due date and today's date
int DaysDiff(string due_date, string today) { 
    int monthDays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    Date dt1, dt2 ; stringstream ss(due_date) ;
    string temp ; getline(ss, temp, '-') ; dt1.d = stoi(temp) ;
    getline(ss, temp, '-') ; dt1.m = stoi(temp) ;
    getline(ss, temp, '-') ; dt1.y = stoi(temp) ;
    stringstream ss2(today) ;
    getline(ss2, temp, '-') ; dt2.d = stoi(temp) ;
    getline(ss2, temp, '-') ; dt2.m = stoi(temp) ;
    getline(ss2, temp, '-') ; dt2.y = stoi(temp) ;
    long int n1 = dt1.y * 365 + dt1.d; 
    for (int i = 0; i < dt1.m - 1; i++) n1 += monthDays[i]; 
    n1 += countLeapYears(dt1); 
    long int n2 = dt2.y * 365 + dt2.d; 
    for (int i = 0; i < dt2.m - 1; i++) n2 += monthDays[i];
    n2 += countLeapYears(dt2); 
    return (n2 - n1); 
}

// A function to ask user to confirm his/her action
bool confirm() {
    cout << "[Input] Confirm ? (Y/N): " ;
    char confirm ;
    cin >> confirm ;
    cin.clear();
    cin.ignore(10000, '\n');
    if( confirm == 'N' || confirm == 'n' ) {
        cout << "Process Cancelled!" << endl ;
        return false ;
    }
    else if( confirm != 'Y' && confirm != 'y' ) {
        cout << "Invalid input!" << endl ;
        cout << "Process Cancelled!" << endl ;
        return false ;
    }
    return true ;
}

void Customer_Menu() {
    string userid  = Customer().CustomerLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 6 ) {   
        Customer* customer = CustomerDBM().SelectCustomer(userid) ;    
        cout << "-----------------------------------" << endl ;
        cout << "          CUSTOMER WINDOW          " << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "||  1 - VIEW RENTED CARS         ||" << endl ;
        cout << "||  2 - RENT A CAR               ||" << endl ;
        cout << "||  3 - RETURN A CAR             ||" << endl ;
        cout << "||  4 - CLEAR DUES               ||" << endl ;
        cout << "||  5 - VIEW ALL AVAILABLE CARS  ||" << endl ;
        cout << "||  6 - LOGOUT                   ||" << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Car().DisplayRentedCars(userid) ;
        else if ( option == 2 ) {
            if( Car().DisplayAvailableCars() == 0 ) continue ;
            if( customer->MaxCars() <= customer->getNumberOfCarsRented()  ) {
                cout << "You have reached the maximum limit of cars rented!" << endl ;
                continue ;
            }
            string carid ;
            cout << "-----------------------------------" << endl ;
            cout << "            RENT A CAR             " << endl ;
            cout << "-----------------------------------" << endl ;
            cout << "[Input] Enter CarID from above available cars: " ;
            cin >> carid ;
            cin.clear(); 
            cin.ignore(10000, '\n');
            Car *carcheck = CarDBM().SelectCar(carid) ; 
            if( carcheck == nullptr ) {
                cout << "No car with provided CarID available for rent." << endl ;
                continue ;
            }
            if( carcheck -> isRented() ) {
                cout << "Car already rented!" << endl ;
                continue ;
            }
            carcheck -> RentCar(userid,0) ;
        }
        else if( option == 3 ) customer->ReturnRequest() ;
        else if( option == 4 ) customer->clearDues() ;
        else if( option == 5 ) Car().DisplayAvailableCars() ;
        else if( option == 6 ) cout << "Logging out" << endl ;
        else cout << "Invalid input!" << endl ;
    }
}

void Employee_Menu(){
    string userid  = Employee().EmployeeLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 6 ) {   
        Employee* employee = EmployeeDBM().SelectEmployee(userid) ;    
        cout << "-----------------------------------" << endl ;
        cout << "          EMPLOYEE WINDOW          " << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "||  1 - VIEW RENTED CARS         ||" << endl ;
        cout << "||  2 - RENT A CAR               ||" << endl ;
        cout << "||  3 - RETURN A CAR             ||" << endl ;
        cout << "||  4 - CLEAR DUES               ||" << endl ;
        cout << "||  5 - VIEW ALL AVAILABLE CARS  ||" << endl ;
        cout << "||  6 - LOGOUT                   ||" << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Car().DisplayRentedCars(userid) ;
        else if ( option == 2 ) {
            if( Car().DisplayAvailableCars() == 0 ) continue ;
            if( employee->MaxCars() <= employee->getNumberOfCarsRented()  ) {
                cout << "You have reached the maximum limit of cars rented!" << endl ;
                continue ;
            }
            string carid ;
            cout << "-----------------------------------" << endl ;
            cout << "            RENT A CAR             " << endl ;
            cout << "-----------------------------------" << endl ;
            cout << "[Input] Enter CarID from above available cars: " ;
            cin >> carid ;
            cin.clear(); 
            cin.ignore(10000, '\n');
            Car *carcheck = CarDBM().SelectCar(carid) ; 
            if( carcheck == nullptr ) {
                cout << "No car with provided CarID available for rent." << endl ;
                continue ;
            }
            if( carcheck -> isRented() ) {
                cout << "Car already rented!" << endl ;
                continue ;
            }
            carcheck -> RentCar(userid,1) ;
        }
        else if( option == 3 ) employee->ReturnRequest() ;
        else if( option == 4 ) employee->clearDues() ;
        else if( option == 5 ) Car().DisplayAvailableCars() ;
        else if( option == 6 ) cout << "Logging out" << endl ;
        else cout << "Invalid input!" << endl ;
    }
} 

void Manager_Menu() {
    string userid  = Manager().ManagerLogin() ;
    if( userid == "" ) return ;
    int option = 0 ;
    while( option != 17 ) {  
        Manager* manager = ManagerDBM().SelectManager(userid) ;      
        cout << "-----------------------------------" << endl ;
        cout << "          MANAGER WINDOW           " << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "||  1 - DISPLAY AVAILABLE CARS   ||" << endl ;
        cout << "||  2 - DISPLAY ALL RENTED CARS  ||" << endl ;
        cout << "||  3 - DISPLAY ALL CUSTOMERS    ||" << endl ;
        cout << "||  4 - DISPLAY ALL EMPLOYEES    ||" << endl ;
        cout << "||  5 - ADD CUSTOMER             ||" << endl ;
        cout << "||  6 - DELETE CUSTOMER          ||" << endl ;
        cout << "||  7 - UPDATE CUSTOMER          ||" << endl ;
        cout << "||  8 - ADD EMPLOYEE             ||" << endl ;
        cout << "||  9 - DELETE EMPLOYEE          ||" << endl ;
        cout << "|| 10 - UPDATE EMPLOYEE          ||" << endl ;
        cout << "|| 11 - ADD MANAGER              ||" << endl ;
        cout << "|| 12 - DELETE MANAGER           ||" << endl ;
        cout << "|| 13 - UPDATE MANAGER           ||" << endl ;
        cout << "|| 14 - ADD CAR                  ||" << endl ;
        cout << "|| 15 - DELETE CAR               ||" << endl ;
        cout << "|| 16 - UPDATE CAR               ||" << endl ;
        cout << "|| 17 - LOGOUT                   ||" << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "[Input] Enter Option: " ;
        cin >> option ;
        cin.clear(); 
        cin.ignore(10000, '\n'); 
        if( option == 1 ) Car().DisplayAvailableCars() ;
        else if( option == 2 ) Car().DisplayAllRentedCars() ;
        else if( option == 3 ) Customer().DisplayAllCustomers() ;
        else if( option == 4 ) Employee().DisplayAllEmployees() ;
        else if( option == 5 ) manager->AddUser(0) ;
        else if( option == 6 ) manager->DeleteUser(0) ;
        else if( option == 7 ) manager->UpdateUser(0) ;
        else if( option == 8 ) manager->AddUser(1) ;
        else if( option == 9 ) manager->DeleteUser(1) ;
        else if( option == 10 ) manager->UpdateUser(1) ;
        else if( option == 11 ) manager->AddUser(2) ;
        else if( option == 12 ) manager->DeleteUser(2) ;
        else if( option == 13 ) manager->UpdateUser(2) ;
        else if( option == 14 ) manager->AddCar() ;
        else if( option == 15 ) manager->DeleteCar() ;
        else if( option == 16 ) manager->UpdateCar() ;
        else if( option == 17 ){
            cout << "Logging out!" << endl ;
            return ;
        }
        else cout << "Invalid Option!" << endl ;
    }
}


// First Screen to display.. options to login as a customer, employee or manager
void LoginMenu() {
    int option = 0 ;
    while ( option != 4 ) {
        system("cls") ;
        cout << "===================================" << endl ;
	    cout << "||                               ||" << endl ;
	    cout << "||       CAR RENTAL SYSTEM       ||" << endl ;
	    cout << "||                               ||" << endl ;
	    cout << "===================================" << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "           LOGIN OPTIONS           " << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "||   1 - CUSTOMER                ||" << endl ;
        cout << "||   2 - EMPLOYEE                ||" << endl ;
        cout << "||   3 - MANAGER                 ||" << endl ;
        cout << "||   4 - EXIT                    ||" << endl ;
        cout << "-----------------------------------" << endl ;
        cout << "[Input] Enter Login Option: ";	
        cin >> option;
        cin.clear(); 
        cin.ignore(10000, '\n');

        if ( option == 1 ) {
            system("cls") ;
            Customer_Menu() ;
        }
        else if( option == 2 ) {
            system("cls") ;
            Employee_Menu() ;
        }
        else if( option == 3 ) {
            system("cls") ;
            Manager_Menu() ;
        }
        else if( option == 4 ) {
            cout << "Exiting" << endl ;
            cout << "Thank you for using our service!" << endl ;
        }
        else {
            cout << "Invalid option!" << endl ;
        }
    }
}

int main(){
    LoginMenu() ;
    return 0 ; 
}
