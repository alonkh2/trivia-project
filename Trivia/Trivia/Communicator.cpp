#include "Communicator.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory): m_serverSocket(0), m_handlerFactory(handlerFactory)
{
	
}


void Communicator::startHandleRequests()
{
	
	bindAndListen();
}

void Communicator::bindAndListen()
{
	struct sockaddr_in sa = {0};

	m_serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_serverSocket == INVALID_SOCKET)
	{
		throw std::exception(__FUNCTION__ " - socket");
	}

	sa.sin_port = htons(DEF_PORT); // port that server will listen for
	sa.sin_family = AF_INET; // must be AF_INET
	sa.sin_addr.s_addr = INADDR_ANY; // when there are few ip's for the machine. We will use always "INADDR_ANY"

	// again stepping out to the global namespace
	// Connects between the socket and the configuration (port and etc..)
	if (bind(m_serverSocket, reinterpret_cast<sockaddr*>(&sa), sizeof(sa)) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - bind");

	// Start listening for incoming requests of clients
	if (listen(m_serverSocket, SOMAXCONN) == SOCKET_ERROR)
		throw std::exception(__FUNCTION__ " - listen");
	std::cout << "Listening on port " << DEF_PORT << std::endl;

	while (true)
	{
		const auto client_socket = ::accept(m_serverSocket, nullptr, nullptr);

		if (client_socket == INVALID_SOCKET)
			throw std::exception(__FUNCTION__);

		// Have to add the option to create login handler here

		std::thread t([=] { handleNewClient(client_socket); });
		t.detach();
	}
}

void Communicator::handleNewClient(SOCKET client) const
{
	const std::string message = "HELLO";
	const auto* data = message.c_str();

	if (send(client, data, message.size(), 0) == INVALID_SOCKET)
	{
		throw std::exception("Error while sending message to client");
	}
}
