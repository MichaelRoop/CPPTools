#pragma once

#include "CppUtilsDefines.h"

namespace CppUtils {


	/// <summary>
	/// Not sure what this scheme was expect to force derived classes to  have an Instance() 
	/// function initialise or return a static instance. The derived class could call the 
	/// default constructor
	/// 
	/// Example: Engine derived from CppSingleton
	/// 
	/// Engine* m_instance;
	/// 
	/// Engine& Engine::Instance() {
	/// if (m_instance == 0) {
	/// 	m_instance = new Engine();
	/// }
	/// return *m_instance;
	///  
	/// </summary>
	class CPPUTILS_API CppSingleton {

	protected:

		/// @brief	Default constructor in protected scope to prevent direct intantiation.
		CppSingleton();


		/// @brief	Copy constructor in protected scope to prevent direct intantiation.
		/// @param	obj	The Singleton object used to contruct an instance.
		CppSingleton(const CppSingleton& obj);

	};
}