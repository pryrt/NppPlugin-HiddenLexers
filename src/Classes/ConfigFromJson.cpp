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
ts_StyleInfo lexerInfoNotFound{ "","","0",false,false,false,false};

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

// returns true if the cfg file and directory already exists, or if it was successfully created; false if there's a problem
bool ConfigFromJson::_cfg_exists_or_created(void)
{
	// if file already exists, great
	if( PathFileExists(_wsConfigFilePath.data()) )
		return true;

	return pcjHelper::write_file_wrapper(_wsConfigFilePath, R"myMultiLineJSON({
    "extensions": {
        "adoc": "asciidoc",
        "md": "markdown",
        "markdown": "markdown",
        "stata": "stata",
        "do": "stata"
    },
    "lexers": {
        "asciidoc": {
            "0  SCE_ASCIIDOC_DEFAULT":        { "fgColor": "", "bgColor": "", "fontStyle": "0" },
            "1  SCE_ASCIIDOC_STRONG1":        { "fgColor": "224466", "bgColor": "", "fontStyle": "1" },
            "2  SCE_ASCIIDOC_STRONG2":        { "fgColor": "224466", "bgColor": "", "fontStyle": "5" },
            "3  SCE_ASCIIDOC_EM1":            { "fgColor": "663300", "bgColor": "", "fontStyle": "2" },
            "4  SCE_ASCIIDOC_EM2":            { "fgColor": "663300", "bgColor": "", "fontStyle": "6" },
            "5  SCE_ASCIIDOC_HEADER1":        { "fgColor": "FFFFFF", "bgColor": "A2B6BF", "fontStyle": "1", "eolFilled": "1" },
            "6  SCE_ASCIIDOC_HEADER2":        { "fgColor": "336193", "bgColor": "DFEAF4", "fontStyle": "1", "eolFilled": "1" },
            "7  SCE_ASCIIDOC_HEADER3":        { "fgColor": "0080C0", "bgColor": "F0F9FF", "fontStyle": "1", "eolFilled": "1" },
            "8  SCE_ASCIIDOC_HEADER4":        { "fgColor": "007F7F", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "9  SCE_ASCIIDOC_HEADER5":        { "fgColor": "408080", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "10 SCE_ASCIIDOC_HEADER6":        { "fgColor": "5183C4", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "11 SCE_ASCIIDOC_ULIST_ITEM":     { "fgColor": "555555", "bgColor": "", "fontStyle": "0" },
            "12 SCE_ASCIIDOC_OLIST_ITEM":     { "fgColor": "555555", "bgColor": "", "fontStyle": "0" },
            "13 SCE_ASCIIDOC_BLOCKQUOTE":     { "fgColor": "A46000", "bgColor": "FFFFC0", "fontStyle": "0" },
            "14 SCE_ASCIIDOC_LINK":           { "fgColor": "0000AA", "bgColor": "", "fontStyle": "4" },
            "15 SCE_ASCIIDOC_CODEBK":         { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "16 SCE_ASCIIDOC_PASSBK":         { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "17 SCE_ASCIIDOC_COMMENT":        { "fgColor": "008000", "bgColor": "", "fontStyle": "0" },
            "18 SCE_ASCIIDOC_COMMENTBK":      { "fgColor": "008000", "bgColor": "", "fontStyle": "0" },
            "19 SCE_ASCIIDOC_LITERAL":        { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "20 SCE_ASCIIDOC_LITERALBK":      { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "21 SCE_ASCIIDOC_ATTRIB":         { "fgColor": "CC00CC", "bgColor": "", "fontStyle": "0" },
            "22 SCE_ASCIIDOC_ATTRIBVAL":      { "fgColor": "CC00CC", "bgColor": "DDDDDD", "fontStyle": "1" },
            "23 SCE_ASCIIDOC_MACRO":          { "fgColor": "CC8800", "bgColor": "", "fontStyle": "2" },
            "options": {},
            "keywords": [ "", "", "", "", "", "", "", "", "" ]
        },
        "markdown": {
            "0  SCE_MARKDOWN_DEFAULT"    : { "fgColor": "", "bgColor": "", "fontStyle": "0" },
            "1  SCE_MARKDOWN_LINE_BEGIN" : { "fgColor": "DADADA", "bgColor": "FF0000", "fontStyle": "0" },
            "2  SCE_MARKDOWN_STRONG1"    : { "fgColor": "224466", "bgColor": "", "fontStyle": "1" },
            "3  SCE_MARKDOWN_STRONG2"    : { "fgColor": "224466", "bgColor": "", "fontStyle": "5" },
            "4  SCE_MARKDOWN_EM1"        : { "fgColor": "663300", "bgColor": "", "fontStyle": "2" },
            "5  SCE_MARKDOWN_EM2"        : { "fgColor": "663300", "bgColor": "", "fontStyle": "6" },
            "6  SCE_MARKDOWN_HEADER1"    : { "fgColor": "FFFFFF", "bgColor": "A2B6BF", "fontStyle": "1", "eolFilled": "1" },
            "7  SCE_MARKDOWN_HEADER2"    : { "fgColor": "336193", "bgColor": "DFEAF4", "fontStyle": "1", "eolFilled": "1" },
            "8  SCE_MARKDOWN_HEADER3"    : { "fgColor": "0080C0", "bgColor": "F0F9FF", "fontStyle": "1", "eolFilled": "1" },
            "9  SCE_MARKDOWN_HEADER4"    : { "fgColor": "007F7F", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "10 SCE_MARKDOWN_HEADER5"    : { "fgColor": "408080", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "11 SCE_MARKDOWN_HEADER6"    : { "fgColor": "5183C4", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
            "12 SCE_MARKDOWN_PRECHAR"    : { "fgColor": "", "bgColor": "", "fontStyle": "0" },
            "13 SCE_MARKDOWN_ULIST_ITEM" : { "fgColor": "555555", "bgColor": "", "fontStyle": "0" },
            "14 SCE_MARKDOWN_OLIST_ITEM" : { "fgColor": "555555", "bgColor": "", "fontStyle": "0" },
            "15 SCE_MARKDOWN_BLOCKQUOTE" : { "fgColor": "A46000", "bgColor": "FFFFC0", "fontStyle": "0" },
            "16 SCE_MARKDOWN_STRIKEOUT"  : { "fgColor": "888888", "bgColor": "", "fontStyle": "0" },
            "17 SCE_MARKDOWN_HRULE"      : { "fgColor": "FFFFFF", "bgColor": "FFC040", "fontStyle": "0" },
            "18 SCE_MARKDOWN_LINK"       : { "fgColor": "0000AA", "bgColor": "", "fontStyle": "4" },
            "19 SCE_MARKDOWN_CODE"       : { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "20 SCE_MARKDOWN_CODE2"      : { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "21 SCE_MARKDOWN_CODEBK"     : { "fgColor": "EEEEEE", "bgColor": "000088", "fontStyle": "0" },
            "options": { "lexer.markdown.header.eolfill": "1" },
            "keywords": [ "", "", "", "", "", "", "", "", "" ]
        },
        "stata": {
            "0  SCE_STATA_DEFAULT"        : { "fgColor": "", "bgColor": "", "fontStyle": "0", "eolFilled": "0" },
            "1  SCE_STATA_COMMENT"        : { "fgColor": "008000", "bgColor": "", "fontStyle": "0" },
            "2  SCE_STATA_COMMENTLINE"    : { "fgColor": "008000", "bgColor": "", "fontStyle": "0" },
            "3  SCE_STATA_COMMENTBLOCK"   : { "fgColor": "008000", "bgColor": "", "fontStyle": "0" },
            "4  SCE_STATA_NUMBER"         : { "fgColor": "FF0000", "bgColor": "", "fontStyle": "0" },
            "5  SCE_STATA_OPERATOR"       : { "fgColor": "000080", "bgColor": "", "fontStyle": "0" },
            "6  SCE_STATA_IDENTIFIER"     : { "fgColor": "000000", "bgColor": "", "fontStyle": "0" },
            "7  SCE_STATA_STRING"         : { "fgColor": "808080", "bgColor": "", "fontStyle": "0" },
            "8  SCE_STATA_TYPE"           : { "fgColor": "FF8000", "bgColor": "", "fontStyle": "0" },
            "9  SCE_STATA_WORD"           : { "fgColor": "0000FF", "bgColor": "", "fontStyle": "0" },
            "10 SCE_STATA_GLOBAL_MACRO"   : { "fgColor": "FF00FF", "bgColor": "", "fontStyle": "0" },
            "11 SCE_STATA_MACRO"          : { "fgColor": "FF00FF", "bgColor": "", "fontStyle": "0" },
            "options": {},
            "keywords": [
                "anova by ci clear correlate describe diagplot drop edit exit gen generate graph help if infile input list log lookup oneway pcorr plot predict qnorm regress replace save sebarr set sort stem summ summarize tab tabulate test ttest use",
                "byte int long float double strL str",
                "", "", "", "", "", "", ""
            ]
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

        std::string sLexerName = oLex.key();

        // process each entry in this lexer object
        t_StylerMap thisStyler;
        for (const auto& stylePair : oLex.value().items()) {
            if (!(stylePair.value().is_object() || stylePair.value().is_array()))
            {
                std::string errmsg = std::string("JSON lexer info must contain 'styleID': {...} or 'options': {...} or 'keywords': [] pairs\nProblem with lexer=") + sLexerName + " key=" + stylePair.key();
                throw std::runtime_error(errmsg);
            }
            const std::string sStyleID = stylePair.key();
            const auto& oStyle = stylePair.value();
            if (std::string(stylePair.key()) == "options") {
                if (!stylePair.value().is_object())
                {
                    std::string errmsg = std::string("JSON lexer info options must contain an object of \"variable\": \"value\" pairs\nProblem with lexer = ") + sLexerName + " key = " + stylePair.key();
                    throw std::runtime_error(errmsg);
                }
                for (const auto& itemOption : stylePair.value().items()) {
                    std::string sOptionName = itemOption.key();
                    std::string sOptionValue = itemOption.value();
                    _mOptions[sLexerName][sOptionName] = sOptionValue;
                }
            }
            else if (std::string(stylePair.key()) == "keywords") {
                if (!stylePair.value().is_array())
                {
                    std::string errmsg = std::string("JSON lexer info keywords must contain array of strings\nProblem with lexer=") + sLexerName + " key=" + stylePair.key();
                    throw std::runtime_error(errmsg);
                }
                for (const auto& itemKeyword : stylePair.value().items()) {
                    auto idx = std::stoul(itemKeyword.key(), nullptr, 10);
                    std::string sKeywords = itemKeyword.value();
                    if (0 <= idx && idx <= 8) {
                        try {
                            _mKeywords[sLexerName][idx] = sKeywords;
                        }
                        catch (std::exception& e) {
                            std::string msg = std::string("JSON lexer exception: ") + e.what();
                            ::MessageBoxA(gNppMetaInfo.hwnd._nppHandle, msg.c_str(), "HiddenLexers: JSON lexer exception", MB_ICONERROR);
                            _status = false;
                        }
                    }
                    else {
                        std::string errmsg = std::string("JSON lexer info keywords must contain array of 9 strings\nProblem with lexer=") + sLexerName + " key=" + stylePair.key() + " idx=" + itemKeyword.key();
                        throw std::runtime_error(errmsg);
                    }
                }
            }
            else {  // actual style
                ts_StyleInfo thisStyle{ "","","0", false, false, false, false};

                for (const auto& styleAttrib : oStyle.items()) {
                    std::string thisVal;
                    styleAttrib.value().get_to(thisVal);
                    if (styleAttrib.key() == "fgColor")
                        thisStyle.fgColor = thisVal;
                    else if (styleAttrib.key() == "bgColor")
                        thisStyle.bgColor = thisVal;
                    else if (styleAttrib.key() == "eolFilled") {
                        if (thisVal == "")
                            thisVal = "0";
                        int val = std::stoi(thisVal);
                        thisStyle.isEOLFilled = val;
                    }
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
        _mStyles[sLexerName] = thisStyler;
    }

    return true;
}
