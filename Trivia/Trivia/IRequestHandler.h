#pragma once
#include <vector>

typedef struct RequestInfo
{
	unsigned id;
	time_t recievalTime;
	std::vector<Byte> buffer;
};

class IRequestHandler
{
	
};