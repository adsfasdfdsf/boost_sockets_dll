#include "pch.h"
#include "CCaller.h"
#include "CMessenger.h"
#include <boost/bind.hpp>
#include <memory>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include "CSession.h"
CCaller::CCaller(boost::asio::io_context& io, const boost::uuids::uuid& uuid): _io(io), _uuid(uuid)
{
}

void CCaller::OnResponseReceived(const CMessagePtr& msg)
{
	// TODO deserialization vector<char> -> TaskResponse
	boost::unique_lock<boost::mutex> lock(_mutex);
	TaskResponse response;
	auto iter = _active_sessions.find(response.uuid);
	auto end = _active_sessions.end();
	CSessionPtr obj;
	if (iter != end) {
		obj = iter->second;
	}
	lock.unlock();
	obj->onResponseReceived(response);
	lock.lock();
	_active_sessions.erase(response.uuid);
}

void CCaller::OnErrorReceived(const boost::system::error_code& ec)
{

}

ICallerPtr CCaller::Instance(boost::asio::io_context& io, const boost::uuids::uuid& uuid)
{
	return ICallerPtr(new CCaller(io, uuid));
}

boost::signals2::scoped_connection CCaller::Init(const SocketPtr& _sock, const boost::function<void(const boost::system::error_code&)>& on_error)
{
	_messenger_ptr = CMessenger::Instance(_io, on_error, boost::bind(&CCaller::OnResponseReceived, this, _1));
	_messenger_ptr->Run(_sock);
	return _on_error.connect(on_error);
}

std::future<TaskResponse> CCaller::Call(const TaskRequest& request)
{
	boost::lock_guard<boost::mutex> lock(_mutex);
	auto promise = std::make_shared<std::promise<TaskResponse>>(new std::promise<TaskResponse>());
	if (request.uuid.is_nil()) {
		boost::uuids::random_generator gen;
		boost::uuids::uuid uuid = gen();
		const_cast<TaskRequest&>(request).uuid = uuid;
	}
	_active_sessions[request.uuid] = CSession::Instance(request, _messenger_ptr, promise);
	return promise->get_future();
}
