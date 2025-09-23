// main entry
#include "include/pulse/event.hpp"
#include <string>
#include <iostream>
#include <format>


void helloString(std::string str) {
	std::cout << std::format("This is from the helloString function! It says: {}\n", str);
}

void helloInt(int x) {
	std::cout << std::format("This is from the helloInt function! It says: {}\n", x);
}


int main(int argc, char* argv[])
{
	std::cout << "Added Listener to helloStringEvent\n";
	pulse::Event<std::string> helloStringEvent;
	helloStringEvent.addListener(helloString);

	std::cout << "Added Listener to helloIntEvent\n";
	pulse::Event<int> helloIntEvent;
	helloIntEvent.addListener(helloInt);

	std::cout << "Firing helloStringEvent\n";
	helloStringEvent.invoke("Hello World!");

	std::cout << "Firing helloIntEvent\n";
	helloIntEvent.invoke(42069);

	return 0;
}