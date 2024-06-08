#include "pch.h"
#include "CRegistrar.h"
#include "CExecutor.h"
#include "CServer.h"
IExecutorPtr CRegistrar::RegisterExecutor(const std::wstring& ExecName)
{
    auto iter = _executors.find(ExecName);
    if (iter != _executors.end()) {
        return iter->second;
    }
    auto exec = CExecutor::Instance(ExecName);
    _executors[ExecName] = exec;
    _servers[ExecName] = CRemoteConnectionManager::Instance(ExecName);
    return exec;
}

void CRegistrar::UnRegisterExecutor(const std::wstring& ExecName)
{
    auto obj = _servers[ExecName];
    if (!obj) {
        return;
    }
    obj->StopAcceptingRemoteConnections();
    _servers.erase(ExecName);
    _executors.erase(ExecName);
}

IExecutorPtr CRegistrar::GetExecutor(const std::wstring& ExecName)
{
    auto obj = _executors[ExecName];
    if (!obj) {
        return {};
    }
    return obj;
}

void CRegistrar::AllowRemoteExecution(const std::wstring& ExecName, unsigned short port)
{
    auto obj = _servers[ExecName];
    if (!obj) {
        return;
    }
    obj->StartAcceptingRemoteConnections(port);
}

unsigned short CRegistrar::AllowRemoteExecution(const std::wstring& ExecName)
{
    auto obj = _servers[ExecName];
    if (!obj) {
        return;
    }
    obj->StartAcceptingRemoteConnections();
    return obj->GetOpenedPort();
}

void CRegistrar::DenyRemoteExecution(const std::wstring& ExecName, unsigned short port)
{
    auto obj = _servers[ExecName];
    if (!obj) {
        return;
    }
    obj->StopAcceptingRemoteConnections();
}

void CRegistrar::RunPolling(const std::wstring& ExecName)
{
    auto obj = _servers[ExecName];
    if (!obj) {
        return;
    }
    obj->RunPolling();
}
