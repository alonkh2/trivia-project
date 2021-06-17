#include "RequestHandlerFactory.h"


/**
 * \brief Creates a new login handler.
 * \return A new login handler.
 */
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this, m_loginManager);
}

/**
 * \brief Creates a new menu handler.
 * \param username The user who's signed in.
 * \return A MenuRequestHandler.
 */
MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler(const std::string& username)
{
	for (const auto& user : m_loginManager.getLoggedUsers())
	{
		if (user.getUsername() == username)
		{
			return new MenuRequestHandler(user, *this);
		}
	}
	return nullptr;
}

/**
 * \brief Creates a new admin handler.
 * \param room The admin's room.
 * \param user The admin.
 * \return A RoomAdminRequestHandler.
 */
RoomAdminRequestHandler* RequestHandlerFactory::createRoomAdminRequestHandler(Room& room, const LoggedUser& user)
{
	return new RoomAdminRequestHandler(room, user, *this);
}

/**
 * \brief Creates a new member handler.
 * \param room The member's room.
 * \param user The member.
 * \return A RoomMemberRequestHandler.
 */
RoomMemberRequestHandler* RequestHandlerFactory::createRoomMemberRequestHandler(
	Room& room, const LoggedUser& user)
{
	return new RoomMemberRequestHandler(room, user, *this);
}

/**
 * \brief Creates a new game handler.
 * \param game The user's game.
 * \param user The user.
 * \return A GameRequestHandler.
 */
GameRequestHandler* RequestHandlerFactory::createGameRequestHandler(Game& game, const LoggedUser& user)
{
	return new GameRequestHandler(game, user, GameManager::getInstance<IDatabase&>(m_database), *this);
}

/**
 * \brief loginManager getter.
 * \return The login manager.
 */
LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return m_loginManager;
}

/**
 * \brief roomManager getter.
 * \return The room manager. 
 */
RoomManager& RequestHandlerFactory::getRoomManager() const
{
	return m_roomManager;
}

/**
 * \brief statisticsManager getter.
 * \return The statistics manager.
 */
StatisticsManager& RequestHandlerFactory::getStatisticsManager() const
{
	return m_statisticsManager;
}

/**
 * \brief gameManager getter.
 * \return the game manager.
 */
GameManager& RequestHandlerFactory::getGameManager() const
{
	return m_gameManager;
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase& db) : m_database(db),
                                                              m_loginManager(LoginManager::getInstance<IDatabase&>(db)),
                                                              m_roomManager(RoomManager::getInstance<IDatabase&>(db)),
                                                              m_statisticsManager(StatisticsManager::getInstance<IDatabase&>(db)),
                                                              m_gameManager(GameManager::getInstance<IDatabase&>(db))
{
}
