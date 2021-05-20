#include "Communicator.h"


#include "JsonResponsePacketSerializer.h"
#include "LoginRequestHandler.h"


Communicator::Communicator(RequestHandlerFactory& handlerFactory): m_serverSocket(0), m_handlerFactory(handlerFactory)
{
	
}


Communicator::~Communicator()
{
	try
	{
		for (const auto &client : m_clients)
		{
			delete client.second;
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

		LoginRequestHandler *req = m_handlerFactory.createLoginRequestHandler();

		std::lock_guard<std::mutex> lock(m_clientMutex);
		m_clients.insert_or_assign(client_socket, req);

		std::thread t([=] { handleNewClient(client_socket); });
		t.detach();
	}
}

/**
 * \brief Handles a new client. Doesn't do much for now, will do more later.
 * \param client The new client.
 */
void Communicator::handleNewClient(SOCKET client)
{
	std::unique_lock<std::mutex> lock(m_clientMutex, std::defer_lock);
	lock.lock();
	auto* requestHandler = m_clients.at(client);
	lock.unlock();
	try
	{
		char* code = nullptr, * length = nullptr;
		
		while (true)
		{
			
			code = receive(client, sizeof(Byte));
			length = receive(client, sizeof(int));
			
			if (code == nullptr || length == nullptr)
			{
				throw std::exception(std::string("Data received not according to protocol! " + std::to_string(client)).c_str());
			}

			const auto numericalLength = *reinterpret_cast<int*>(length);

			auto* data = receive(client, numericalLength);

			RequestInfo info;
			info.id = *reinterpret_cast<Byte*>(code);
			time(&info.receivalTime);
			for (int i = 0; i < numericalLength; ++i)
			{
				info.buffer.push_back(data[i]);
			}

			delete code;
			delete length;
			delete data;

			if (requestHandler->isRequestRelevant(info))
			{
				const auto result = requestHandler->handleRequest(info);

				if (result.newHandler != nullptr)
				{
					delete requestHandler;
					requestHandler = result.newHandler;
				}
				
				sendall(client, result.buffer);
			}
			else
			{
				ErrorResponse error;
				error.message = "Error with login/signup attempt" + std::to_string(client);
				sendall(client, JsonResponsePacketSerializer::serializeResponse(error));
			}
		}
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		closesocket(client);
		lock.lock();
		m_clients.erase(client);
		lock.unlock();
	}
}

/**
 * \brief Sends a message via a socket.
 * \param socket The socket to send to.
 * \param msg The message to send.
 */
void Communicator::sendall(SOCKET socket, const std::vector<Byte>& msg) const
{
	auto* toSend = new char[msg.size() + 1];
	for (auto i = 0; i < msg.size(); ++i)
	{
		toSend[i] = msg[i];
	}

	const auto res = send(socket, toSend, msg.size(), 0);

	delete toSend;
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

	if (res == 0)
	{
		throw std::exception("Client disconnected");
	}

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
