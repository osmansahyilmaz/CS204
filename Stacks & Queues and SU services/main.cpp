//CS204 Fall 2023 - HW3: Stacks & Queues and SU services

#include <iostream>
#include <fstream>       // for ifstream
#include <cctype>        
#include <string>
#include <vector>
#include <sstream>      // std::stringstream
using namespace std;

struct QueueNode
{
	string function;
	string name;
	int ID;
	int price;
	QueueNode* next;
	QueueNode(string inputFunction, string inputName, int inputID, QueueNode* ptr = nullptr)
	{

		function = inputFunction;
		name = inputName;
		ID = inputID;
		price = 0;
		next = ptr;
	}
};

class DynStringQueue
{
private:
	// These track the front and rear of the queue.
	QueueNode* front;
	QueueNode* rear;
public:
	// Constructors.
	DynStringQueue()
	{
		front = nullptr;
		rear = nullptr;
	};

	// Member functions.
	void enqueue(string inputFunction, string inputName, int inputID){
		if (isEmpty())   //if the queue is empty
		{	//make it the first element
			front = new QueueNode(inputFunction, inputName, inputID);
			rear = front;
		}
		else  //if the queue is not empty
		{	//add it after rear
			rear->next = new QueueNode(inputFunction, inputName, inputID);
			rear = rear->next;
		}
	}

	void dequeue(int &inputID)
	{
		QueueNode* temp;
		if (isEmpty())
		{
			cout << "Attempting to dequeue on empty queue, exiting program...\n";
			exit(1);
		}
		else //if the queue is not empty
		{	//return front's value, advance front and delete old front
			inputID = front->ID;
			temp = front;
			front = front->next;
			delete temp;
		}
	}
	bool isEmpty() const
	{
		if (front == nullptr)
			return true;
		else
			return false;
	}

	QueueNode* getFront() const {
		return front;
	}

	void clear()
	{
		int ID;   // Dummy variable for dequeue

		while (!isEmpty())
			dequeue(ID); //delete all elements
	}

};

struct StackNode
{
	string value;
	StackNode* next;
};

class DynStringStack
{
private:
	StackNode* top;

public:
	DynStringStack() {
		top = nullptr;
	}
	void push(string inputValue)
	{
		StackNode* newNode;
		// Allocate a new node & store Num
		newNode = new StackNode;
		newNode->value = inputValue;

		// If there are no nodes in the list
		// make newNode the first node
		if (isEmpty())
		{
			top = newNode;
			newNode->next = nullptr;
		}
		else	// Otherwise, insert NewNode before top
		{
			newNode->next = top;
			top = newNode;
		}
	}

	void pop(string& inputValue)
	{
		StackNode* temp;

		if (isEmpty())
		{
			cout << "The stack is empty.\n";
		}
		else	// pop value off top of stack
		{
			inputValue = top->value;
			temp = top->next;
			delete top;
			top = temp;
		}
	}
	StackNode* getTop() const {
		return top;
	}

	bool isEmpty(void)
	{
		bool status;

		if (top == nullptr)
			status = true;
		else
			status = false;

		return status;
	}
	
	DynStringStack(const DynStringStack& other) {
		top = nullptr;
		StackNode* source = other.top;

		// Create a temporary stack to reverse the order
		DynStringStack tempStack;

		while (source) {
			// Push elements onto the temporary stack
			tempStack.push(source->value);
			source = source->next;
		}

		// Now, push elements back onto the original stack in reverse order
		while (!tempStack.isEmpty()) {
			string value;
			tempStack.pop(value);
			push(value);
		}
	}
};

struct CommandNode {
	string command;
	CommandNode* next;

	CommandNode(const string& cmd) : command(cmd), next(nullptr) {}
};

struct FunctionNode {
	string functionName;
	CommandNode* commands;
	FunctionNode* next;

	FunctionNode(const string& name) : functionName(name), commands(nullptr), next(nullptr) {}
};

class FunctionList {
private:
	FunctionNode* head;

public:
	FunctionList() {
		head = nullptr;
	}


	FunctionNode* getHead() const {
		return head;
	}

	void addFunction(const string& functionName) {
		FunctionNode* newNode = new FunctionNode(functionName);
		if (head == nullptr) {
			head = newNode;
		}
		else {
			FunctionNode* current = head;
			while (current->next != nullptr) {
				current = current->next;
			}
			current->next = newNode;
		}
	}

