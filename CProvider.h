#pragma once
#include "provider.h"
#include "unordered_map"
#include "boost/uuid/uuid.hpp"
#include <boost/thread/mutex.hpp>
class CProvider : public IProvider
{
public:
	virtual IConnectorPtr getConnector(const std::wstring& ip, unsigned short port, const std::wstring& executor_name) override;
	virtual IRegistrar& getRegistrar() override;
private:
	std::unordered_map<boost::uuids::uuid, IConnectorPtr, boost::hash<boost::uuids::uuid>> _connections;
	boost::mutex _mutex;
};

