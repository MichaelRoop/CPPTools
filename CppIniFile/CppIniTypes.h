#if !defined(CPP_INI_TYPES_H)
#define CPP_INI_TYPES_H


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


	/// <summary>Type of line</summary>
	enum class INI_LINE_TYPE {
		BLANK,
		COMMENT,
		SECTION,
		NODE,
		GARBAGE,
		UNDEFINED
	};

}

#endif
