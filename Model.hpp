#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class User {
	protected:
		std::string userid ;
		std::string password ;
		std::string name ;
	public:
		void setUserId(std::string userid) ;
		void setPassword(std::string password) ;
		void setName(std::string name) ;
		std::string getUserId() ;
		std::string getPassword() ;
		std::string getName() ;		        
} ;

class Car {
	private :
		std::string car_id ;
		std::string model ;
		int condition ;
		std::string rent_date ;
		std::string due_date ;
		std::string user ;
		float rent ;
	public :
		Car(std::string car_id, std::string model, int condition) ;
		Car() ;
		void setCarId(std::string car_id) ;
		void setModel(std::string model) ;
		void setCondition(int condition) ;
		void setRentDate(std::string rent_date) ;
		void setDueDate(std::string due_date) ;
		void setUser(std::string) ;
		void setRent(float rent) ;
		bool isRented() ;
		double CalculateFine( int days ) ;
		double CalculateDues( int days ) ;
		std::string getCarId() ;
		std::string getModel() ;
		int getCondition() ;
		std::string getUser() ;
		float getRent() ;
		std::string showRentDate() ;
		std::string showDueDate() ;
		bool RentCar(std::string userid , int user_type) ;
		void DisplayRentedCars(std::string userid) ;
		bool DisplayAvailableCars() ;
		void DisplayAllRentedCars() ;
} ;

class Customer : public User {
	private :
		float customer_record ;
		double dues ;
		int num_cars_rented ;
	public :
		bool authenticate(std::string , std::string) ;
		Customer(std::string userid, std::string password, std::string name) ;
		Customer(std::string userid, std::string password, std::string name, float customer_record,  double dues) ;
		Customer() ;
		float getCustomerRecord() ;
		double getDues() ;
		int getNumberOfCarsRented() ;
		void setCustomerRecord(float customer_record) ;
		void setDues(double dues) ;
		void setNumberOfCarsRented(int num_cars_rented) ;
		int MaxCars() ;
		std::string CustomerLogin() ;
		void ReturnRequest() ;
		float CalculateCustomerRecord( int initial_condition , int final_condition , int days ) ;
		float AvgCustomerRecord() ;
		void clearDues() ;
		void DisplayAllCustomers() ;
} ;

class Employee : public User {
	private :
		float employee_record ;
		double dues ;
		int num_cars_rented ;
	public :
		Employee(std::string userid, std::string password, std::string name, float employee_record,  double dues) ;
		Employee(std::string userid, std::string password, std::string name) ;
		Employee() ;
		float CalculateEmployeeRecord( int initial_condition , int final_condition , int days ) ;
		float getEmployeeRecord() ;
		int getNumberOfCarsRented() ;
		void setEmployeeRecord(float employee_record) ;
		double getDues() ;
		float AvgEmployeeRecord() ;
		bool authenticate(std::string , std::string) ;
		void setDues(double dues) ;
		void setNumberOfCarsRented(int num_cars_rented) ;
		int MaxCars() ;
		std::string EmployeeLogin() ;
		void DisplayAllEmployees() ;
		void ReturnRequest() ;
		void clearDues() ;		
} ;

class Manager : public User {
	public :
		bool authenticate(std::string , std::string) ;
		Manager(std::string userid, std::string password, std::string name) ;
		Manager() ;
		std::string ManagerLogin() ;
		void AddUser(int user_type) ;
		void DeleteUser(int user_type) ;
		void UpdateUser(int user_type) ;
		void AddCar() ;
		void DeleteCar() ;
		void UpdateCar() ;
} ;

class CustomerDBM{
    private:
        std::vector<Customer*> customers ;
    public:
		CustomerDBM() ;
		void AddCustomer(Customer* customer) ;
		void DeleteCustomer(std::string userid) ;
		void UpdateCustomer(Customer* customer) ;
		Customer* SelectCustomer(std::string userid) ;
		std::vector<Customer*> ListCustomers() ;
		~CustomerDBM() ;
} ;

class CarDBM{
    private:
        std::vector<Car*> cars ;
    public:
		CarDBM() ;
        void AddCar(Car* car) ;
		void DeleteCar(std::string car_id) ;
		void UpdateCar(Car* car) ;
		Car* SelectCar(std::string car_id) ;
		std::vector<Car*> ListCars() ;
		void DeleteCarsUserID(std::string userid) ;
		~CarDBM() ;
} ;

class ManagerDBM{
    private:
        std::vector<Manager*> managers ;
    public:
		ManagerDBM() ;
		void AddManager(Manager* Manager) ;
		void DeleteManager(std::string userid) ;
		void UpdateManager(Manager* Manager) ;
		Manager* SelectManager(std::string userid) ;
		std::vector<Manager*> ListManagers() ;
		~ManagerDBM() ;
} ;

class EmployeeDBM{
	private:
		std::vector<Employee*> employees ;
	public:
		EmployeeDBM() ;
		void AddEmployee(Employee* employee) ;
		void DeleteEmployee(std::string userid) ;
		void UpdateEmployee(Employee* employee) ;
		Employee* SelectEmployee(std::string userid) ;
		std::vector<Employee*> ListEmployees() ;
		~EmployeeDBM() ;
} ;

struct Date { int d, m, y ; } ;

int countLeapYears(Date d) ;
int DaysDiff(std::string, std::string) ;
bool confirm() ;

std::vector<std::string> readFromFile(std::string filename, int columns) ;
void writeToFile(std::string filename, std::vector<std::string> data, int columns) ;

bool isNumber(std::string s) ;
bool isDecimal(std::string s) ;