	void addCommand(const string& command, const string& functionName) {
		FunctionNode* current = head;
		while (current != nullptr) {
			if (current->functionName == functionName) {
				if (current->commands == nullptr) {
					current->commands = new CommandNode(command);
				}
				else {
					CommandNode* cmd = current->commands;
					while (cmd->next != nullptr) {
						cmd = cmd->next;
					}
					cmd->next = new CommandNode(command);
				}
				return;
			}
			current = current->next;
		}
	}

	void displayFunctions() {
		FunctionNode* current = head;
		while (current != nullptr) {
			cout << current->functionName << " ";
			cout << endl;
			CommandNode* cmd = current->commands;
			while (cmd->next != nullptr) {
				cout << cmd->command << ", ";
				cmd = cmd->next;
			}
			cout << cmd->command.substr(0, cmd->command.length()-1) << ".";
			cout << endl;
			cout << endl;
			current = current->next;
		}
	}
};

// our queues 
DynStringQueue instructorsQueue;
DynStringQueue studentsQueue;
DynStringQueue usersQueue;



// function lists
vector<FunctionList> functionLists;
vector<string> functionNameListGlobal;

vector<FunctionList> createFunctionList(const vector<string>& inputFiles) {
	vector<FunctionList> functionLists;
	vector<string> functionNameList; // create a separate vector for function names

	for (const string& inputFile : inputFiles) {
		ifstream file(inputFile);
		if (file.is_open()) {
			string line;
			string currentFunction;

			FunctionList functionList;
			getline(file, line);
			currentFunction = line;
			functionList.addFunction(currentFunction);

			functionNameList.push_back(currentFunction.substr(0, currentFunction.length() - 1));

			while (getline(file, line)) {
				functionList.addCommand(line, currentFunction);
			}

			functionLists.push_back(functionList);
		}
		else {
			cout << "Could not open the file " << inputFile << endl;
			exit(1);
		}
	}

	// store the function name list in the global vector
	functionNameListGlobal = functionNameList;

	return functionLists;
}


void addInstructorWorkload() {
	cout << "Add a service (function) that the instructor wants to use: " << endl;
	string inputFunction;
	cin >> inputFunction;
	if (find(functionNameListGlobal.begin(), functionNameListGlobal.end(), inputFunction) != functionNameListGlobal.end()) {
		int index = 0;
		for (int i = 0; i < functionLists.size(); i++) {
			if ( functionNameListGlobal[i] == inputFunction) {
				index = i;
				break;
			}
		}
		cout << "Give instructor's name: ";
		string inputName;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, inputName);
		
		size_t spacePos = inputName.find(" ");
		if (spacePos != string::npos) {
			// replace spaces with "(username-cannot-have-white-spaces-included)"
			inputName = inputName.substr(0, spacePos) + "(username-cannot-have-white-spaces-included)";
		}

		cout << "Give instructor's ID (an int): ";
		int inputID;
		cin >> inputID;

		cout << "Prof. " << inputName << "'s service request of "<< inputFunction<<" has been put in the instructor's queue." << endl;
		cout << "Waiting to be served..." << endl;
		instructorsQueue.enqueue(inputFunction, inputName, inputID);
		
		QueueNode* temp = usersQueue.getFront();
		while (temp) {
			if (temp->ID == inputID) {
				return;
			}
			temp = temp->next;
		}
		usersQueue.enqueue(inputFunction, inputName, inputID);
	}
	else {
		cout << "The requested service (function) does not exist." << endl;
		return;
	}
}

void addStudentWorkload() {
	cout << "Add a service (function) that the student wants to use: " << endl;
	string inputFunction;
	cin >> inputFunction;
	if (find(functionNameListGlobal.begin(), functionNameListGlobal.end(), inputFunction) != functionNameListGlobal.end()) {
		int index = 0;
		for (int i = 0; i < functionLists.size(); i++) {
			if (functionNameListGlobal[i] == inputFunction) {
				index = i;
				break;
			}
		}
		cout << "Give student's name: ";
		string inputName;

		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, inputName);

		size_t spacePos = inputName.find(" ");
		if (spacePos != string::npos) {
			// replace spaces with "(username-cannot-have-white-spaces-included)"
			inputName = inputName.substr(0, spacePos) + "(username-cannot-have-white-spaces-included)";
		}

		cout << "Give student's ID (an int): ";
		int inputID;
		cin >> inputID;

		cout << inputName << "'s service request of " << inputFunction << " has been put in the student's queue." << endl;
		cout << "Waiting to be served..." << endl;
		studentsQueue.enqueue(inputFunction, inputName, inputID);

		QueueNode* temp = usersQueue.getFront();
		while (temp) {
			if (temp->ID == inputID) {
				return;
			}
			temp = temp->next;
		}
		usersQueue.enqueue(inputFunction, inputName, inputID);
	}
	else {
		cout << "The requested service (function) does not exist." << endl;
		return;
	}
}

