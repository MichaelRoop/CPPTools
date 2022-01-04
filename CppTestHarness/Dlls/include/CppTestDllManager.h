#if !defined(CPP_TEST_DLL_MANAGER_H)
#define CPP_TEST_DLL_MANAGER_H

#include "ICppTestDllManager.h"

#if defined(WIN32) || defined(_WIN64)
#	define WIN32_LEAN_AND_MEAN // Exclude rarely-used stuff from Windows headers
#	include <windows.h>
	typedef HINSTANCE DLL_HANDLE;
#else
#	pragma message("_WIN32 or _WIN64 is not defined")
//#	error Faild compilation Nix section not yet defined
	typedef void* DLL_HANDLE;
#endif


namespace CppTestHarness {
		
	/// <summary>Manages the loading and unloading of test case DLLs</summary>
	class DllManager : public IDllManager {

	public:

		/// @brief	Default constructor
		DllManager();


		/// @brief	Destructor
		virtual ~DllManager();


		/// @brief	Load a named DLL
		virtual void Load(const CppUtils::Cpp_string& name);


		/// @brief	Unload a named DLL
		virtual void Unload();

	private:
		DLL_HANDLE m_dllHandle;


		/// @brief	Parse DLL header to load test cases from list of export functions
		void ParseHeaderAndLoad(const CppUtils::Cpp_string& dllName);

		/// @breif	Parse the DLL header to discover exported fixture load functions
		std::vector<std::string> GetMethodNames(const CppUtils::Cpp_string& dllName);

		/// @brief	Validate that the dll was opened or throw an exception
		void ValidateDllOpen(DLL_HANDLE handle, const CppUtils::Cpp_string& name);

	};

}

#endif
