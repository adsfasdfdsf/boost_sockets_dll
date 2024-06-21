#include "pch.h"
#include "CProvider.h"
#include "Module.h"
#include "CRegistrar.h"
#include "CConnector.h"

CSTMODULE_API IProvider& GetProvider() {
	static CProvider prov;
	return prov;
}

IConnectorPtr CProvider::getConnector(const std::wstring& ip, unsigned short port, const std::wstring& executor_name)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	boost::uuids::random_generator gen;
	boost::uuids::uuid uuid = gen();
	auto con = CConnector::Instance(ip, port, executor_name);
	_connections[uuid] = con;
	return con;
}

IRegistrar& CProvider::getRegistrar()
{
	static CRegistrar reg(GetCurrentThreadId());
	return reg;
}
