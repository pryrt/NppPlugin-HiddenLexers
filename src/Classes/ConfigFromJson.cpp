#include "ConfigFromJson.h"
#include "PluginDefinition.h"

#include <string>
#include <shlwapi.h>
#include <fstream>
#include <stdexcept>
#include "pcjHelper.h"

// instantiate and read
ConfigFromJson::ConfigFromJson(void)
{
    _status = false;

	// make sure I have the meta info
	gNppMetaInfo.populate();

	// see if I have the config file, and if not, create a dummy one
	_wsConfigFilePath = gNppMetaInfo.dir.cfgPluginConfigMyDir + L"\\" + gNppMetaInfo.wsPluginName() + L".json";
	if (_cfg_exists_or_created()) {
        try {
            _status = _parse_config_json();
        }
        catch (nlohmann::json::exception& e) {
            std::string msg = std::string("JSON Error in HiddenLexers config: ") + e.what();
            ::MessageBoxA(gNppMetaInfo.hwnd._nppHandle, msg.c_str(), "HiddenLexers: JSON Error", MB_ICONERROR);
            _status = false;
        }
        catch (std::runtime_error & e) {
            std::string msg = std::string("Data Error in HiddenLexers config: ") + e.what();
            ::MessageBoxA(gNppMetaInfo.hwnd._nppHandle, msg.c_str(), "HiddenLexers: Data Error", MB_ICONERROR);
            _status = false;
        }
        catch (std::exception& e) {
            std::string msg = std::string("Unrecognized Error in HiddenLexers config: ") + e.what();
            ::MessageBoxA(gNppMetaInfo.hwnd._nppHandle, msg.c_str(), "HiddenLexers: Unrecognized ConfigFile Error", MB_ICONERROR);
            _status = false;
        }
	}
}

// return the lexer name for the given extension
std::wstring ConfigFromJson::get_lexer_name(std::wstring /*wsExtension*/)
{
	return std::wstring(L"");
}

// return value for lexerInfoNotFound
ts_StyleInfo lexerInfoNotFound{ "","","",false,false,false };

// return the style info for a given lexer and styleID	; TODO=change return type
ts_StyleInfo& ConfigFromJson::get_style_info_for_lexer(std::wstring wsLexer, std::wstring wsStyleID)
{
    std::string sLexer = pcjHelper::wstring_to_utf8(wsLexer);
    std::string sStyleID = pcjHelper::wstring_to_utf8(wsStyleID);

    auto map_iter = _mStyles.find(sLexer);
    if (map_iter == _mStyles.end())
        return lexerInfoNotFound;

    auto style_iter = _mStyles[sLexer].find(sStyleID);
    if (style_iter == _mStyles[sLexer].end())
        return lexerInfoNotFound;

    return _mStyles[sLexer][sStyleID];
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

	return pcjHelper::write_file_wrapper(_wsConfigFilePath, R"myMultiLineJSON({
  "extensions": {
    "stata": "stata",
    "do": "stata"
  },
  "lexers": {
    "stata": {
      "0" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },
      "1" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },
      "2" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },
      "3" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "0" },
      "4" : { "fgColor": "8CD0D3", "bgColor": "3F3F3F", "fontStyle": "0" },
      "5" : { "fgColor": "9F9D6D", "bgColor": "3F3F3F", "fontStyle": "0" },
      "6" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },
      "7" : { "fgColor": "CC9393", "bgColor": "3F3F3F", "fontStyle": "0" },
      "8" : { "fgColor": "93E0E3", "bgColor": "3F3F3F", "fontStyle": "0" },
      "9" : { "fgColor": "DFC47D", "bgColor": "3F3F3F", "fontStyle": "0" },
      "10" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
      "11" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
      "options": {}
    }
  }
}
)myMultiLineJSON");
}

// parses the JSON into the ConfigFromJson data structure
//      wrap the call to this method in the try/catch block, so all JSON errors handled at the same time
bool ConfigFromJson::_parse_config_json(void)
{
    std::string sJsonPath = pcjHelper::wstring_to_utf8(_wsConfigFilePath);
    std::ifstream fstr(sJsonPath);

    nlohmann::json cfgdata = nlohmann::json::parse(fstr);

    // make sure it has the extensions object
    if (!cfgdata.contains("extensions") || !cfgdata["extensions"].is_object())
        throw std::runtime_error("JSON must contain 'extensions' object");

    // make sure it has the lexers object
    if (!cfgdata.contains("lexers") || !cfgdata["lexers"].is_object())
        throw std::runtime_error("JSON must contain 'lexers' object");

    // process each ext in the extensions object, and add the extension/lexer pairs to the map
    for (const auto& item : cfgdata["extensions"].items()) {
        if (!item.value().is_string())
        {
            std::string errmsg = std::string("JSON 'extensions' must contain 'ext': 'lexerName' string-pairs\nProblem with ") + item.key();
            throw std::runtime_error(errmsg);
        }

        // extract key/value strings
        std::string k = item.key();
        std::string v;
        item.value().get_to(v);

        // convert to ws
        std::wstring wsExt = pcjHelper::utf8_to_wstring(k);
        std::wstring wsLex = pcjHelper::utf8_to_wstring(v);

        // store in the map
        _mExt2Lex[wsExt] = wsLex;

    }

    // process each lexer in the lexers object
    for (const auto& oLex : cfgdata["lexers"].items()) {
        if (!oLex.value().is_object())
        {
            std::string errmsg = std::string("JSON 'lexers' must contain 'lexerName': {...} pairs\nProblem with ") + oLex.key();
            throw std::runtime_error(errmsg);
        }

        // process each entry in this lexer object
        t_StylerMap thisStyler;
        for (const auto& stylePair : oLex.value().items()) {
            if (!stylePair.value().is_object())
            {
                std::string errmsg = std::string("JSON lexer info must contain 'styleID': {...} or 'options': {...} pairs\nProblem with lexer=") + oLex.key() + " key=" + stylePair.key();
                throw std::runtime_error(errmsg);
            }
            const std::string sStyleID = stylePair.key();
            const auto& oStyle = stylePair.value();
            if (std::string(stylePair.key()) != "options") {
                ts_StyleInfo thisStyle{ "","","" };

                for (const auto& styleAttrib: oStyle.items()) {
                    std::string thisVal;
                    styleAttrib.value().get_to(thisVal);
                    if (styleAttrib.key() == "fgColor")
                        thisStyle.fgColor = thisVal;
                    else if (styleAttrib.key() == "bgColor")
                        thisStyle.bgColor = thisVal;
                    else if (styleAttrib.key() == "fontStyle") {
                        if (thisVal == "")
                            thisVal = "0";
                        thisStyle.fontStyle = thisVal;
                        int val = std::stoi(thisVal);
                        thisStyle.isBold = val & 0x01;
                        thisStyle.isItalic = val & 0x02;
                        thisStyle.isUnderline = val & 0x04;
                    }
                }

                thisStyler[stylePair.key()] = thisStyle;

                //std::string errmsg = std::string("JSON debugging: ") + oLex.key() + "." + sStyleID + " => " + std::string(oStyle.dump());
                //::MessageBoxA(gNppMetaInfo.hwnd._nppHandle, errmsg.c_str(), "HiddenLexers: Data Debug", MB_OK);
            }
        }
        _mStyles[oLex.key()] = thisStyler;
    }

    return true;
}
