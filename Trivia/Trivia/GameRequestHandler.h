#pragma once

#include "Game.h"
#include "IRequestHandler.h"
#include "GameManager.h"
#include "RequestHandlerFactory.h"

class RequestHandlerFactory;

class GameRequestHandler : public IRequestHandler
{
public:
	GameRequestHandler(Game& game, LoggedUser user, GameManager& gameManager, RequestHandlerFactory& handlerFactory);
	
	bool isRequestRelevant(const RequestInfo& info) override;
	RequestResult handleRequest(const RequestInfo& info) override;

private:
	RequestResult getQuestion(const RequestInfo& info) const;
	RequestResult submitAnswer(const RequestInfo& info) const;
	RequestResult getGameResults(const RequestInfo& info) const;
	RequestResult leaveGame(const RequestInfo& info) const;

	Game& m_game;
	LoggedUser m_user;
	GameManager& m_gameManager;
	RequestHandlerFactory& m_handlerFactory;
};