#pragma once
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <sstream>
#include <vector>
#include <boost/uuid/uuid.hpp>
#include <iostream>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/lexical_cast.hpp>
// #pragma comment(lib, "bcrypt.lib") if error caused
enum ResState {
	Completed,
	Aborted,
	Undefined
};

struct TaskResponse {
	boost::uuids::uuid uuid;
	std::wstring task_name;
	std::vector<char> data;
	ResState res_state;
};
struct TaskRequest {
	boost::uuids::uuid uuid;
	std::wstring task_name;
	std::vector<char> data;
	ResState res_state;
};

BOOST_SERIALIZATION_SPLIT_FREE(TaskRequest);
BOOST_SERIALIZATION_SPLIT_FREE(TaskResponse);
template <typename Archive>
void save(Archive& ar, const TaskResponse& response, const unsigned int version)
{
	std::string uid = boost::lexical_cast<std::string>(response.uuid);
	std::wstring strin(uid.begin(), uid.end());
	ar& strin;
	ar& response.task_name;
	ar& response.data;
	ar& response.res_state;
}

template <typename Archive>
void load(Archive& ar, TaskResponse& response, const unsigned int version)
{
	std::wstring strin;
	ar& strin;
	response.uuid = boost::lexical_cast<boost::uuids::uuid>(strin);
	ar& response.task_name;
	ar& response.data;
	ar& response.res_state;
}

template <typename Archive>
void save(Archive& ar, const TaskRequest& request, const unsigned int version)
{
	std::string uid = boost::lexical_cast<std::string>(request.uuid);
	std::wstring strin(uid.begin(), uid.end());
	ar& strin;
	ar& request.task_name;
	ar& request.data;
}

template <typename Archive>
void load(Archive& ar, TaskRequest& request, const unsigned int version)
{
	std::wstring strin;
	ar& strin;
	request.uuid = boost::lexical_cast<boost::uuids::uuid>(strin);
	ar& request.task_name;
	ar& request.data;
}

template <typename T>
std::vector<char> packTaskData(const T& td) {
	std::ostringstream oss;
	boost::archive::text_oarchive oa(oss);
	oa << td;
	const std::string& str = oss.str();
	return std::vector<char>(str.begin(), str.end());
}

template <typename T>
T unpackTaskData(const std::vector<char>& v) {
	std::string str(v.begin(), v.end());
	std::istringstream iss(str);
	boost::archive::text_iarchive ia(iss);
	T td;
	ia >> td;
	return td;
}

enum eExecutionPolicy
{
    MainThread,
    WorkerThread
};