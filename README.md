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

## Running the Program
This repository contains 4 different databases to store information about `Customers`, `Employees`, `Managers` and `Cars`.
There are initially 5 Customers, 5 Employees, 6 Cars and 1 Manager. The details of which are shown below :

### Customers
| UserID  | Password | Name  | Customer Record |  Dues  | Number of Cars Rented |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| User1 | Password1  | Rohan | 70 | 1000 | 0 |
| User2 | Password2  | Rahul | 80 | 1250 | 1 |
| User3 | Password3  | Karan | 90 | 2000 | 0 |
| User4 | Password4  | Amogh | 85 | 3000 | 0 |
| User5 | Password5  | Rajat | 95 | 1400 | 2 |

### Employees
| UserID  | Password | Name  | Employee Record |  Dues  | Number of Cars Rented in Rs. |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-------------: |
| Employee1 | Password1  | Ben | 65 | 1300 | 1 |
| Employee2 | Password2  | Tom | 95 | 1800 | 0 |
| Employee3 | Password3  | Hog | 40 | 2200 | 0 |
| Employee4 | Password4  | Adi | 65 | 2600 | 1 |
| Employee5 | Password5  | Rvi | 70 | 9800 | 0 |

### Manager
| UserID  | Password | Name  |
| :-------------: | :-------------: | :-------------: |
| Manager1 | Password1  | Harry |

### Cars
| CarID  | Model | Condition  | Rent per Day in Rs. |  Rent Date  | Due Date | UserID of who rented |
| :-------------: | :-------------: | :-------------: | :-------------: | :-------------: | :-----------: | :-----------: |
| UP1818 | Tata | 8 | 2000 | 27-02-2024 | 04-03-2024 | User2 |
| UK1812 | Mahindra | 9 | 2500 |  |  |  |
| MH3632 | Toyota | 6 | 2200 | 28-02-2024 | 07-03-2024 | User5 |
| DL9891 | Hyundai | 7 | 2000 | 24-02-2024 | 01-03-2024 | User5 |
| GJ5172 | Maruti | 5 | 1800 | 15-02-2024 | 03-03-2024 | Employee1 |
| UP8728 | Skoda | 8 | 3000 | 23-02-2024 | 08-03-2024 | Employee4 |

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







