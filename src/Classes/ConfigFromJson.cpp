#include "ConfigFromJson.h"
#include "PluginDefinition.h"

#include <string>
#include <shlwapi.h>
#include "json.hpp"

// instantiate and read
ConfigFromJson::ConfigFromJson(void)
{
	// make sure I have the meta info
	gNppMetaInfo.populate();

	// see if I have the config file, and if not, create a dummy one
	_wsConfigFilePath = gNppMetaInfo.dir.cfgPluginConfigMyDir + L"\\" + gNppMetaInfo.wsPluginName() + L".jsonc";
	if (_cfg_exists_or_created()) {
		;
	}
}

// return the lexer name for the given extension
std::wstring ConfigFromJson::get_lexer_name(std::wstring /*wsExtension*/)
{
	return std::wstring(L"");
}

// return the style info for a given lexer and styleID	; TODO=change return type
void* ConfigFromJson::get_style_info_for_lexer(std::wstring /*wsLexer*/, std::wstring /*wsStyleID*/)
{
	return nullptr;
}

// return the option structure for a given lexer		; TODO=change return type
void* ConfigFromJson::get_options_for_lexer(std::wstring /*wsLexer*/)
{
	return nullptr;
}

// returns true if the cfg file and directory already exists, or if it was successfully created; false if there's a problem
bool ConfigFromJson::_cfg_exists_or_created(void)
{
	// if file already exists, great
	if( PathFileExists(_wsConfigFilePath.data()) )
		return true;

	return pcjHelper::write_file_wrapper(_wsConfigFilePath, R"myMultiLineJSONC({
  // "exensions": { "ext": "lexer", … }
  "extensions": {
    "stata": "stata",
    "do": "stata"
  },
  // "lexers": { "lexer": {"styleID": {...}}, … }
  "lexers": {
    "stata": {
        // https://github.com/notepad-plus-plus/notepad-plus-plus/blob/master/lexilla/include/LexicalStyles.iface
        //      match: val (SCE_*)=(\d+)
      "0" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_DEFAULT
      "1" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_COMMENT
      "2" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_COMMENTLINE
      "3" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_COMMENTBLOCK
      "4" : { "fgColor": "8CD0D3", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_NUMBER
      "5" : { "fgColor": "9F9D6D", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_OPERATOR
      "6" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_IDENTIFIER
      "7" : { "fgColor": "CC9393", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_STRING
      "8" : { "fgColor": "93E0E3", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_TYPE
      "9" : { "fgColor": "DFC47D", "bgColor": "3F3F3F", "fontStyle": "0" },         // SCE_STATA_WORD
      "10" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },        // SCE_STATA_GLOBAL_MACRO
      "11" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },        // SCE_STATA_MACRO
      "options": {}
    }
  }
}
)myMultiLineJSONC");
}
