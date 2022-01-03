#pragma once


namespace CppIniFileNs {

	/// <summary>
	/// Defines if data is legitimate or a comment, white space or garbage.
	/// </summary>
	enum class INI_DATA_TYPE {
		/// <summary>A placeholder for comments or garbage</summary>
		NON_DATA,
		/// <summary>Holds a valid key value pair</summary>
		VALID_DATA
	};


	/// <summary>
	/// 
	/// </summary>
	enum class INI_LINE_TYPE {
		BLANK,
		COMMENT,
		SECTION,
		NODE,
		GARBAGE,
		UNDEFINED
	};



}


