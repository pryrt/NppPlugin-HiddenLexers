#pragma once
#include <string>
#include "json.hpp"

class ConfigFromJson {
public:
	ConfigFromJson(void);	// instantiate and read

	// public methods:
	std::wstring get_config_file_path(void);										// return the path name for the config file
	std::wstring get_lexer_name(std::wstring wsExtension);							// return the lexer name for the given extension
	void* get_style_info_for_lexer(std::wstring wsLexer, std::wstring wsStyleID);	// return the style info for a given lexer and styleID	; TODO=change return type
	void* get_options_for_lexer(std::wstring wsLexer);								// return the option structure for a given lexer		; TODO=change return type

	// public accessors:
	bool get_status() { return _status; }											// returns the status of the read, true if successful
	std::map <std::wstring, std::wstring>& getExt2Lex(void) { return _mExt2Lex; }		// returns the map of extension:lexer pairs

private:
	// private data:
	bool _status;										// stores the status of the read (true if successfully parsed)
	std::wstring _wsConfigFilePath;						// stores the full path of the JSON file
	std::map <std::wstring, std::wstring> _mExt2Lex;	// maps extension:lexer pairs

	// private methods:
	bool _cfg_exists_or_created(void);					// returns true if the cfg file and directory already exists, or if it was successfully created; false if there's a problem
	bool _parse_config_json(void);						// parses the JSON into the ConfigFromJson data structure
};
