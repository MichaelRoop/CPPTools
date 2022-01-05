#if !defined(CPP_INI_FILE_H)
#define CPP_INI_FILE_H

#include "CppIniFileDefines.h"
#include "CppIniSection.h"

namespace CppIniFileNs {

	class CPPINI_EXPORT CppIniFile {

	public:

		typedef std::vector<CppIniSection> SectionVector;
		typedef std::vector<CppIniSection>::iterator SectionIterator;

		/// <summary>Default constructor</summary>
		CppIniFile();


		/// <summary>Constructor</summary>
		/// <param name="filename">File name</param>
		CppIniFile(const Cpp_string& filename);


		/// <summary>Copy constructor</summary>
		/// <param name="obj">The CppIniFile object used to construct this object</param>
		CppIniFile(const CppIniFile& obj);


		/// <summary>Assignment operator</summary>
		/// <param name="rhs">Right hand side value</param>
		/// <returns>The assigned object</returns>
		CppIniFile& operator = (const CppIniFile& rhs);


		/// <summary>Load the ini file into the object</summary>
		/// <param name="filename">File name</param>
		/// <returns>true on success, otherwise false</returns>
		bool Load(const Cpp_string& filename);


		/// <summary>The ini file name</summary>
		/// <returns>The ini file name</returns>
		const Cpp_string& Name() const;


		/// <summary>
		/// Retrieves the named section.
		///	WARNING:	
		/// This is an efficiency method.  It does not make a copy 
		///	but exposes the raw vector of sections.  You must validate
		///	the iterator against sections().end().  You must also 
		///	validate each section with a call to section::isDataSection.
		/// </summary>
		/// <param name="name">The name of the section to retieve</param>
		/// <returns>The retrieved section</returns>
		SectionIterator GetSection(const Cpp_string& name);


		/// <summary>Verifies if named section exists</summary>
		/// <param name="name">The name of the section to check</param>
		/// <returns>true if it exists and is a data section, otherwise false</returns>
		bool SectionExists(const Cpp_string& name);


		/// <summary>Verifies if named node from a named section exists</summary>
		/// <param name="sectionName">Name of the section</param>
		/// <param name="nodeName">Name of the node</param>
		/// <returns>true if it exists as a data section, otherwise false</returns>
		bool NodeExists(const Cpp_string& sectionName, const Cpp_string& nodeName);

		
		/// <summary>Retrieves value from the named section and key</summary>
		/// <param name="sectionName">Section name</param>
		/// <param name="nodeName">Node name</param>
		/// <returns>The retrieved value or an empty string if not found</returns>
		CppUtils::Cpp_string GetValue(const Cpp_string& sectionName, const Cpp_string& nodeName);


		/// <summary>Add a section to the ini file</summary>
		/// <param name="theSection">The section to add</param>
		/// <returns>true if successful, otherwise false</returns>
		bool AddSection(const CppIniSection& theSection);


		/// <summary>
		/// Retrieve a reference to the vector of sections.
		///
		///	WARNING:	
		/// This is an efficiency method.  It does not make a copy 
		///	but exposes the raw vector of sections.  You must validate 
		///	each section with a call to section::isDataSection.
		/// </summary>
		/// <returns>A reference to the vector of sections</returns>
		const SectionVector& Sections() const;


		/// <summary>Retrieve a copy of the vector of data sections</summary>
		/// <returns>A vector of sections</returns>
		SectionVector GetSectionsCopy();


		/// <summary>Retrieve a copy of the vector of data nodes from the named section</summary>
		/// <param name="sectionName">name of the section to retrieve</param>
		/// <returns>A vector of nodes</returns>
		CppIniSection::NodeVector GetNodesCopy(const CppUtils::Cpp_string& sectionName);

	private:

		Cpp_string m_filename;
		SectionVector m_sections;

		/// <summary>Initialise the ini file with another ini file</summary>
		/// <param name="obj">The CppIniFile to use for its values</param>
		void Init(const CppIniFile& obj);

	};
	
	/// <summary>Streaming function for the ini file in global scope</summary>
	/// <param name="os">The output stream</param>
	/// <param name="obj">The CppIniFile to stream</param>
	/// <returns>The output stream object</returns>
	Cpp_ostream& operator << (Cpp_ostream& os, const CppIniFile& obj);

}

#endif // !defined(CPP_INI_FILE_H)
