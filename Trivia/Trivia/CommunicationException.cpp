#include "CommunicationException.h"


CommunicationException::CommunicationException(const std::string& message, Byte status): m_status(status)
{
	m_message = "Login/signup Exception - " + message;
}

char const* CommunicationException::what() const
{
	return m_message.c_str();
}

Byte CommunicationException::getStatus() const noexcept
{
	return m_status;
}
