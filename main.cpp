#include <iostream>
#include <fstream>
#include <string>
#include <list>

const std::string CURRENT_VERSION = "1.1.0";
const std::string FILE_NAME = "list.txt";

enum Commands {
	newTodo = 'n',
	deleteTodo = 'd',
	showTodos = 's',
	clearAll = 'c',
};

void startUp();
void requestOnNewCommand(char& _command);
void stateUpdate(std::list<std::string>& todos);

void _newTodo(std::list<std::string>& todos) {
	std::cin.clear();
	std::string todo = "";
	std::cout << "Enter your todo: ";
	if (todo.length() != 0) {
		std::cout << "Error!" << std::endl;
		return;
	}
	std::cin >> todo;
	std::cout << std::endl;

	while (std::cin.get() != '\n') {
		std::string tmp = "";
		std::cin >> tmp;
		todo += " " + tmp;
	}
	
	todos.push_back(todo);
	stateUpdate(todos);
}

void _deleteTodo(std::list<std::string>& todos) {
	unsigned int number = 0;
	std::cout << "Enter number of your todo: ";
	std::cin >> number; 

	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Not num." << std::endl;
		return;
	}
	if (number - 1 < 0 || number - 1 >= todos.size()) {
		std::cout << "Incorrect position." << std::endl;
		return;
	}

	std::list<std::string>::iterator position = todos.begin();
	std::advance(position, number - 1);

	todos.erase(position);

	stateUpdate(todos);
}

void _showTodos(std::list<std::string>& todos) {
	unsigned int counter = 0;
	if (todos.empty()) {
		std::cout << "You haven't any todos." << std::endl;
		return;
	}
	std::cout << std::endl;
	for (auto& todo: todos)
		std::cout << ++counter << ") " << todo << std::endl;
	std::cout << std::endl;
}

void _clearAll(std::list<std::string>& todos) {
	todos.clear();
	std::cout << "Cleared all todos." << std::endl;
	stateUpdate(todos);
}

int main() {
	setlocale(LC_ALL, "eng");

	std::ifstream listIn(FILE_NAME);
	if (!listIn.is_open()) {
		std::cout << "Have no needed file in this directory." << std::endl;
		system("pause");
		exit(100);
	}

	std::list<std::string> todos = {};
	std::string text;
	while (getline(listIn, text))
		todos.push_back(text);
	
	listIn.close();

	startUp();

	char command;

	while (true) {

		requestOnNewCommand(command);

		switch (command){
		case Commands::newTodo:
			_newTodo(todos);
			continue;
		case Commands::deleteTodo:
			_deleteTodo(todos);
			continue;
		case Commands::showTodos:
			_showTodos(todos);
			continue;
		case Commands::clearAll:
			_clearAll(todos);
			continue;
		}
	}

	return 0;
}

void startUp() {
	std::cout << "You are welcome in todos application (" << CURRENT_VERSION << ")." << std::endl << std::endl;
	std::cout << "You can: " << std::endl;
	std::cout << "create [n]ew todo." << std::endl;
	std::cout << "[d]elete todo." << std::endl;
	std::cout << "[s]how todos." << std::endl;
	std::cout << "[c]lear all todos." << std::endl;
	std::cout << std::endl << std::endl;
}

void requestOnNewCommand(char& _command) {
	std::string command;
	std::cout << "Enter command: ";
	std::cin >> command;

	while (std::cin.get() != '\n') {
		std::string tmp = "";
		std::cin >> tmp;
		command += " " + tmp;
	}
	
	if (command.length() > 1 || (command[0] != Commands::clearAll &&
		command[0] != Commands::deleteTodo &&
		command[0] != Commands::newTodo &&
		command[0] != Commands::showTodos)) {
		std::cout << "Error command!!! Try again." << std::endl << std::endl;
		_command = ' ';
		return;
	}

	_command = command[0];
}

void stateUpdate(std::list<std::string>& todos) {
	std::ofstream listOut(FILE_NAME);
	if (!listOut.is_open()) {
		std::cout << "Something went wrong.";
		exit(200);
	}
	for(auto& todo: todos) {
		listOut << todo << '\n';
	}
	listOut.close();
}