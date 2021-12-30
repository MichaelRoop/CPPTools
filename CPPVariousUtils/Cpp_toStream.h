#pragma once

#include "CppUtilsDefines.h"
#include "Cpp_char.h"
#include "Cpp_iostream.h"
#include "Cpp_string.h"

#include <vector>
#include <algorithm>

namespace CppUtils {

	// Forward declaration for compiler errors.
	template<class T, class T2> class CPPUTILS_API ToStreamClass;

	// Forward declaration for compiler errors.
	template<class T, class T2> class ToStreamVecClass;


	// Template function to stream out types to an output with automatic conversions.
	template<class T>
	Cpp_ostream& ToStream(Cpp_ostream& os, const T& streamValue) {
		ToStreamClass<T, Cpp_ostream>::streamOut(os, streamValue);
		return os;
	}


	// Template function to stream out a vector of types to an output with automatic conversions.
	template<class T, class T2>
	CppUtils::Cpp_ostream& ToStream(Cpp_ostream& os, const std::vector<T>& streamValue, T2& outputFormater) {
		ToStreamVecClass<T, /*Cpp_ostream,*/T2>::streamOut( /*os,*/ streamValue, outputFormater);
		return os;
	}

	//------------------------------------------------------------------------------------------------
	//	Note: Use the template functions rather than the template classes below directly.  They will 
	//	automaticaly resolve the template args from the function arg types so you do not have to use 
	//	the <> notation.  They will automaticaly call the right template class specialization which 
	//	will do the work.
	//------------------------------------------------------------------------------------------------


	template<class T, class T2> class CPPUTILS_API ToStreamClass {
	public:
		static void streamOut(T2& os, const T& value) {
			os << value;
		}


		ToStreamClass(T2& os) : m_os(os) {
		}


		void operator () (const T& obj) {
			m_os << obj;
		}

	private:

		T2& m_os;


		/// @brief	Assignment operator to satisfy compiler warnings.
		ToStreamClass& operator = (const ToStreamClass& rhs) {
			if (&rhs != this) {
				m_os = rhs.m_os;
			}
			return *this;
		}
	};


	// Class specialisation to bridge between wide char to narrow char output stream.
	template<> class CPPUTILS_API ToStreamClass<std::wstring, std::ostream> {
	public:
		static void streamOut(std::ostream& os, const std::wstring& value) {
			os << CppUtils::WideToNarrowString(value);
		}
	};


	// Class specialisation to bridge between narrow char to wide output stream.
	template<> class CPPUTILS_API ToStreamClass<std::string, std::wostream> {
	public:
		static void streamOut(std::wostream& os, const std::string& value) {
			os << CppUtils::NarrowToWideString(value);
		}
	};

	//---------------------------------------------------------------------------------
	// Vector streaming functors and classes.
	//---------------------------------------------------------------------------------

	template<class T> struct CPPUTILS_API VecStreamCommaDelimited {
		VecStreamCommaDelimited(Cpp_ostream& os)
			: m_os(os),
			m_count(0) {
		}

		void operator () (const T& val) {
			if (m_count++ > 0) {
				ToStream(m_os, L(","));
			}
			ToStream(m_os, val);
		}
	private:
		Cpp_ostream& m_os;
		int			m_count;
	};


	template<class T> struct CPPUTILS_API VecStreamLineDelimited {
		VecStreamLineDelimited(Cpp_ostream& os, const Cpp_string& leader = L(""))
			: m_os(os),
			m_leader(leader) {
		}

		void operator () (const T& val) {
			m_os << m_leader;
			ToStream(m_os, val);
			m_os << std::endl;
		}
	private:
		Cpp_ostream& m_os;
		Cpp_string		m_leader;

		VecStreamLineDelimited& operator = (const VecStreamLineDelimited& /*rhs*/) { return *this; }
	};


	// Class to stream out vector of values.
	template<class T, class T2> class ToStreamVecClass {
	public:
		static void streamOut(const std::vector<T>& values, T2& outputFormater) {
			std::for_each(values.begin(), values.end(), outputFormater);
		}
	};



	//---------------------------------------------------------------------------------
	// End template class specialisations.
	//---------------------------------------------------------------------------------



}


