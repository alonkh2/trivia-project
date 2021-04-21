#include "LoginException.h"


LoginException::LoginException(const std::string& message, Byte status): m_status(status)
{
	m_message = "Login Exception - " + message;
}

char const* LoginException::what() const
{
	return m_message.c_str();
}

Byte LoginException::getStatus() const noexcept
{
	return m_status;
}
