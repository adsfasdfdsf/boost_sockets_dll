#include "pch.h"
#include "CExecutor.h"

void CExecutor::AddTaskHandler(const std::wstring& TaskName, eExecutionPolicy policy, 
	boost::function<void(const std::vector<char>&, TaskResponse&)> handler)
{
	Task task{ TaskName, handler, policy };
	_tasks.insert(task);
}

CExecutorPtr CExecutor::Instance(const std::wstring& ExecName)
{
	return CExecutorPtr(new CExecutor(ExecName));
}

bool CExecutor::Proccess(const TaskRequest& task_request, TaskResponse& task_response)
{
	task_response.res_state = ResState::Undefined;
	return true;
	// ����� ������ ���� � tasks ���� ��� �� return false;
	//���� ���� �� � ����� �� exec policy ��������� � main thread ��� worker thread
	// ���� working thread �� ������ �������  ���� main thread �� � ������ 
}

CExecutor::CExecutor(const std::wstring& ExecName) : _exec_name(ExecName)
{

}

