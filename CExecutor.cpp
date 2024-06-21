#include "pch.h"
#include "CExecutor.h"

void CExecutor::AddTaskHandler(const std::wstring& TaskName, eExecutionPolicy policy, 
	boost::function<void(const std::vector<char>&, TaskResponse&)> handler)
{
	Task task{ TaskName, handler, policy };
	_tasks.insert(task);
}

CExecutorPtr CExecutor::Instance(const std::wstring& ExecName, DWORD main_thread_id)
{
	return CExecutorPtr(new CExecutor(ExecName, main_thread_id));
}

bool CExecutor::Proccess(const TaskRequest& task_request, TaskResponse& task_response)
{
	task_response.res_state = ResState::Undefined;
	auto task = _tasks.find(CExecutor::Task({ task_request.task_name }));
	if (task == _tasks.end()) {
		return false;
	}
	if (task->_policy == eExecutionPolicy::MainThread) {
		execute_in_thread(_main_thread_id, [&task, &task_request, &task_response]() {task->_func(task_request.data, task_response); });
		return true;
	}
	task->_func(task_request.data, task_response);
	return true;
}

CExecutor::CExecutor(const std::wstring& ExecName, DWORD main_thread_id) : _exec_name(ExecName), _main_thread_id(main_thread_id)
{
}

