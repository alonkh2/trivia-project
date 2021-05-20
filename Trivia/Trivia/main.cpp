#include <iostream>

#include "WSAInitializer.h"
#include "Server.h"

int main()
{
	try
	{
		WSAInitializer wsa;
		Server& s = Server::getInstance();
		s.run();
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	
	return 0;
}
