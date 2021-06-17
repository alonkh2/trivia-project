#include "CommunicationException.h"

#include <utility>


CommunicationException::CommunicationException(std::string message, Byte status): m_message(std::move(message)), m_status(status)
{
}

char const* CommunicationException::what() const
{
	return m_message.c_str();
}

Byte CommunicationException::getStatus() const noexcept
{
	return m_status;
}
