#include "pch.h"
#include "CSession.h"
#include "CMessenger.h"
#include "fwd.h"
CSessionPtr CSession::Instance(const TaskRequest& request, const CMessengerPtr& messenger_ptr, const std::shared_ptr<std::promise<TaskResponse>>& response)
{
	return CSessionPtr(new CSession(request, messenger_ptr, response));
}

void CSession::SendRequest()
{
	_messenger_ptr->AsyncSend(CMessage::Instance(packTaskData<TaskRequest>(_request), CMessage::TaskProccess));
}

void CSession::onResponseReceived(const TaskResponse& resp)
{
	_response->set_value(resp);
}

CSession::CSession(const TaskRequest& request, const CMessengerPtr& messenger_ptr, const std::shared_ptr<std::promise<TaskResponse>>& response):
	_request(request), _messenger_ptr(messenger_ptr), _response(response)
{
}

