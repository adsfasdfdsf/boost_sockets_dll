#include "pch.h"
#include "CExecutor.h"

CExecutorPtr CExecutor::Instance(const std::wstring& ExecName)
{
	return CExecutorPtr(new CExecutor(ExecName));
}

CExecutor::CExecutor(const std::wstring& ExecName) : _exec_name(ExecName)
{
}

