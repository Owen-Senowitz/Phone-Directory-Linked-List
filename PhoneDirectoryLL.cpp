// //Author: Owen Senowitz
// Program to implement a phone directory

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

const char FILENAME[] = "Data.txt"; //Global constant for data file
const int BUFFERSIZE = 30;	// Maximum size for a name/category
const int PHONESIZE = 13;	// Maximum size for a phone number

// Structure used to define a phone directory entry
struct PDEntry
{
	char name[BUFFERSIZE];
	char phone[PHONESIZE];
	char category[BUFFERSIZE];
};

// type definition to define the data type for the list data
typedef PDEntry ListItemType;

// create the node structure
struct Node
{
	ListItemType item;
	Node* next;
};

/*
* Attempts to open a file if present and read contents and adds them to a list.
* If no file is found it creates a file and doesn't
* add anything to the list
*/
Node* openFile();

// Adds entry into the phone directory
Node* addEntry(Node* head);

// Changes the name, phone number, and category in the list
void changeEntry(Node* head);

// Displays pohne directory by Category entered by the user
void displayCategory(Node* head);

// Displays all of the names, phone numbers, and categorys in the list
void displayAll(Node* head, bool printLineNumbers);

// Removes the phone entry off the list 
void removeEntry(Node*& head);

// Writes the phone directory to Data.txt on exit
void writeFile(Node* head);

//Inserts the nodes to the list
Node* insert(Node* head, ListItemType data);

//Deletes the nodes from memory on program exit
void deleteList(Node*& head);

// Main function
int main()
{
	int choice;

	Node* head = openFile();

	do
	{
		cout << "1. Add Entry\n";
		cout << "2. Change Entry\n";
		cout << "3. Display Names in Category\n";
		cout << "4. Display All\n";
		cout << "5. Remove Entry\n";
		cout << "6. Exit\n";
		cout << endl;
		cout << "Select: ";

		// Gets the numeric entry from the menu
		cin >> choice;

		// Makes the 'enter' key that was pressed after the numeric entry be ignored
		cin.ignore();

		switch (choice)
		{
		case 1:
			head = addEntry(head);
			break;
		case 2:
			changeEntry(head);
			break;
		case 3:
			displayCategory(head);
			break;
		case 4:
			displayAll(head, false);
			break;
		case 5:
			removeEntry(head);
			break;
		}
		cout << endl;
	} while (choice != 6);

	writeFile(head);
	deleteList(head);
	return 0;
}

// Loads the program and opens the data.txt file with the contacts in a list
Node* openFile()
{
	ifstream inFile(FILENAME, ios::in);
	Node* head = NULL;

	PDEntry temp;

	if (!inFile.is_open()) {
		cerr << "ERROR! File was not found to Read" << endl;
		return head;
	}

	while (!inFile.eof() && inFile.peek() != EOF) {

		inFile.getline(temp.name, BUFFERSIZE);
		inFile.getline(temp.phone, PHONESIZE);
		inFile.getline(temp.category, BUFFERSIZE);
		head = insert(head, temp);

	}

	inFile.close();
	return head;
}

// Ask the user to enter a name, phone number, and category to add a new contact
Node* addEntry(Node* head)
{
	PDEntry temp;

	cout << "Enter name: ";
	cin.getline(temp.name, BUFFERSIZE);

	cout << "Enter phone number: ";
	cin.getline(temp.phone, PHONESIZE);

	cout << "Enter category: ";
	cin.getline(temp.category, BUFFERSIZE);

	head = insert(head, temp);
	cout << "Entry added" << endl;
	return head;
}

// Shows all of the names and phone numbers in a category
void displayCategory(Node* head)
{
	char category[BUFFERSIZE];
	cout << "Enter category: ";
	cin >> category;

	Node* temp = head;
	while (temp != NULL)
	{
		if (strcmp(temp->item.category, category) == 0)
			printf("\t%-35s %-18s %s\n", temp->item.name, temp->item.phone, temp->item.category);
		temp = temp->next;
	}
}

