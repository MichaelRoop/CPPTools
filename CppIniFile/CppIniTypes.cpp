#include "CppIniTypes.h"

namespace CppIniFileNs {


	const Cpp_string ToString(const CppIniFileNs::INI_LINE_TYPE& lineType) {
		switch (lineType) {
		case INI_LINE_TYPE::BLANK: return _L_("BLANK");
		case INI_LINE_TYPE::COMMENT: return _L_("COMMENT");
		case INI_LINE_TYPE::SECTION: return _L_("SECTION");
		case INI_LINE_TYPE::NODE: return _L_("NODE");
		case INI_LINE_TYPE::GARBAGE: return _L_("GARBAGE");
		case INI_LINE_TYPE::UNDEFINED: return _L_("UNDEFINED");
		default: return _L_("Not define");
		}
	}


	const Cpp_string ToString(const CppIniFileNs::INI_DATA_TYPE& dataType) {
		switch (dataType) {
			case INI_DATA_TYPE::NON_DATA: return _L_("NON_DATA");
			case INI_DATA_TYPE::VALID_DATA: return _L_("VALID_DATA");
			default: return _L_("Not define");
		}
	}



}
