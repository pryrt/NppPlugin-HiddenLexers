#include "ConfigFromJson.h"
#include "PluginDefinition.h"

#include <string>
#include "json.hpp"

// instantiate and read
ConfigFromJson::ConfigFromJson(void)
{
	// make sure I have the meta info
	gNppMetaInfo.populate();

	// see if I have the config file, and if not, create a dummy one
	_wsConfigFilePath = gNppMetaInfo.dir.cfgPluginConfigMyDir + L"\\" + gNppMetaInfo.wsPluginName();
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