// Displays all of the names, phone numbers, and categories in the list
void displayAll(Node* head, bool printLineNumbers)
{
	Node* temp = head;
	int lineNum = 0;

	while (temp != NULL)
	{
		lineNum++;

		printf("\t");

		if (printLineNumbers)
		{
			printf("%d. ", lineNum);
		}

		printf("%-35s %-18s %s\n", temp->item.name, temp->item.phone, temp->item.category);

		temp = temp->next;
	}
}

// Removes a name, phone number, and category that is from a numbered list
void removeEntry(Node*& head)
{

	Node* temp = head;
	int userNumber;
	displayAll(head, true);

	cout << "Enter number to remove from list: ";
	cin >> userNumber;
	cin.ignore();

	if (userNumber < 1)
	{
		cerr << "Invalid entry\n";
	}

	else if (userNumber == 1)
	{
		temp = head;
		head = head->next;
		delete temp;

		cout << "Entry removed" << endl;
	}

	else
	{
		int cnt = 2;
		Node* prev = head;
		temp = prev->next;

		while (userNumber > cnt && temp != NULL)
		{
			cnt++;
			prev = prev->next;
			temp = temp->next;
		}

		if (temp == NULL)
		{
			cerr << "Invalid Entry " << endl;
		}

		else
		{
			prev->next = temp->next;
			delete temp;
			cout << "Entry removed" << endl;
		}
	}
}

// Exits the file by writing and saving the changes made to it while it was open
void writeFile(Node* head)
{
	ofstream outFile(FILENAME, ios::out);
	Node* temp = head;

	if (!outFile.is_open())
	{
		cerr << "ERROR! File cannot be opened" << endl;
		return;
	}

	while (temp != NULL)
	{
		outFile << temp->item.name << endl << temp->item.phone << endl << temp->item.category << endl;
		temp = temp->next;
	}

	outFile.close();
}

// Insert into the linked list
Node* insert(Node* head, ListItemType data)
{
	Node* temp = new Node;

	temp->item = data;
	temp->next = head;
	head = temp;

	return head;
}

// Deletes from the linked list
void deleteList(Node*& head)
{
	while (head != NULL)
	{
		Node* temp = head->next;
		delete head;
		head = temp;
	}
	head = NULL;
}

// Adds to the linked list
bool addToList(Node*& head, Node*& lastNode, ListItemType item)
{
	Node* temp = new Node;
	if (temp == NULL) return false;
	temp->item = item;
	temp->next = NULL;

	if (head == NULL)
	{
		head = temp;
		lastNode = temp;
	}

	else
	{
		lastNode->next = temp;
		lastNode = temp;
	}

	return true;
}

/*
* Displays the list of contacts in a numbered list
* and ask the user which contact they want to change
*/
void changeEntry(Node* head)
{
	Node* temp = head;
	int userNumber;

	displayAll(head, true);

	cout << "Enter Number to change Entry: ";
	cin >> userNumber;
	cin.ignore();

	if (userNumber < 1)
	{
		cerr << "Invalid entry\n";
		return;
	}

	else
	{
		int cnt = 1;

		while (userNumber > cnt && temp != NULL)
		{
			cnt++;
			temp = temp->next;
		}

		if (temp == NULL)
		{
			cerr << "Invalid entry\n";
			return;
		}

		cout << "1) " << temp->item.name << endl;;
		cout << "2) " << temp->item.phone << endl;
		cout << "3) " << temp->item.category << endl;

		int choice;
		cout << "What do you want to edit: " << endl;

		cin >> choice;
		cin.ignore();

		if (choice == 1)
		{
			cout << "Enter new Name.\n";
			cin.getline(temp->item.name, BUFFERSIZE);

			cout << "Name updated.\n";
			return;
		}

		else if (choice == 2)
		{
			cout << "Enter new Phone for this entry: ";
			cin.getline(temp->item.phone, PHONESIZE);

			cout << "Phone updated.\n";
			return;
		}

		else if (choice == 3)
		{
			cout << "Enter new category: ";
			cin.getline(temp->item.category, BUFFERSIZE);

			cout << "Category updated.\n";
			return;
		}
	}
}