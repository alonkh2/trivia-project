#pragma once

#include <exception>
#include <string>
#include "constants.h"

class CommunicationException : public std::exception
{
public:
	CommunicationException(const std::string& message, Byte status);
	char const* what() const override;
	Byte getStatus() const noexcept;

private:
	std::string m_message;
	Byte m_status;
	
};
