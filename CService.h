#pragma once
#include "fwd.h"
#include "CMessage.h"

class CService 
{
public:
	static CServicePtr Instance(const CMessengerPtr& messenger_ptr, const std::wstring& executor_name);
private:
	CService(const CMessengerPtr& messenger_ptr, const std::wstring& executor_name);
	void OnErrorReceived(const boost::system::error_code& ec);
	void OnRequestReceived(const CMessagePtr& msg_ptr);
private:
	CMessage::Header _header;
	std::vector<char> _buffer;
	std::wstring _executor_name;
	CMessengerPtr _messenger_ptr;
};