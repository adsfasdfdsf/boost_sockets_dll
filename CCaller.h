#pragma once
#include "caller.h"
#include <boost/function.hpp>
#include <boost/asio.hpp>
#include <boost/signals2/signal.hpp>
#include <boost/uuid/uuid.hpp>
#include "fwd.h"
#include <boost/thread.hpp>
class CCaller : public ICaller
{
private:
	CCaller(boost::asio::io_context& io, const boost::uuids::uuid& uuid);
	void OnResponseReceived(const CMessagePtr& msg);
	void OnErrorReceived(const boost::system::error_code& ec);
public:
	static ICallerPtr Instance(boost::asio::io_context& io, const boost::uuids::uuid& uuid);
	boost::signals2::scoped_connection Init(const SocketPtr& _sock,
		const boost::function<void(const boost::system::error_code&)>& on_error);
	virtual std::future<TaskResponse> Call(const TaskRequest& request) override;
	virtual boost::signals2::scoped_connection SubscribeOnConnectionLoss(const boost::function<void()>& on_disconnect) override { return {}; };
private:
	CMessengerPtr _messenger_ptr;
	boost::uuids::uuid _uuid;
	boost::asio::io_context& _io;
	boost::signals2::signal<void(const boost::system::error_code&)> _on_error;
	std::unordered_map<boost::uuids::uuid, CSessionPtr, boost::hash<boost::uuids::uuid>> _active_sessions;
	boost::mutex _mutex;
};
