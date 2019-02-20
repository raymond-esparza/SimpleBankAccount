/*
Program: Simple Bank Account
Author: Raymond Esparza

This program reads in a text file with each line in the file in the format: "firstname lastname floatamount".
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


//This function simply goes through the text file and returns the number of lines
int getnumlines () {
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


//This function takes an empty array of type Person and fills the array with customers 
//and their informtion from the text file
void FillArray(Person *customers){
	int index = 0;
	string firstname, lastname = "";
	float balance = 0.0;
	ifstream datafile("data.txt");
	if(datafile.is_open()){										//test if the textfile is successfully opened
		while( datafile >> firstname >> lastname >> balance) {
			Person x;
			string fullname = firstname + " " + lastname;
			x.balance = balance;
			strcpy( x.name, fullname.c_str() );   //convert fullname into a char array and copy it into x.name
			x.name[fullname.size()] = 0;          //sets the last used char in x.name to null
			customers[index] = x;
			++index;	
		}
		datafile.close();					//close the textfile
    }
}


//This function displays the name and balance of each customer to the screen
void Display( Person *customers, int numlines){
	cout << "     Name            Balance\n";
	cout << "----------------------------------\n";
	for(int i = 0; i != numlines; ++i){
		cout << customers[i].name;
		cout << "    " << customers[i].balance <<endl;
	}
	cout << endl;
}


//This function goes through the balances of the customers and displays the customer with the highest amount
void FindRichest( Person *customers, int numlines){
	int richestposition;
	float highestbalance = 0.0;
	for(int i = 0; i != numlines; ++i){
		if(customers[i].balance >= highestbalance){
			richestposition = i;
			highestbalance = customers[i].balance;
		}
		//else continue searching
	}
	cout << "The customer with the highest balance is " << customers[richestposition].name;
	cout << " with a balance of: $" << customers[richestposition].balance << endl;
}


//This function relies on a user imputted username and compares it with the names of customers in the
//array. If a match is found, this function allows the user to deposit an amount to increase their balance
void Deposit(string username, Person *customers, int numcustomers){
	float amount;
	int name_location;
	bool namefound = false;
	string customer_name;
	for(int i = 0; i != numcustomers; ++i){
		customer_name = customers[i].name;
		if(customer_name == username){
			name_location = i;
			namefound = true;
		}
	}
	if(namefound){
		cout << customers[name_location].name << ", how much would you like to deposit?  $";
		cin >> amount;
		customers[name_location].balance = customers[name_location].balance + amount;
		cout << "Your new balance is:  $" << customers[name_location].balance << endl;
	}
	else
			cout << "Name not found.\n";
	return;
}


//update the text file with any updated information
void NewCopy(string filename, Person *customers, int numlines){
	ofstream datafile(filename);
	if( datafile.is_open() ){
		for(int i = 0; i != numlines; ++i){
			datafile << customers[i].name << " " << customers[i].balance << endl;
		}
	}
	datafile.close();
	return;
}






int main() {


	int numlines = getnumlines();			//find out how many lines are in the text file
	string username = "";
	Person *customers = new Person[numlines]; //creates an array of Persons depending on number of lines in textfile

	FillArray(customers);
	Display(customers, numlines);
	FindRichest(customers, numlines);

	cout << "Enter your full name to deposit money: ";
	getline(cin, username);
	Deposit(username, customers, numlines);
	NewCopy("data.txt", customers, numlines);
	
	delete[] customers;					//release memory of Person array

   	cout << "End of Program.\n";
   	
	return 0;
}

/* sample data.txt content:

Maria Brown 2100.90
Jeffrey Jackson 200.20
Bernard Smith 223.10
Matthew Davenport 1630.2
Kimberly Macias 19100.90
Amber Daniels 2400.40

*/