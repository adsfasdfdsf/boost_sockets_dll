#include "CService.h"
#include "pch.h"
#include "Utils.h"
#include "Module.h"
#include "CMessage.h"
#include "CExecutor.h"
#include "CMessenger.h"
CServicePtr CService::Instance(const CMessengerPtr& messenger_ptr, const std::wstring& executor_name)
{
	return CServicePtr(new CService(messenger_ptr, executor_name));
}

CService::CService(const CMessengerPtr& messenger_ptr, const std::wstring& executor_name) : _messenger_ptr(messenger_ptr),
																							_executor_name(executor_name)
{
}

void CService::OnErrorReceived(const boost::system::error_code& ec)
{
	
}

void CService::OnRequestReceived(const CMessagePtr& msg_ptr)
{
	//auto executor = GetProvider().GetRegistrar().GetExecutor(_executor_name);
	CExecutorPtr executor;
	if (!executor) {
		return;
	}
	auto task_request = unpackTaskData<TaskRequest>(msg_ptr->GetBufferData());
	switch (msg_ptr->GetHeader()._action)
	{
	case CMessage::eAction::NoAction:{
		
	}
		break;
	case CMessage::eAction::TaskProccess:{
		TaskResponse task_response;
		executor->Proccess(task_request, task_response);
		CMessagePtr msg_response = CMessage::Instance(packTaskData<TaskResponse>(task_response), CMessage::eAction::TaskProccess);
		_messenger_ptr->AsyncSend(msg_response);
	}
		break;
	}
}
