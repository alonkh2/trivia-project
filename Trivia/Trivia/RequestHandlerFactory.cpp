#include "RequestHandlerFactory.h"


/**
 * \brief Creates a new login handler.
 * \return A new login handler.
 */
LoginRequestHandler RequestHandlerFactory::createLoginRequestHandler()
{
	return {*this, m_loginManager};
}

RequestHandlerFactory::RequestHandlerFactory(IDatabase& db) : m_database(db),
                                                              m_loginManager(LoginManager::getInstance<IDatabase&>(db))
{
}
