#include "ListException.h"

ListException::ListException(const ListError& error_code_) :
	error_code(error_code_)
{
	switch (error_code)
	{
	case BAD_SIZE:
		m_msg.assign("Error : Bad size");
		break;
	case BAD_ELEMENT:
		m_msg.assign("Error : Bad element");
		break;
	case BAD_POP:
		m_msg.assign("Error : Bad pop");
		break;
	default:
		break;
	}
}

const char* ListException::what() const noexcept {
	return m_msg.c_str();
}