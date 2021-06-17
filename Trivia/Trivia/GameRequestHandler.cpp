#include "GameRequestHandler.h"

#include <utility>


GameRequestHandler::GameRequestHandler(Game& game, LoggedUser user, GameManager& gameManager,
                                       RequestHandlerFactory& handlerFactory): m_game(game), m_user(std::move(user)), m_gameManager(gameManager), m_handlerFactory(handlerFactory)
{
}

/**
 * \brief Checks if a request is relevant.
 * \param info The request's info.
 * \return True if the request is relevant, else false.
 */
bool GameRequestHandler::isRequestRelevant(const RequestInfo& info)
{
	return info.id >= LG_CD && info.id <= GG_CD;
}

/**
 * \brief Calls the correct function to handle the request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult GameRequestHandler::handleRequest(const RequestInfo& info)
{
	switch (info.id)
	{
	case LG_CD:
		return leaveGame(info);
	case GQ_CD:
		return getQuestion(info);
	case SA_CD:
		return submitAnswer(info);
	case GG_CD:
		return getGameResults(info);
	default:
		return RequestResult{};
	}
}

/**
 * \brief Handles a leaveGame request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult GameRequestHandler::leaveGame(const RequestInfo& info) const
{
	RequestResult rr;
	LeaveGameResponse lg;
	rr.newHandler = m_handlerFactory.createMenuRequestHandler(m_user.getUsername());

	try
	{
		const auto data = m_game.removeUser(m_user);
		m_gameManager.updateScore(data);
		lg.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(lg);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		rr.newHandler = m_handlerFactory.createGameRequestHandler(m_game, m_user);
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << std::endl;
		rr.newHandler = nullptr;
	}
	return rr;
}

/**
 * \brief Handles a getQuestion request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult GameRequestHandler::getQuestion(const RequestInfo& info) const
{
	GetQuestionResponse gq;
	RequestResult rr;
	rr.newHandler = m_handlerFactory.createGameRequestHandler(m_game, m_user);
	
	try
	{
		const auto question = m_game.getQuestionForUser(m_user);
		gq.question = question.getQuestion();
		for (auto i = 0; i < question.getPossibleAnswers().size(); ++i)
		{
			gq.answers[i] = question.getPossibleAnswers()[i];
		}
		
		gq.status.push_back('1');
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gq);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();
		
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}
	return rr;
}

/**
 * \brief Handles a submitAnswer request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult GameRequestHandler::submitAnswer(const RequestInfo& info) const
{
	SubmitAnswerResponse sa;
	RequestResult rr;
	rr.newHandler = m_handlerFactory.createGameRequestHandler(m_game, m_user);
	
	try
	{
		const auto data = JsonResponsePacketDeserializer::deserializeSubmitAnswerRequest(info.buffer);
		sa.correctAnswer = m_game.submitAnswer(m_user, data.answer);
		sa.status.push_back('1');
		
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(sa);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();

		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}
	return rr;
}


/**
 * \brief Handles a getGameResults request.
 * \param info The request's info.
 * \return The request's result.
 */
RequestResult GameRequestHandler::getGameResults(const RequestInfo& info) const
{
	GetGameResultsResponse gr;
	RequestResult rr;
	rr.newHandler = m_handlerFactory.createGameRequestHandler(m_game, m_user);
	
	try
	{
		gr.results = m_game.getResults();
		gr.status.push_back('1');
		
		rr.buffer = JsonResponsePacketSerializer::serializeResponse(gr);
	}
	catch (CommunicationException& e)
	{
		ErrorResponse er;
		er.message = e.what();

		rr.buffer = JsonResponsePacketSerializer::serializeResponse(er);
	}
	catch (std::exception& e)
	{
		rr.newHandler = nullptr;
		std::cout << e.what() << std::endl;
	}
	return rr;
}
 