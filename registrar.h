#pragma once
#include <boost/shared_ptr.hpp>
#include <string>
class IRegistrar {
public:
	virtual IExecutorPtr RegisterExecutor(const std::wstring& ExecName) = 0;
	virtual void UnRegisterExecutor(const std::wstring& ExecName) = 0;
	virtual IExecutorPtr GetExecutor(const std::wstring& ExecName) = 0;
	virtual unsigned short AllowRemoteExecution(const std::wstring& ExecName) = 0;
	virtual void AllowRemoteExecution(const std::wstring& ExecName, unsigned short port) = 0;
	virtual void DenyRemoteExecution(const std::wstring& ExecName, unsigned short port) = 0;
    virtual void RunPolling(const std::wstring& ExecName) = 0;
};