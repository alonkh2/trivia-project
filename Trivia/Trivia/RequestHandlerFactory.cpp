#include "RequestHandlerFactory.h"


/**
 * \brief Creates a new login handler.
 * \return A new login handler.
 */
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this, m_loginManager);
}

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

LoginManager& RequestHandlerFactory::getLoginManager() const
{
	return m_loginManager;
}

RoomManager& RequestHandlerFactory::getRoomManager() const
{
	return m_roomManager;
}

StatisticsManager& RequestHandlerFactory::getStatisticsManager() const
{
	return m_statisticsManager;
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase& db) : m_database(db),
                                                              m_loginManager(LoginManager::getInstance<IDatabase&>(db)),
                                                              m_roomManager(RoomManager::getInstance()),
                                                              m_statisticsManager(
	                                                              StatisticsManager::getInstance<IDatabase&>(db))
{
}
