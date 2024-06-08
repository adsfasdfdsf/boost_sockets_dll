#include "pch.h"
#include "CConnector.h"
#include "pch.h"
#include "CConnector.h"
#include <boost/make_shared.hpp>
#include <future>
#include <boost/shared_ptr.hpp>
#include <string>
#include <boost/bind.hpp>

//hidden interface
CConnector::CConnector(const std::wstring& ip, unsigned short port, const std::wstring& executor_name) :
    _sock_ptr(new boost::asio::ip::tcp::socket(_io)),
    _ip(ip),
    _port(port),
    _executor_name(executor_name)
{
}



void CConnector::StartConnection()
{
    std::string st(_ip.begin(), _ip.end());
    boost::system::error_code ec;
    auto address = boost::asio::ip::address::from_string(st, ec);
    _ep = boost::asio::ip::tcp::endpoint(address, _port);
    _sock_ptr->open(_ep.protocol(), ec);
    _sock_ptr->async_connect(_ep, boost::bind(&CConnector::OnConnected, this, _1));
    if (!_threads_group){
        auto f = [this]() {
            try { 
                _io.run(); 
            }
            catch (...) {

            }
        };
        _threads_group.reset(new boost::thread_group());
        _threads_group->create_thread(f);
        _threads_group->create_thread(f);
    }
   
}

void CConnector::OnConnected(const boost::system::error_code& ec)
{
    if (!_connectedPromise) {
        return;
    }
    if (ec) {
        _connectedPromise->set_value(nullptr);
        _connectedPromise.reset();
        // mb reconnetion 
    }
    else {
        
    }

}

// user interface


std::future<ICallerPtr> CConnector::ConnectToExecutor()
{
    _connectedPromise = boost::make_shared<std::promise<ICallerPtr>>();
    return _connectedPromise->get_future();
}


IConnectorPtr CConnector::Instance(const std::wstring& ip, unsigned short port, const std::wstring& executor_name)
{
    return boost::make_shared<IConnector>(new CConnector(ip, port, executor_name));
}