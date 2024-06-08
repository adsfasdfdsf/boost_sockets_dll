#pragma once
#include <boost/shared_ptr.hpp>
#include "connector.h"
#include "registrar.h"
#include <string>
class IProvider {
	virtual IConnectorPtr getConnector(const std::wstring& ip, unsigned short port, const std::wstring& executor_name) = 0;
	virtual IRegistrar& getRegistrar() = 0;
};
