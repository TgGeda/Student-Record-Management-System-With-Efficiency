# Student-Record-Management-System-With-Efficiency
A time and space efficient  Student Record Management System implementation using c:
To ensure time and space efficiency, the program uses dynamic memory allocation to allocate memory only when required and deallocates memory when it is no longer needed. The program uses a linked list data structure to store the student records, which allows for easy insertion and deletion of records. 

The program starts by reading the student records from the binary file and storing them in the linked list. The user is then presented with a menu of options to perform CRUD operations on the student data. 

To add a new student, the program prompts the user to enter the student details, which are then added to the linked list and written to the binary file. 

To search for a student, the program prompts the user to enter the name or roll number of the student. The program then searches the linked list for the student and displays their details if found. 

To update a student's details, the program prompts the user to enter the roll number of the student. The program then searches the linked list for the student and prompts the user to enter the updated details. The program then updates the student record in the linked list and writes the updated record to the binary file. 

To delete a student, the program prompts the user to enter the roll number of the student. The program then searches the linked list for the student and removes the record from the linked list. The program then writes the updated records to the binary file. 

The program also includes error handling to prevent invalid input and to handle file I/O errors. 

Overall, this Student Record Management System provides an efficient and reliable way to manage student records using file I/O operations and dynamic memory allocation.
