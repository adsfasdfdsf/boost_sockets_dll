#pragma once
#include "executor.h"

class CExecutor : public IExecutor
{
public:
	virtual void AddTaskHandler(const std::wstring& TaskName, eExecutionPolicy policy,
		boost::function<void(const std::vector<char>, TaskResponse&)> handler) override;
	static CExecutorPtr Instance(const std::wstring& ExecName);
private:
	CExecutor(const std::wstring& ExecName);
private:
	std::wstring _exec_name;
};

