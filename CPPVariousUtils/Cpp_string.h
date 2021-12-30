#pragma once

#include "CppUtilsDefines.h"
#include "Cpp_char.h"

namespace CppUtils {

#if defined(CPP_USE_WIDE_STR)
	typedef std::wstring	Cpp_string;
#else
	typedef std::string		Cpp_string;
#endif


	/// @brief	Function to trim white space from the right of a string.
	///
	/// @param	str	The string to trim.
	///
	/// @return	A copy of the trimmed string.
	CPPUTILS_API Cpp_string TrimRight(const Cpp_string& str);


	/// @brief	Function to trim white space from the left of a string.
	///
	/// @param	str	The string to trim.
	///
	/// @return	A copy of the trimmed string.
	CPPUTILS_API Cpp_string TrimLeft(const Cpp_string& str);


	/// @brief	Function to trim white space from the left and right of a string.
	///
	/// @param	str	The string to trim.
	///
	/// @return	A copy of the trimmed string.
	CPPUTILS_API Cpp_string Trim(const Cpp_string& str);


	/// @brief	Function to extract the file name from a string which may include the path.
	///
	/// @param	pathAndFile	The string which includes the fully defined file name and path.
	///
	/// @return	A copy of the string with only the file name.
	CPPUTILS_API std::string ExtractFileName(const std::string& pathAndFile);


	/// @brief	Function to extract the file name from a string which may include the path.
	///
	/// @param	pathAndFile	The string which includes the fully defined file name and path.
	///
	/// @return	A copy of the string with only the file name.
	CPPUTILS_API std::wstring ExtractFileName(const std::wstring& pathAndFile);


	/// @brief	Function to convert a wide string with only ANSII characters to narrow.
	///
	/// @param	str	The string to convert.
	///
	/// @return	A copy of the string converted to narrow char.
	CPPUTILS_API std::string WideToNarrowString(const std::wstring& str);


	/// @brief	Function to convert a narrow string to wide.
	///
	/// @param	str	The string to convert.
	///
	/// @return	A copy of the string converted to wide char.
	CPPUTILS_API std::wstring NarrowToWideString(const std::string& str);


	/// @brief	Function to tokenize a string by calling it repeatedly.
	///
	/// @param	currentPos	The current position of the parsing. This has to be initialised to 
	///						0 before the first call.
	/// @param	str			The complete string to tokenize.
	/// @param	token		A holder to receive the extracted token.
	/// @param	delimiter	The char delimiter that defines the boundry of the next token.
	///
	/// @return	true if a new token has been found, otherwise false.
	CPPUTILS_API bool MrTokenize(
		Cpp_string::size_type& currentPos,
		const Cpp_string& str,
		Cpp_string& token,
		Cpp_char delimiter
	);



	/// @brief	Function to substring a string. Needed because reference to the npos causing 
	///			a link failure
	/// @param	pos	The start position 0 indexed.
	/// @param	length	The length of the substring.
	/// @return	the substring
	CPPUTILS_API CppUtils::Cpp_string SubString(
		const CppUtils::Cpp_string& s,
		CppUtils::Cpp_string::size_type pos,
		CppUtils::Cpp_string::size_type length);


	/// @brief	Function to substring a string from pos to end of string. Needed because reference 
	//			to the npos causing a link failure
	/// @param	pos	The start position 0 indexed.
	/// @return	the substring
	CPPUTILS_API CppUtils::Cpp_string SubString(const CppUtils::Cpp_string& s, CppUtils::Cpp_string::size_type pos);


	/// @ replace the static npos with a function that returns the same value. The function will be exported
	CPPUTILS_API CppUtils::Cpp_string::size_type StrNPos();


	/// @brief	Function to replace find. Needed because reference to the npos causing a link failure
	/// @param	pos	The start position 0 indexed.
	CPPUTILS_API std::string::size_type Find(const std::string& s, const std::string pattern, std::string::size_type pos);


	/// @brief	Contain function
	CPPUTILS_API bool Contains(const std::string& s, const std::string pattern);


	/// @brief	Contain function
	CPPUTILS_API bool Contains(const std::wstring& s, const std::wstring pattern);


	/// @brief	Convert a char* to Cpp_string. Useful for dealing with hard coded types
	//			as they interact with the wide/narrow Cpp_string in the system
	/// @param	value	The value to tranform
	CPPUTILS_API CppUtils::Cpp_string ToMrString(const char* value);


	/// @brief	Convert a char* to Cpp_string. Useful for dealing with hard coded types
	//			as they interact with the wide/narrow Cpp_string in the system
	/// @param	value	The value to tranform
	CPPUTILS_API CppUtils::Cpp_string ToMrString(const wchar_t* value);


	/// @brief	Convert a char* to Cpp_string. Useful for dealing with hard coded types
	//			as they interact with the wide/narrow Cpp_string in the system
	/// @param	value	The value to tranform
	CPPUTILS_API CppUtils::Cpp_string ToMrString(const std::string& value);


	/// @brief	Convert a char* to Cpp_string. Useful for dealing with hard coded types
	//			as they interact with the wide/narrow Cpp_string in the system
	/// @param	value	The value to tranform
	CPPUTILS_API CppUtils::Cpp_string ToMrString(const std::wstring& value);


	/// @brief	Convert to a char* from Cpp_string. Useful for dealing with returns requiring 
	///			hard coded types as they interact with the wide/narrow Cpp_string in the system
	///			The argument is hard coded to handle one possible form of the Cpp_string
	/// @param	value	The value to tranform
	CPPUTILS_API std::string ToCharPtr(const std::string& value);


	/// @brief	Convert to a char* from Cpp_string. Useful for dealing with returns requiring 
	///			hard coded types as they interact with the wide/narrow Cpp_string in the system
	///			The argument is hard coded to handle one possible form of the Cpp_string
	/// @param	value	The value to tranform
	CPPUTILS_API std::string ToCharPtr(const std::wstring value);

}
