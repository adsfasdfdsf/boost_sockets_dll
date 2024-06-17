#pragma once
#include "executor.h"
#include "fwd.h"
#include <unordered_set>
#include <string>
class CExecutor : public IExecutor
{
public:
	virtual void AddTaskHandler(const std::wstring& TaskName, eExecutionPolicy policy,
		boost::function<void(const std::vector<char>&, TaskResponse&)> handler) override;
	static CExecutorPtr Instance(const std::wstring& ExecName);
	bool Proccess(const TaskRequest& task_request, TaskResponse& task_response);
private:
	struct Task {
		std::wstring _name;
		boost::function<void (const std::vector<char>&, TaskResponse&)> _func;
		eExecutionPolicy _policy;
		struct hash {
			size_t operator() (const Task& task) const{
				return std::hash<std::wstring>{}(task._name);
			}
		};
		bool operator== (const Task& task) const {
			return _name == task._name;
		}
	};
	CExecutor(const std::wstring& ExecName);
private:
	std::wstring _exec_name;
	std::unordered_set<Task, Task::hash> _tasks;
};

