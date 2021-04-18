#include "Communicator.h"

#include "LoginRequestHandler.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory): m_serverSocket(0), m_handlerFactory(handlerFactory)
{
	
}


Communicator::~Communicator()
{
	try
	{
		for (const auto client : m_clients)
		{
			closesocket(client.first);
		}
		closesocket(m_serverSocket);
	}
	catch (...)
	{
	}
}

/**
 * \brief Runs the server.
 */
void Communicator::startHandleRequests()
{
	
	bindAndListen();
}

/**
 * \brief Binds the server to a port and starts listening for new connections.
 */
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

		LoginRequestHandler req = m_handlerFactory.createLoginRequestHandler();
		m_clients.insert_or_assign(client_socket, &req);

		std::thread t([=] { handleNewClient(client_socket); });
		t.detach();
	}
}

/**
 * \brief Handles a new client. Doesn't do much for now, will do more later.
 * \param client The new client.
 */
void Communicator::handleNewClient(SOCKET client) const
{
	const std::string message = "HELLO";
	sendall(client, message);
	auto* ans = receive(client, message.size());
	std::cout << ans << std::endl;
	delete ans;
}

/**
 * \brief Sends a message via a socket.
 * \param socket The socket to send to.
 * \param msg The message to send.
 */
void Communicator::sendall(SOCKET socket, const std::string& msg) const
{
	const auto* toSend = msg.c_str();

	const auto res = send(socket, toSend, msg.size(), 0);

	if (res == INVALID_SOCKET || res == SOCKET_ERROR || !res)
	{
		std::string error = "Error while sending message to client: ";
		error += std::to_string(socket);
		throw std::exception(error.c_str());
	}
}

/**
 * \brief Receives a message from a socket.
 * \param socket The socket to receive from.
 * \param numOfBytes The number of bytes to receive.
 * \param flags Operation flags.
 * \return The received message.
 */
char* Communicator::receive(SOCKET socket, int numOfBytes, int flags) const
{
	if (numOfBytes == 0)
	{
		return (char*)"";
	}

	char* data = new char[numOfBytes + 1];
	int res = recv(socket, data, numOfBytes, flags);

	if (res == INVALID_SOCKET)
	{
		std::string s = "Error while receiving from socket: ";
		s += std::to_string(socket);
		throw std::exception(s.c_str());
	}

	if (numOfBytes < strlen(data))
	{
		data[numOfBytes] = 0;
	}
	return data;
}
