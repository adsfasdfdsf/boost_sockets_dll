#pragma once
#include <vector>
#include <boost/cstdint.hpp>
#include "fwd.h"
class CMessage
{
public:
	enum eAction {
		NoAction,
		TaskProccess
	};
	struct Header {
	public:
		Header(boost::int32_t body_size, eAction action) : _body_size(body_size), _action(action) {};
		Header() {};
		boost::int32_t _body_size;
		eAction _action;
	};

	static CMessagePtr Instance() {
		CMessagePtr sp(new CMessage());
		return sp;
	};
	static CMessagePtr Instance(std::vector<char> data, eAction action) {
		CMessagePtr sp(new CMessage(data, action));
		return sp;
	};

	Header& GetHeader() {
		return _header;
	};

	std::pair<void*, boost::int32_t> GetBuffer() {
		_ASSERT(_header._body_size > 0);
		if (_header._body_size != _buffer.size()) {
			_buffer.resize(_header._body_size);
		}
		return {&_buffer.at(0), _header._body_size};
	};

	std::vector<char> GetBufferData() {
		_ASSERT(_header._body_size > 0);
		if (_header._body_size != _buffer.size()) {
			_buffer.resize(_header._body_size);
		}
		return _buffer;
	};

private:
	CMessage() {};
	CMessage(std::vector<char> data, eAction action) : _buffer(data), _header(Header((int32_t)data.size(), action)) {};
	Header _header;
	std::vector<char> _buffer;
};