void updatePrice(QueueNode* currentNode, int num) {
	QueueNode* userNode = usersQueue.getFront();
	while (userNode->name != currentNode->name) {
		userNode = userNode->next;
	}
	userNode->price += num;
}

// recursive function processing
void processWorkload(QueueNode* currentNode ,string functionName, DynStringStack printStackParameter) {
	// this is for using new printstick to after inner recursive, delete inner recursives data from outer stack
	// we are basically not using outer functions stack, just copying it, so deleting its data is a lie, we never used original one :)
	DynStringStack innerPrintStack = printStackParameter;

	int f = 0;
	FunctionNode* currentFunction = functionLists[f++].getHead();
	string toPush = "";
	while (f <= functionLists.size()) {
		if (currentFunction->functionName.substr(0, currentFunction->functionName.length() - 1) == functionName) {
			CommandNode* currentCommand = currentFunction->commands;
			while (currentCommand != nullptr) {
				string command = currentCommand->command;

				if (command.find("define") != string::npos) {
					// if the command is a "define" command, push it to the print stack
					toPush = functionName + " " + command;
					innerPrintStack.push(toPush);
					updatePrice(currentNode, 1);
					//currentNode->price += 1;
				}
				else if (command.find("call") != string::npos) {
					cout << "Calling " << command.substr(5, 10) << " from " << currentFunction->functionName.substr(0, 10) << endl;
					// if the command is a "call" command, execute it as before
					if (find(functionNameListGlobal.begin(), functionNameListGlobal.end(), command.substr(5, 10)) != functionNameListGlobal.end()) {
						string functionToCall = command.substr(5, 10);
						for (size_t i = 0; i < functionLists.size(); i++) {
							if (functionLists[i].getHead()->functionName.substr(0, 10) == functionToCall) {
								// recursively process the function call
								processWorkload(currentNode, functionToCall, innerPrintStack);
							}
						}
					}
					updatePrice(currentNode, 5);
					//currentNode->price += 5;
				}
				else if (command.find("print stack") != string::npos) {
					cout << "Executing print stack; command from " << functionName << endl;
					cout << "PRINTING THE STACK TRACE:" << endl;

					if (innerPrintStack.isEmpty()) {
						cout << "The stack is empty" << endl;
					}
					else {
						// execute and print stored "define" commands from the print stack in order
						DynStringStack tempStack = innerPrintStack;  // copy of the stack to avoid modifying the original stack

						// vector to store the elements in reverse order for printing the stack trace
						vector<string> reversedCommands;

						while (!tempStack.isEmpty()) {
							string command;
							tempStack.pop(command); // Pop the top element to get the command
							reversedCommands.push_back(command);
						}

						// Reverse the vector
						reverse(reversedCommands.begin(), reversedCommands.end());

						// Print the elements in reverse order
						for (auto it = reversedCommands.begin(); it != reversedCommands.end(); ++it) {
							cout << *it << endl;
						}
					}
					updatePrice(currentNode, 2);
					//currentNode->price += 2;
				}
				if (!currentCommand) {
					cout << functionName << " is finished. Clearing the stack from it's data..." << endl;
					return;
				}
				else {
					currentCommand = currentCommand->next;
				}
			}
			if (!currentCommand) {
				cout << functionName << " is finished. Clearing the stack from it's data..." << endl;
				return;
			}
		}
		currentFunction = functionLists[f++].getHead();
	}

}

