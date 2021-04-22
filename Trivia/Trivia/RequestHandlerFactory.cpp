#include "RequestHandlerFactory.h"


/**
 * \brief Creates a new login handler.
 * \return A new login handler.
 */
LoginRequestHandler* RequestHandlerFactory::createLoginRequestHandler()
{
	return new LoginRequestHandler(*this, m_loginManager);
}

MenuRequestHandler* RequestHandlerFactory::createMenuRequestHandler()
{
	return nullptr;
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase& db) : m_database(db),
                                                              m_loginManager(LoginManager::getInstance<IDatabase&>(db))
{
}
