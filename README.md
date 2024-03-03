# Car Rental Management System
This repository contains my submission for the C++ Assignment for the course CS253 : Software Development and Operations, Spring 2024 under the guidance of Prof. Indranil Saha.

## Setup Instructions
Clone this repository using the below command in terminal.
```
git clone https://github.com/Manglik-R/Car-Rental-System-CS253.git
```
Run the code below to compile the files and create an executable file.
```
g++ -std=c++17 main.cpp
```
Run the created executable file by running below code.
```
./a.exe
```

## Project Structure

The repository is organised as : 
- `DB` Folder : This folder acts as the database and contains 4 comma separated values files to store information.
  - `customer.csv` : This file contains information about customers. It contains 6 different columns namely `UserId`, `Password`, `Name`, `CustomerRecord`, `Dues` and `NumberOfCarsRented`.
  - `employee.csv` : This file contains information about employees. It contains 6 different columns namely `UserId`, `Password`, `Name`, `EmployeeRecord`, `Dues` and `NumberOfCarsRented`.
  - `manager.csv` : This file contains information about managers. It contains 6 different columns namely `UserId`, `Password` and `Name`.
  - `car.csv` : This file contains information about customers. It contains 6 different columns namely `CarId`, `Model`, `Condition`, `RentDate`, `DueDate` and `UserIdRented`.

- `Model.hpp` : This file contains the definitions of classes, functions and structures.
  - `User` class :
    - Base class for Customer, Employee and Manager.
    - Attributes - UserID, Password and Name.
  - `Customer` class :
    - Attributes - UserId, Password, Name, CustomerRecord, Dues and NumberOfCarsRented.
    - Functions - to Authenticate, Login, Calculate Max Cars a Customer can Rent, Return a Rented Car, Calculate CustomerRecord, Clear Dues and Display All Customers.
  - `Employee` class :
    - Attributes - UserId, Password, Name, EmployeeRecord, Dues and NumberOfCarsRented.
    - Functions - to Authenticate, Login, Calculate Max Cars a Employee can Rent, Return a Rented Car, Calculate EmployeeRecord, Clear Dues and Display All Employees.
  - `Car` class :
    - Attributes - CarId, Model, Condition, RentPerDay, RentDate, DueDate and UserID.
    - Functions - to Rent a Car, check if a Car is Rented, Calculate Fines, Calculate Dues and Display Cars - Rented Cars, Available Cars and All Cars of Store. 
  - `CustomerDBM` class : A vector of Customer class which reads from and write to comma separated values files.
    - Functions - to Add a Customer, Delete a Customer, Update a Customer, Select a particular Customer using UserID and get List of all Customers.
  - `EmployeeDBM` class : A vector of Employee class which reads from and write to comma separated values files.
    - Functions - to Add an Employee, Delete an Employee, Update an Employee, Select a particular Employee using UserID and get List of all Employee.
  - `ManagerDBM` class : A vector of Manager class which reads from and write to comma separated values files.
    - Functions - to Add a Manager, Delete a Manager, Update a Manager, Select a particular Manager using UserID and get List of all Manager.
  - `CarDBM` class : A vector of Customer class which reads from and write to comma separated values files.
    - Functions - to Add a Car, Delete a Car, Update a Car, Select a particular Car using CarID and get List of all Cars.
  - `Date` structure : A structure to perform operations on Date Type data.
  - Other Functions : to find Number of days between 2 dates, Read a comma separated values file, Write a comma separated values file and check if a string is a Decimal/Number or not.

- `Car.cpp` : Contains implementation of functions of `Car` class.
- `Customer.cpp` : Contains implementation of functions of `Customer` class.
- `Employee.cpp` : Contains implementation of functions of `Employee` class.
- `Manager.cpp` : Contains implementation of functions of `Manager` class.
- `DB_Manager.cpp` : Contains implementation of functions of `CustomerDBM`, `EmployeeDBM`, `ManagerDBM` and `CarDBM` class.
- `main.cpp` : Consists of the main program, managing the flow of control between different functions and classes. Also includes implementation of `Other Functions`.


## Running the Program
This repository contains 4 different databases to store information about `Customers`, `Employees`, `Managers` and `Cars`.
There are initially 5 Customers, 5 Employees, 6 Cars and 1 Manager. The details of which are shown below :

### Customers
| UserID  | Password | Name  | Customer Record |  Dues  | Number of Cars Rented |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| user1 | password1  | Rohan | 70 | 1000 | 0 |
| user2 | password2  | Rahul | 80 | 1250 | 1 |
| user3 | password3  | Karan | 90 | 2000 | 0 |
| user4 | password4  | Amogh | 85 | 3000 | 0 |
| user5 | password5  | Rajat | 95 | 1400 | 2 |

### Employees
| UserID  | Password | Name  | Employee Record |  Dues  | Number of Cars Rented in Rs. |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| employee1 | password1  | Ben | 65 | 1300 | 1 |
| employee2 | password2  | Tom | 95 | 1800 | 0 |
| employee3 | password3  | Hog | 40 | 2200 | 0 |
| employee4 | password4  | Adi | 65 | 2600 | 1 |
| employee5 | password5  | Jen | 70 | 9800 | 0 |

### Manager
| UserID  | Password | Name  |
| :-------------: | :-------------: | :-------------: |
| manager1 | password1  | Harry |

### Cars
| CarID  | Model | Condition  | Rent per Day in Rs. |  Rent Date  | Due Date | UserID of who rented |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-----------: | :-----------: |
| UP1818 | Tata | 8 | 2000 | 27-02-2024 | 04-03-2024 | user2 |
| UK1812 | Mahindra | 9 | 2500 |  |  |  |
| MH3632 | Toyota | 6 | 2200 | 28-02-2024 | 07-03-2024 | user5 |
| DL9891 | Hyundai | 7 | 2000 | 24-02-2024 | 01-03-2024 | user5 |
| GJ5172 | Maruti | 5 | 1800 | 15-02-2024 | 03-03-2024 | employee1 |
| UP8728 | Skoda | 8 | 3000 | 23-02-2024 | 08-03-2024 | employee4 |

**NOTE : In Cars database, If a car is not rented its attributes `Due Date`, `Rent Date` and `UserID of who rented` are left blank.**

## Assumptions and Design 

- A Car rented to a User can not be deleted or updated by Manager.
- If Manager deletes a User, Cars rented by him are returned back.
- Condition of a Car is rated on a scale of `0 to 10`, 0 being very bad condition and 10 being very good.
- Record of both Customer and Employee are maintained using a scale from `0 to 100`, 0 being bad and 100 being good.
-  If the Customer/Employee database is empty and a new User is added, User is assigned an initial record score of `80`.
- A User can rented maximum upto `(User Record)/30 + 1` Cars.
- It is assumed that condition of a car can improve as well worsen when returned back by a User and Record of the User is updated based on change in the condition of the Car and how late car is returned back.
- A User can rent a Car for upto 200 days only.
- `UserID`, `CarID`, `Name`, `Model` and `Password` Attributes contains a single word. If an input in the proegram is of more than one word then only first word would be considered for processing.

## Portability 

- The code was written in Windows operating system. Few functionalities can cause issue in other operating systems, like to clear terminal screen in Linux, replace `system("cls")` has to be changed to `system("clear")`.

## Author
- Raghav Manglik
- IIT Kanpur
- 220854 




