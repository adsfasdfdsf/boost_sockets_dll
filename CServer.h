#pragma once
#include "fwd.h"
#include <boost/shared_ptr.hpp>
#include <boost/thread.hpp>

class CRemoteConnectionManager {
public:
	static CRemoteConnectionManagerPtr Instance(const std::wstring& executor_name);
	void StartAcceptingRemoteConnections(unsigned short port);
	void StartAcceptingRemoteConnections();
	void StopAcceptingRemoteConnections();
	void RunPolling();
	unsigned short GetOpenedPort();
private:
	CRemoteConnectionManager(const std::wstring& executor_name);
private:
	const std::wstring& _executor_name;
	boost::asio::io_context _io;
	std::unique_ptr<boost::asio::io_context::work> _work_ptr;
	std::unique_ptr<CAcceptor> _acceptor_ptr;
	std::vector<boost::shared_ptr<boost::thread>> _thread_pool;
};


class CAcceptor {
private:
	CAcceptor(boost::asio::io_context& io, unsigned short port, const std::wstring& executor_name);
	void InitAccept();
	void OnAccept(const boost::system::error_code& ec, const boost::asio::ip::tcp::socket& sock);
public:
	static std::unique_ptr<CAcceptor> Instance(boost::asio::io_context& io, unsigned short port, const std::wstring& executor_name);
	void Start();
	void Restart();
	void Stop();
	unsigned short GetOpenedPort();
private:
	boost::asio::io_context& _io;
	unsigned short _port;
	const std::wstring& _executor_name;
	boost::asio::ip::tcp::acceptor _acceptor;
	boost::mutex _mutex;
	std::atomic<bool> _is_stopped;
	std::vector<CServicePtr> _active_services;
};