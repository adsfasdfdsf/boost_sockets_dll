#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/asio/ip/tcp.hpp>
using IProviderPtr = boost::shared_ptr<class IProvider>;
using IConnectorPtr = boost::shared_ptr<class IConnector>;
using IRegistrarPtr = boost::shared_ptr<class IRegistrar>;
using IExecutorPtr = boost::shared_ptr<class IExecutor>;
using ICallerPtr = boost::shared_ptr<class ICaller>;
using CMessengerPtr = boost::shared_ptr<class CMessenger>;
using CMessagePtr = boost::shared_ptr<class CMessage>;
using SocketPtr = boost::shared_ptr<boost::asio::ip::tcp::socket>;
using CSessionPtr = boost::shared_ptr<class CSession>;
using CExecutorPtr = boost::shared_ptr<class CExecutor>;
using CRemoteConnectionManagerPtr = boost::shared_ptr<class CRemoteConnectionManager>;
using CAcceptorPtr = boost::shared_ptr<class CAcceptor>;
using CServicePtr = boost::shared_ptr<class CService>;
