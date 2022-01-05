#if !defined(CPP_INPUT_LINE_H)
#define CPP_INPUT_LINE_H

#include "CppIniFileDefines.h"
#include "CppIniTypes.h"

namespace CppIniFileNs {

	/// <summary>Forward declaration of implementation object</summary>
	class CppIniInputLineImpl;

	class CPPINI_EXPORT CppIniInputLine {
	public:

		/// <summary>Default constructors</summary>
		CppIniInputLine();


		/// <summary>Copy Constructor</summary>
		/// <param name="str">The object to copy</param>
		CppIniInputLine(const Cpp_string& str);
		

		~CppIniInputLine();
		
		/// <summary>Initialise the object with the string</summary>
		/// <param name="str">The string to parse and identify</param>
		/// <returns>The line type as identified by parsing</returns>
		INI_LINE_TYPE Init(const Cpp_string& str);


		/// <summary>
		/// The first value created by parsing the line string
		/// This would be the only value for Section, the key name for
		///	a node, and the comment or garbage value for those types of lines.
		/// </summary>
		/// <returns>The first value</returns>
		const Cpp_string& FirstValue() const;


		/// <summary>
		/// The second value created by parsing the line string
		/// This would only apply to nodes and it would correspond to the value of
		///	the key value pair.
		/// </summary>
		/// <returns>The second value</returns>
		const Cpp_string& SecondValue() const;


		/// <summary>Indicates the type of line that was parsed</summary>
		/// <returns>The type of line that was parsed</returns>
		INI_LINE_TYPE TypeOf() const;

	private:

		CppIniInputLineImpl* m_impl = NULL;
		void Cleanup();
	};

} 

#endif