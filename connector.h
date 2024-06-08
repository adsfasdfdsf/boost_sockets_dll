#pragma once
#include <boost/shared_ptr.hpp>
#include <future>
class IConnector {
	virtual std::future<ICallerPtr> ConnectToExecutor() = 0;
};