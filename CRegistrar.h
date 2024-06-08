#pragma once
#include "registrar.h"
#include <unordered_map>
#include "fwd.h"
class CRegistrar : public IRegistrar
{
public:
	virtual IExecutorPtr RegisterExecutor(const std::wstring& ExecName) override;
	virtual void UnRegisterExecutor(const std::wstring& ExecName) override;
	virtual IExecutorPtr GetExecutor(const std::wstring& ExecName) override;
	virtual void AllowRemoteExecution(const std::wstring& ExecName, unsigned short port) override;
	virtual unsigned short AllowRemoteExecution(const std::wstring& ExecName) override;
	virtual void DenyRemoteExecution(const std::wstring& ExecName, unsigned short port) override;
	virtual void RunPolling(const std::wstring& ExecName) override;

private:
	std::unordered_map<std::wstring, CExecutorPtr> _executors;
	std::unordered_map<std::wstring, CRemoteConnectionManagerPtr> _servers;
	std::wstring _ip;
	unsigned short _port;
};