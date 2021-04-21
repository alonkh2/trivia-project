#pragma once
#include <vector>
#include "constants.h"

class IRequestHandler;

typedef struct RequestInfo
{
	unsigned id;
	time_t receivalTime;
	std::vector<Byte> buffer;
} RequestInfo;


typedef struct RequestResult
{
	std::vector<Byte> buffer;
	IRequestHandler* newHandler;
} RequestResult;

class IRequestHandler
{
public:
	virtual bool isRequestRelevant(const RequestInfo& info) = 0;
	virtual RequestResult handleRequest(const RequestInfo& info) = 0;
};