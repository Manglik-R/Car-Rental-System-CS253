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
| UP1818 | Tata | 8 | 2000 |  | 1 | 1 |
| UK1812 | Mahindra | 9 | 2500 | 1800 | 0 | 1 |
| MH3632 | Toyota | 6 | 2200 | 2200 | 0 | 1 |
| DL9891 | Hyundai | 7 | 2000 | 2600 | 1 | 1 |
| GJ5172 | Maruti | 5 | 1800 | 9800 | 0 | 1 |
| UP8728 | Skoda | 8 | 3000 | 9800 | 0 | 1 |





