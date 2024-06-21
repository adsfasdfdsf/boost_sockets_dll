#pragma once
#include <boost/thread.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <deque>
#include <boost/function.hpp>
#include "CMessage.h"
#include <boost/asio/coroutine.hpp>
#include <boost/asio/write.hpp>
#include <boost/asio/read.hpp>
#include <boost/bind.hpp>
using error_handler = boost::function<void (const boost::system::error_code&)>;
using receive_handler = boost::function<void(const CMessagePtr&)>;

class CMessenger
{
public:
	//static CMessengerPtr Instance(boost::asio::io_context& io, 
	//	const error_handler& error_handle, const receive_handler& receive_handle);

	//static CMessengerPtr Instance(boost::asio::io_context& io);

	//void Run(SocketPtr sock);

	//void AsyncSend(const CMessagePtr& msg);

	//void SetReceiveHandler(const receive_handler& rh);

	//void SetErrorHandler(const error_handler& eh);
private:
//	void StartAsyncOperations();
//
//	void OnWrite(const boost::system::error_code& er, size_t size);
//
//	void OnRecieve(const boost::system::error_code& er, size_t size);
//
//	void OnError(const boost::system::error_code ec);
//	
//	void SendQueue();
//
//	boost::system::error_code AsyncReceive();

	CMessenger(boost::asio::io_context& io, 
			   const error_handler& error_handle, 
			   const receive_handler& receive_handle) : _io(io), 
														_error_handler(error_handle), 
														_receive_handler(receive_handle) {};

	CMessenger(boost::asio::io_context& io) : _io(io)
	{};


private:
	static boost::asio::const_buffers_1 const_message_header(const CMessagePtr& msg_ptr) {
		return boost::asio::buffer((const void*) &msg_ptr->GetHeader(), sizeof(CMessage::Header));
	}
	static boost::asio::const_buffers_1 const_message_body(const CMessagePtr& msg_ptr) {
		auto buf = msg_ptr->GetBuffer();
		return boost::asio::buffer((const void*)buf.first, buf.second);
	}
	
	static boost::asio::mutable_buffers_1 mutable_message_header(const CMessagePtr& msg_ptr) {
		return boost::asio::buffer((void*)&msg_ptr->GetHeader(), sizeof(CMessage::Header));
	}
	static boost::asio::mutable_buffers_1 mutable_message_body(const CMessagePtr& msg_ptr) {
		auto buf = msg_ptr->GetBuffer();
		return boost::asio::buffer(buf.first, buf.second);
	}
	SocketPtr _sock;
	boost::asio::io_context& _io;
	boost::mutex _mutex;
	std::deque<CMessagePtr> _send_queue;
	error_handler _error_handler;
	receive_handler _receive_handler;
	boost::asio::coroutine _send_coroutine;
	boost::asio::coroutine _receive_coroutine;
	CMessagePtr _message_ptr;
	bool _abort_connection = false;
	bool _write_in_progress = false;
	CMessagePtr _msg;

public:

static CMessengerPtr Instance(boost::asio::io_context& io, 
	const error_handler& error_handle, const receive_handler& receive_handle) {
	return CMessengerPtr(new CMessenger(io, error_handle, receive_handle));
}


static CMessengerPtr Instance(boost::asio::io_context& io) {
	return CMessengerPtr(new CMessenger(io));
}


void Run(SocketPtr sock) {
	_sock = sock;
	_send_coroutine = boost::asio::coroutine();
	_receive_coroutine = boost::asio::coroutine();
	StartAsyncOperations();
}


void StartAsyncOperations() {
	_ASSERT(_sock && _sock->is_open());
	SendQueue();
	_message_ptr = CMessage::Instance();
	AsyncReceive();
}


void OnWrite(const boost::system::error_code& er, size_t size) {
	boost::lock_guard<boost::mutex> lock(_mutex);
	if (_abort_connection) {
		return;
	}
	if (er) {
		_error_handler(er);
		return;
	}
	SendQueue();
}



void OnRecieve(const boost::system::error_code& er, size_t size) {
	boost::lock_guard<boost::mutex> lock(_mutex);
	if (_abort_connection) {
		return;
	}
	if (er) {
		_error_handler(er);
		return;
	}
	AsyncReceive();
}



void OnError(const boost::system::error_code ec) {
	_abort_connection = true;
	// if (ec != boost::asio::error::operation_aborted)
	if (!_error_handler.empty()) {
		_error_handler(ec);
	}
}


void SendQueue() {

	BOOST_ASIO_CORO_REENTER(_send_coroutine) while (!_abort_connection) {
		_write_in_progress = true;
		while (!_abort_connection && !_send_queue.empty()) {
			BOOST_ASIO_CORO_YIELD boost::asio::async_write(*_sock, const_message_header(_send_queue.front()), boost::bind(&CMessenger::OnWrite, this, _1, _2));
			if (!_abort_connection && _send_queue.front()->GetBuffer().second > 0) {
				BOOST_ASIO_CORO_YIELD boost::asio::async_write(*_sock, const_message_body(_send_queue.front()), boost::bind(&CMessenger::OnWrite, this, _1, _2));
			}
			_send_queue.pop_front();
		}
		_write_in_progress = false;
		if (!_abort_connection) {
			BOOST_ASIO_CORO_YIELD;
		}
	}
}


boost::system::error_code AsyncReceive() {
	BOOST_ASIO_CORO_REENTER(_receive_coroutine) while (!_abort_connection) {
		_msg = CMessage::Instance();
		BOOST_ASIO_CORO_YIELD boost::asio::async_read(*_sock, mutable_message_header(_msg), boost::bind(&CMessenger::OnRecieve, this, _1, _2));
		if (!_abort_connection && _msg->GetHeader()._body_size > 0) {
			BOOST_ASIO_CORO_YIELD boost::asio::async_read(*_sock, mutable_message_body(_msg), boost::bind(&CMessenger::OnRecieve, this, _1, _2));
			if (!_receive_handler.empty()) {
				_io.post(boost::bind(_receive_handler, _msg));
			}
		}
		else {
			return boost::system::error_code(boost::system::errc::bad_message, boost::system::generic_category());
		}
	}
	return {};

}


void AsyncSend(const CMessagePtr& msg) {
	if (!_abort_connection){
		msg->GetHeader()._body_size = msg->GetBuffer().second;
		_send_queue.push_back(msg);
		if (!_write_in_progress) {
			SendQueue();
		}
	}
}

};