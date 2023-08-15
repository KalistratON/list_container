#pragma once

#include <exception>
#include <string>

class ListException : public std::exception
{
public:
	enum ListError {
		BAD_SIZE,
		BAD_ELEMENT,
		BAD_POP,
	};

private:
	std::string m_msg;
	ListError error_code;

public:
	explicit ListException(const ListError&);
	
	const char* what() const noexcept override;
};