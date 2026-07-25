#pragma once
#include <string>

class ConfigFromJson {
public:
	ConfigFromJson(void);	// instantiate and read

	std::wstring get_config_file_path(void);										// return the path name for the config file
	std::wstring get_lexer_name(std::wstring wsExtension);							// return the lexer name for the given extension
	void* get_style_info_for_lexer(std::wstring wsLexer, std::wstring wsStyleID);	// return the style info for a given lexer and styleID	; TODO=change return type
	void* get_options_for_lexer(std::wstring wsLexer);								// return the option structure for a given lexer		; TODO=change return type

private:
	std::wstring _wsConfigFilePath;
};
