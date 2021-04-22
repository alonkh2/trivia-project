#pragma once

#include <exception>
#include <string>
#include "constants.h"

class LoginException : public std::exception
{
public:
	LoginException(const std::string& message, Byte status);
	char const* what() const override;
	Byte getStatus() const noexcept;

private:
	std::string m_message;
	Byte m_status;
	
};