int processedInst = 0;
void processWorkload()
{
	// shared memory stack"
	DynStringStack printStack;
	
	if (!instructorsQueue.isEmpty() && ::processedInst < 10)
	{
		cout << "Processing instructors queue..." << endl;
		QueueNode* currentNode = instructorsQueue.getFront();

		cout << "Processing prof." << currentNode->name << "'s request (with ID " << currentNode->ID << ") of service (function):\n" << currentNode->function << endl;
		//You need to implement the processWorkload --> you can modify inputs
		processWorkload(currentNode, currentNode->function, printStack);
		instructorsQueue.dequeue(currentNode->ID);
		cout << "GOING BACK TO MAIN MENU" << endl;
		::processedInst++;
	
	}
	else if (!studentsQueue.isEmpty())
	{
		//TODO: This should print when you implemented 10 requests for instructors and 1 request for students logic
		if (::processedInst >= 10 && !instructorsQueue.isEmpty()) {
			cout<<"10 instructors are served. Taking 1 student from the queue..."<<endl;
		}
		else if (instructorsQueue.isEmpty()) {
			cout << "Instructors queue is empty. Proceeding with students queue..." << endl;
		}
		::processedInst = 0;
		QueueNode* currentNode = studentsQueue.getFront();

		cout << "Processing " << currentNode->name << "'s request (with ID " << currentNode->ID << ") of service (function):\n" << currentNode->function << endl;
		cout << "-------------------------------------------------------" << endl;

		//You need to implement the processWorkload --> you can modify inputs
		processWorkload(currentNode, currentNode->function, printStack);
		studentsQueue.dequeue(currentNode->ID);
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
	else
	{
		cout << "Both instructor's and student's queue is empty.\nNo request is processed." << endl << "GOING BACK TO MAIN MENU" << endl;
	}
}

void displayUsers() {
	if (usersQueue.isEmpty()) {
		cout << "No payments defined." << endl;
		return;
	}

	cout << "Displaying user information:" << endl;

	QueueNode* currentNode = usersQueue.getFront();
	while (currentNode != nullptr) {
		int ID = currentNode->ID;
		cout << "Name: " << currentNode->name << " ID: " << ID << " " << currentNode->price << " TRY" << endl;
		currentNode = currentNode->next;
	}
}

int main()
{
	vector<string> inputFiles;
	string inputFile;
	char openAnotherFile;
	cout << "If you want to open a service (function) defining file," << endl;
	cout << "then press (Y/y) for 'yes', otherwise press any single key" << endl;
	cin >> openAnotherFile;
	if (tolower(openAnotherFile) == 'y') {
		cout << "Enter the input file name: ";
		cin >> inputFile;
		inputFiles.push_back(inputFile);
		while (true) {
			cout << "If you want to open another service defining file?" << endl;
			cout << "Press (Y/y) for 'yes', otherwise press any key" << endl;
			cin >> openAnotherFile;

			if (tolower(openAnotherFile) == 'y') {
				cout << "Enter the input file name: ";
				cin >> inputFile;
				inputFiles.push_back(inputFile);
			}
			else {
				break;
			}
		}
	}
	else {
		exit(1);
	}

	functionLists = createFunctionList(inputFiles);



	cout << "------------------------------------------------------------------" << endl;
	cout << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl;
	cout << "------------------------------------------------------------------" << endl;

	//print here
	for (int i = 0; i < functionLists.size(); i++) {
		functionLists[i].displayFunctions();
	}

	while (true){		
       cout << endl;
 		cout<<"**********************************************************************"<<endl
	    <<"**************** 0 - EXIT PROGRAM                        *************"<<endl
	    <<"**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST   *************"<<endl
	    <<"**************** 2 - ADD A STUDENT SERVICE REQUEST       *************"<<endl	
	    <<"**************** 3 - SERVE (PROCESS) A REQUEST           *************"<<endl
		<<"**************** 4 - DISPLAY USER PAYMENTS               *************"<<endl
	    <<"**********************************************************************"<<endl;
		cout << endl;
		int option;
		cout << "Pick an option from above (int number from 0 to 3): ";
		cin>>option;
		switch (option)
		{
			case 0:
				cout<<"PROGRAM EXITING ... "<<endl;
				exit(0);
			case 1:
				addInstructorWorkload();
				break;
			case 2:
				addStudentWorkload();
				break;
			case 3:
				processWorkload();
				break;
			case 4:
				displayUsers();
				break;
			default:
				cout<<"INVALID OPTION!!! Try again"<<endl;
		}
	}
	return 0;
}