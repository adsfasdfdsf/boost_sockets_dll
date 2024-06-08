#pragma once

#include <boost/asio.hpp>
#include <boost/system/error_code.hpp>

class random_port_selector
{
public:
	random_port_selector() :
		ep_(boost::asio::ip::tcp::v4(), 0),
		acceptor_(io_service_)
	{
		acceptor_.open(ep_.protocol());
		acceptor_.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
		acceptor_.bind(ep_);
	}

	unsigned short port() const
	{
		return acceptor_.local_endpoint().port();
	}

	~random_port_selector()
	{
		boost::system::error_code ec;
		acceptor_.close(ec);
	}

private:
	boost::asio::io_context io_service_;
	boost::asio::ip::tcp::endpoint ep_;
	boost::asio::ip::tcp::acceptor acceptor_;
};

inline unsigned short get_free_port()
{
    random_port_selector p;
    return p.port();
}