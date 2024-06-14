#include "CService.h"
#include "pch.h"
#include "Utils.h"
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
	getProvider
}
