#pragma once
#include "connector.h"
#include <string>
#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_context.hpp>
#include <future>
#include <boost/thread.hpp>

class CConnector : public IConnector, boost::enable_shared_from_this<CConnector>
{
public:
    virtual std::future<ICallerPtr> ConnectToExecutor() override;
    static IConnectorPtr Instance(const std::wstring& ip, unsigned short port, const std::wstring& executor_name);
private:
    CConnector(const std::wstring& ip, unsigned short port, const std::wstring& executor_name);
    void StartConnection();
    void OnConnected(const boost::system::error_code& ec);

    boost::asio::io_context _io;
    boost::shared_ptr<boost::asio::ip::tcp::socket> _sock_ptr;
    boost::asio::ip::tcp::endpoint _ep;
    std::wstring _ip;
    std::wstring _executor_name;
    unsigned short _port;
    boost::shared_ptr<std::promise<ICallerPtr>> _connectedPromise;
    boost::shared_ptr<boost::thread_group> _threads_group;
};
