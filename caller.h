#pragma once
#include <boost/shared_ptr.hpp>
#include <future>
#include "Utils.h"
#include <boost/signals2/connection.hpp>
#include <boost/function.hpp>
class ICaller {
	virtual std::future<TaskResponse> Call(const TaskRequest& request) = 0;
	virtual boost::signals2::scoped_connection SubscribeOnConnectionLoss(const boost::function<void()>& on_disconnect) = 0;
};