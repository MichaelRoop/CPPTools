///--------------------------------------------------------------------------------------
/// @brief	Data column information type.
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_FIELD_PAIR_H)
#define CPP_TEST_FIELD_PAIR_H

#include "CppTestHarnessDefines.h"
#include <vector>


namespace CppTestHarness {

	/// @brief Typedef of the basic pair that defines the name and type strings of a SQL field.
	typedef std::pair<Cpp_string, Cpp_string> FieldPair;


	/// @brief	Typedef of a vector of the FieldPair.
	typedef std::vector< std::pair<Cpp_string, Cpp_string> > FieldVector;


}

#endif
