#pragma once
#include "fwd.h"
#include <boost/shared_ptr.hpp>
#include <future>
class IConnector {
public:
	virtual std::future<ICallerPtr> ConnectToExecutor() = 0;
};