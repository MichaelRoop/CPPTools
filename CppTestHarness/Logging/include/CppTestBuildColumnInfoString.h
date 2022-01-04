///--------------------------------------------------------------------------------------
/// @brief	Builds strings with for column information.
///--------------------------------------------------------------------------------------
#if !defined(CPP_TEST_BUILD_COLUMN_INFO_STRING_H)
#define CPP_TEST_BUILD_COLUMN_INFO_STRING_H


#include "CppTestFieldPair.h"


namespace CppTestHarness {

	///--------------------------------------------------------------------------------------
	/// @brief	Functor to Add a value to the value string on each iteration.
	///
	/// You can use this with the std::for each
	struct BuildColumnInfoString {
		enum class ColumnInfoParts {
			NAME_ONLY,
			TYPE_ONLY,
			NAME_TYPE
		};


		/// @brief Functor constructor.
		///
		/// @param	os					The stream to receive the string.
		/// @param	nameTypeDelimiter	Delimiter between Column name and type.
		/// @param	unitDelimiter		Delimiter between info for one column.
		///	@param	parts				What column info to concatente.
		BuildColumnInfoString(
			Cpp_stringstream& os,
			const Cpp_string& nameTypeDelimiter,
			const Cpp_string& unitDelimiter,
			ColumnInfoParts parts
		);


		/// @brief	Function operator called on each iteration.
		///
		/// @param	field	The current field at iteration.
		void operator () (const FieldPair& field);

	private:

		Cpp_stringstream& m_os;			///< Stream to build string.
		Cpp_string m_nameTypeDelimiter;	///< Delimiter between names and types.	
		Cpp_string m_unitDelimiter;		///< Delimiter between each column's info.
		ColumnInfoParts m_parts;		///< Specifies which parts to add to string.
		int	m_count;					///< Iteration counter.
	};

}

#endif
