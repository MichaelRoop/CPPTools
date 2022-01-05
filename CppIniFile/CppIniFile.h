#pragma once
#include "CppIniFileDefines.h"
#include "CppIniSection.h"

namespace CppIniFileNs {

	class CPPINI_EXPORT CppIniFile {

	public:

		typedef std::vector<CppIniSection> SectionVector;
		typedef std::vector<CppIniSection>::iterator SectionIterator;


		/// @brief	Constructor.
		CppIniFile();


		/// @brief	Constructor.
		///
		/// @param	filename	The name of the ini file.
		CppIniFile(const CppUtils::Cpp_string& filename);


		/// @brief	Copy constructor.
		///
		/// @param	obj	The CppIniFile object used to construct this object.
		CppIniFile(const CppIniFile& obj);


		/// @brief	Assignment operator.
		///
		/// @param	rhs	The CppIniFile object used to initialise this object.
		CppIniFile& operator = (const CppIniFile& rhs);


		/// @brief	Load the ini file into the object.
		///
		/// @param	filename	The name of the ini file.
		///
		/// @return	true if the load was successful, otherwise false.
		bool Load(const CppUtils::Cpp_string& filename);


		/// @brief	The ini file name.
		///
		/// @return	The ini file name.
		const CppUtils::Cpp_string& Name() const;


		/// @brief	Retrieves the named section.
		///
		///	WARNING:	This is an efficiency method.  It does not make a copy 
		///				but exposes the raw vector of sections.  You must validate
		///				the iterator against sections().end().  You must also 
		///				validate each section with a call to section::isDataSection.
		///
		/// @param	name	The name of the section to retrieve.
		///
		/// @return The retrieved section 
		SectionIterator GetSection(const CppUtils::Cpp_string& name);


		/// @brief	Verifies if named section exists.
		///
		/// @param	name	The name of the section to check.
		///
		/// @return true if it exists and is a data section, otherwise false.
		bool SectionExists(const CppUtils::Cpp_string& name);


		/// @brief	Verifies if named node from a named section exists.
		///
		/// @param	sectionName	The name of the section to check.
		/// @param	nodeName	The name of the node to check.
		///
		/// @return true if it exists and is a data section, otherwise false.
		bool NodeExists(const CppUtils::Cpp_string& sectionName, const CppUtils::Cpp_string& nodeName);


		/// @brief	Retrieves value from the named section and key.
		///
		/// @param	sectionName	name of the section to retrieve.
		/// @param	nodeName	name of the node that holds the value to retrieve.
		///
		/// @return	The retrieved value or an empty string if not found. 
		CppUtils::Cpp_string GetValue(
			const CppUtils::Cpp_string& sectionName,
			const CppUtils::Cpp_string& nodeName
		);


		/// @brief	Add a section to the ini file.
		///
		/// @param	theSection	The section to add.
		///
		/// @return	true if successful, otherwise false.
		bool AddSection(const CppIniSection& theSection);


		/// @brief	Retrieve a reference to the vector of sections.
		///
		///	WARNING:	This is an efficiency method.  It does not make a copy 
		///				but exposes the raw vector of sections.  You must validate 
		///				each section with a call to section::isDataSection.
		///
		/// @return	A reference to the vector of sections.
		const SectionVector& Sections() const;


		/// @brief	Retrieve a copy of the vector of data sections.
		///
		/// @return	A vector of sections.
		SectionVector GetSectionsCopy();


		/// @brief	Retrieve a copy of the vector of data nodes from the named section.
		///
		/// @param	sectionName	name of the section to retrieve.
		///
		/// @return	A vector of nodes.
		CppIniSection::NodeVector GetNodesCopy(const CppUtils::Cpp_string& sectionName);


	private:

		CppUtils::Cpp_string	m_filename;	///< File name of the ini file.
		SectionVector			m_sections;	///< vector of sections.


		/// @brief	Initialise the ini file with another ini file.
		///
		/// @param	obj	The CppIniFile to use for its values.
		void Init(const CppIniFile& obj);

	};


	/// @brief	Streaming function for node object.
	///
	/// @param	os	The output stream.
	/// @param	obj	The CppIniFile object to stream out.
	///
	/// @return	The output stream object.
	CppUtils::Cpp_ostream& operator << (CppUtils::Cpp_ostream& os, const CppIniFile& obj);


}
