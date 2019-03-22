/*
Program: Simple Bank Account
Author: Raymond Esparza
File: balance.cpp

This updated program reads in a text file with each line in the file in the format: "firstname lastname floatamount".
It then creates creates a dynamic array of type "Person" AKA individual customers and fills the elements
with information from the text file. The program prints to the screen a list of each customer and their
balance, finds the person with the largest amount in their account, and prompts the user for a name to make
a deposit. Finally, the program overwrites the original textfile with updated information.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;



struct Person {
	char name[20];
	float balance;
};


//function declarations
int getnumlines();
Person* readData(int &);
void FillArray(Person*);
void Display(Person*, int);
void FindRichest(Person*, int);
void Deposit(Person*, int, string, float);
void NewCopy(string, Person*, int);



int main() {


	int N = 0;
	string custName;
	float amount;
	bool namefound = false;
	Person *arr = readData(N);

	Display(arr, N);
	FindRichest(arr, N);

	//see if user is in the system before prompting an amount
	cout << "Enter name: ";
	getline(cin, custName);

	for(int i = 0; i != N; ++i){
		if(arr[i].name == custName){
			namefound = true;
		}
	}
	if(namefound){
		cout << "Amount: ";
		cin >> amount;
		Deposit(arr, N, custName, amount);	//all user input is gathered outside this function
	}
	else{
		cout << "Record not found.\n";
	}
	
	NewCopy("data.txt", arr, N);
	
   	cout << "End of Program.\n";
   	delete[] arr;
	return 0;
}




//This function simply goes through the text file and returns the number of lines
int getnumlines() {
	ifstream datafile("data.txt");
	int numlines = 0;
	string textline;
	if(datafile.is_open()){		
		while(getline(datafile, textline)) {
			++numlines;
		}
		
		datafile.close();
	}
	return numlines;
}


//This function opens a textfile and reads in the data. It then creates a dynamically
//allocated array of type Person and fills each element with the information it read.
//When all lines are read and the array is full, it returns a pointer to the array.
Person* readData(int &N){
	N = getnumlines();
	Person *arr = new Person[N];
	string firstname, lastname = "";
	ifstream datafile("data.txt");

	if(datafile.is_open()){								//test if the textfile is successfully opened
		for(int i = 0; i != N; ++i){
			datafile >> firstname >> lastname >> arr[i].balance;
			string fullname = firstname.substr(0,9) + " " + lastname.substr(0,10);  //only accept the first 9 characters of the firstname and first 10 characters from the lastname
			strcpy( arr[i].name, fullname.c_str() );   //convert fullname into a char array and copy it into the current Person's name
			arr[i].name[fullname.size()] = 0;
		}
		datafile.close();		//close the textfile
    }
    return arr;
}


//This function displays the name and balance of each customer to the screen
void Display( Person *arr, int N){
	cout << "     Name            Balance\n";
	cout << "----------------------------------\n";
	for(int i = 0; i != N; ++i){
		cout << arr[i].name;
		cout << "    " << arr[i].balance <<endl;
	}
	cout << endl;
	return;
}


//This function goes through the balances of the customers and displays the customer with the highest amount
void FindRichest( Person *arr, int N){
	int richestposition;
	float highestbalance = 0.0;
	for(int i = 0; i != N; ++i){
		if(arr[i].balance >= highestbalance){
			richestposition = i;
			highestbalance = arr[i].balance;
		}
		//else continue searching
	}
	cout << "Highest balance: " << arr[richestposition].name << endl << endl;
	return;
}


//This function relies on a valid user imputted username and compares it with the names of customers in the
//array. When a match is found, this function deposits an amount to increase their balance.
void Deposit(Person *arr, int N, string custName, float amount){
	for(int i = 0; i != N; ++i){
		if(custName == arr[i].name){
			arr[i].balance = arr[i].balance + amount;
			cout << "New balance: " << arr[i].balance << endl << endl;
		break;
		}
		//else continue searching
	}
	return;
}


//update the text file with any updated information
void NewCopy(string filename, Person *arr, int N){
	ofstream datafile(filename);
	if( datafile.is_open() ){
		for(int i = 0; i != N; ++i){
			datafile << arr[i].name << " " << arr[i].balance << endl;
		}
		datafile.close();
	}
	cout << "File Updated...\n" << endl;
	return;
}


/* sample data.txt content:

Maria Brown 2100.90
Jeffrey Jackson 200.20
Bernard Smith 223.10
Matthew Davenport 1630.2
Kimberly Macias 19100.90
Amber Daniels 2400.40

*/