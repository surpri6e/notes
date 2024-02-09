# Notes

In project don't use other **.dll** or **.lib** 
Standart: **ISO C++ 14**

For work you need list.txt in current directory.

I use React.js principles in cpp project!

Example: 

```
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
```