#pragma once
#include <string>
#include "Utils.h"
#include <boost/function.hpp>
class IExecutor {
	virtual void AddTaskHandler(const std::wstring& TaskName, eExecutionPolicy policy, 
		boost::function<void (const std::vector<char>&, TaskResponse&)> handler) = 0;
};