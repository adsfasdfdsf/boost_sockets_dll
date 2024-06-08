#pragma once
#include "Utils.h"
#include <future>
class CSession
{
public:
	CSessionPtr Instance(const TaskRequest& request, const CMessengerPtr& messenger_ptr, const std::shared_ptr<std::promise<TaskResponse>>& response);
	void SendRequest();
	void onResponseReceived(const TaskResponse& msg);
private:
	CSession(const TaskRequest& request, const CMessengerPtr& messenger_ptr, const std::shared_ptr<std::promise<TaskResponse>>& response);
private:
	TaskRequest _request;
	CMessengerPtr _messenger_ptr;
	std::shared_ptr<std::promise<TaskResponse>> _response;
};

