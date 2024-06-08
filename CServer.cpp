#include "pch.h"
#include "CServer.h"
#include <boost/asio.hpp>
#include "port_selector.h"
CRemoteConnectionManagerPtr CRemoteConnectionManager::Instance(const std::wstring& executor_name)
{
	return CRemoteConnectionManagerPtr(new CRemoteConnectionManager(executor_name));
}
void CRemoteConnectionManager::StartAcceptingRemoteConnections(unsigned short port)
{
	if (!_io.stopped()) {
		_acceptor_ptr = CAcceptor::Instance(_io, port, _executor_name);
		_acceptor_ptr->Start();
		for (auto i = 0; i < std::thread::hardware_concurrency(); ++i) {
			_thread_pool.push_back(boost::make_shared<boost::thread>(new boost::thread(boost::bind(&boost::asio::io_service::run, &_io))));
		}
	}
	else {
		_work_ptr.reset(new boost::asio::io_context::work(_io));
		_io.restart();
		_acceptor_ptr->Restart();
	}
}
void CRemoteConnectionManager::StartAcceptingRemoteConnections()
{
	StartAcceptingRemoteConnections(get_free_port());
}

void CRemoteConnectionManager::StopAcceptingRemoteConnections()
{
	_acceptor_ptr->Stop();
	_work_ptr.reset();
	_io.stop();
}

void CRemoteConnectionManager::RunPolling()
{
	_io.run();
}

unsigned short CRemoteConnectionManager::GetOpenedPort()
{
	return _acceptor_ptr->GetOpenedPort();
}

CRemoteConnectionManager::CRemoteConnectionManager(const std::wstring& executor_name): _executor_name(executor_name)
{
	_work_ptr.reset(new boost::asio::io_context::work(_io));
}








//Acceptor


CAcceptor::CAcceptor(boost::asio::io_context& io, unsigned short port, const std::wstring& executor_name): _io(io), 
																										   _port(port),
																										   _executor_name(executor_name),
																										   _acceptor(io, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)),
																										   _is_stopped(false)
{
	boost::asio::socket_base::reuse_address serverOption(true);
	_acceptor.set_option(serverOption);
}

std::unique_ptr<CAcceptor> CAcceptor::Instance(boost::asio::io_context& io, unsigned short port, const std::wstring& executor_name)
{
	return std::unique_ptr<CAcceptor>(new CAcceptor(io, port, executor_name));
}

void CAcceptor::Start()
{

}

void CAcceptor::Restart()
{
}

void CAcceptor::Stop()
{
}

unsigned short CAcceptor::GetOpenedPort()
{
	return 0;
}
