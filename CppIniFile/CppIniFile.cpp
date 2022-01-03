#include "CppIniFile.h"
#include "../CPPVariousUtils/Cpp_char.h"
#include "../CPPVariousUtils/Cpp_fstream.h"
#include "../CPPVariousUtils/Cpp_functors.h"
#include "../CPPVariousUtils/Cpp_toStream.h"
#include "../CPPVariousUtils/Cpp_sstream.h"
#include "../CPPVariousUtils/Cpp_exceptions.h"
#include "CppIniInputLine.h"

namespace CppIniFileNs {

		/// @brief	Filter out non valid sections to produce a good set of sections.
		struct FilterSectionsFunctor {
			FilterSectionsFunctor(CppIniFile::SectionVector& sectionVec) : m_sections(sectionVec) {}
	
			void operator () (const CppIniSection& theSection) {
				if (theSection.IsDataSection()) {
					m_sections.push_back(theSection);
				}
			}
			CppIniFile::SectionVector& m_sections; ///< Target for sections.
		};
		// -------------------- end functors ----------------
	
		CppIniFile::CppIniFile() {
		}
	
	
		CppIniFile::CppIniFile(const CppUtils::Cpp_string& filename) : m_filename(filename) {
		}
	
	
		CppIniFile::CppIniFile(const CppIniFile& obj) {
			this->Init(obj);
		}
	
	
		CppIniFile& CppIniFile::operator = (const CppIniFile& rhs) {
			if (this != &rhs) {
				this->Init(rhs);
			}
			return *this;
		}
	
	
		void CppIniFile::Init(const CppIniFile& obj) {
			m_sections.clear();
			m_sections = obj.m_sections;
			m_filename = obj.m_filename;
		}
	
	
		bool CppIniFile::Load(const CppUtils::Cpp_string& filename) {
			
			m_sections.clear();
	#if defined(_WIN32) || defined (_WIN64)
			// The wchar_t for filename is a MS extension
			CppUtils::Cpp_ifstream  script(filename.c_str());
	#else
			mr_utils::Cpp_ifstream  script(CppUtils::ToCharPtr(filename).c_str());
	#endif
			CppUtils::Cpp_stringstream ss;
			CppUtils::ToStream(ss, filename) << L(" cannot be opened");
			CppUtils::Cpp_exception::assertCondition(script.is_open(), FL, ss.str());
	
			const int size = 2048;
			std::vector<CppUtils::Cpp_char> buff;
			buff.assign(size + 1, L('\0'));
			CppIniSection			workingSection;
			CppIniInputLine	inLine;
	
			while (script.getline(&buff[0], size)) {
				inLine.Init(CppUtils::Cpp_string(&buff[0]));
	
				switch (inLine.TypeOf()) {
				case INI_LINE_TYPE::SECTION:
					this->AddSection(workingSection);
					workingSection.SetName(inLine.firstValue());
					break;
				default:
					if (workingSection.Name().empty()) {
						// Text lines before the first section is detected will be written as non data 
						// sections representing comments and garbage lines.
						this->AddSection(CppIniSection(inLine));
					}
					else {
						workingSection.AddNode(inLine);
					}
					break;
				}
			}
	
			// Add the last section built before leaving.
			this->AddSection(workingSection);
			
			return true;
		}
	
	
		bool CppIniFile::AddSection(const CppIniSection& theSection) {
			if (!theSection.Name().empty()) {
				m_sections.push_back(theSection);
				return true;
			}
			return false;
		}
	
	
		const CppUtils::Cpp_string& CppIniFile::Name() const {
			return m_filename;
		}
	
	
		CppIniFile::SectionIterator CppIniFile::GetSection(const CppUtils::Cpp_string& name) {
			return
				std::find_if(
					m_sections.begin(),
					m_sections.end(),
					CppUtils::IsNamed<CppIniSection, CppUtils::Cpp_string>(name)
				);
		}
	
	
		bool CppIniFile::SectionExists(const CppUtils::Cpp_string& name) {
			SectionIterator it = this->GetSection(name);
			if (it == m_sections.end() || !it->IsDataSection()) {
				return false;
			}
			return true;
		}
	
	
		bool CppIniFile::NodeExists(
			const CppUtils::Cpp_string& sectionName,
			const CppUtils::Cpp_string& nodeName) {
			if (this->SectionExists(sectionName)) {
				return this->GetSection(sectionName)->NodeExists(nodeName);
			}
			return false;
		}
	
	
		CppUtils::Cpp_string CppIniFile::GetValue(
			const CppUtils::Cpp_string& sectionName,
			const CppUtils::Cpp_string& nodeName) {
			SectionIterator it = this->GetSection(sectionName);
			return it == this->Sections().end() ? CppUtils::Cpp_string(L("")) : it->value(nodeName);
		}
	
	
		const CppIniFile::SectionVector& CppIniFile::Sections() const {
			return m_sections;
		}
	
	
		CppIniFile::SectionVector CppIniFile::GetSectionsCopy() {
			CppIniFile::SectionVector sections;
			std::for_each(
				m_sections.begin(), 
				m_sections.end(), 
				FilterSectionsFunctor(sections));
			return sections;
		}
	
	
		CppIniSection::NodeVector CppIniFile::GetNodesCopy(const CppUtils::Cpp_string& sectionName) {
			if (this->SectionExists(sectionName)) {
				return this->GetSection(sectionName)->GetNodesCopy();
			}
			return CppIniSection::NodeVector();
		}
	
	
		CppUtils::Cpp_ostream& operator << (CppUtils::Cpp_ostream& os, const CppIniFile& obj) {
			std::for_each(
				obj.Sections().begin(),
				obj.Sections().end(),
				CppUtils::ToStreamClass<CppIniSection, CppUtils::Cpp_ostream>(os));
			return os;
		}
	
	

}

