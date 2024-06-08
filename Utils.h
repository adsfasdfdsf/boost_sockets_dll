#pragma once
#include <string>
#include <vector>
#include <boost/uuid/uuid.hpp>
struct TaskResponse {
	boost::uuids::uuid uuid;
	std::wstring TaskName;
	std::vector<char> data;
	enum ResState {
		Completed,
		Aborted, 
		Undefined
	};
	//todo serialization
};
struct TaskRequest {
	boost::uuids::uuid uuid;
	std::wstring TaskName;
	std::vector<char> data;
	//todo serialization
};

enum eExecutionPolicy
{
    MainThread,
    WorkerThread
};