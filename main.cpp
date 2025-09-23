// main entry
#include "include/pulse/event.hpp"
#include "include/pulse/message_bus.hpp"
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
	std::cout << "-------------------------Event tests-------------------------\n";
	pulse::Event<std::string> helloStringEvent;

	std::cout << "Added Listener to helloStringEvent\n";
	pulse::Event<std::string>::EventConnection helloStringMethodConnection = helloStringEvent.addListener(helloString);
	std::cout << "Added Listener to helloStringEvent (lambda)\n";
	pulse::Event<std::string>::EventConnection helloStringLambdaConnection = helloStringEvent.addListener([](std::string s) { std::cout << std::format("This is from a lambda! It says: {}\n", s); });

	std::cout << "Added Listener to helloIntEvent\n\n";
	pulse::Event<int> helloIntEvent;
	helloIntEvent.addListener(helloInt);

	/*std::cout << "disconnect lambda connection\n";
	helloStringLambdaConnection.disconnect();*/

	std::cout << "Firing helloStringEvent\n";
	helloStringEvent.invoke("Hello World!");

	std::cout << "Firing helloIntEvent\n";
	helloIntEvent.invoke(42069);

	std::cout << "\n\n";
	std::cout << "-------------------------message_bus tests-------------------------\n";



	return 0;
}
