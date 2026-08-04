#pragma once
#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "NppMetaClass.h"
#include "Version.h"
#include "ConfigFromJson.h"
#include <windows.h>
#include <wininet.h>
#include <pathcch.h>
#include <string>
#include <vector>
#include <map>

class HiddenLexerInterface {
public:
	// instantiate interface
	HiddenLexerInterface(void);

	// launch the hidden lexer interface, so it will start handling the lexers for the active
	//		(keep this separate from instantiation, so that code can control when certain setup occurs)
	void launch(void);

	// check if the active file needs to use a hidden lexer
	void check_lexers(Sci_NotifyHeader* notifyHeader);

	// apply the appropriate lexer
	void apply_lexer(std::wstring wsLexerName);

	// set colors for the appropriate lexer
	void set_colors(std::wstring wsLexerName);		// set colors for the appropriate lexer
	void set_colors(std::string sLexerName);		// set colors for the appropriate lexer

	// set keywords for the appropriate lexer
	void set_keywords(std::wstring wsLexerName);	// set keywords for the appropriate lexer
	void set_keywords(std::string sLexerName);		// set keywords for the appropriate lexer

	// set options for the appropriate lexer
	void set_options(std::wstring wsLexerName);		// set options for the appropriate lexer
	void set_options(std::string sLexerName);		// set options for the appropriate lexer

	// read plugin config file and apply to the HiddenLexerInterface map structures
	bool configure(void);

	// return the style info for a given lexer and styleID
	ts_StyleInfo& get_style_info_for_lexer(std::wstring wsLexer, std::wstring wsStyleID);	// return the style info for a given lexer and styleID
	ts_StyleInfo& get_style_info_for_lexer(std::string sLexer, std::string sStyleID);		// return the style info for a given lexer and styleID


private:
	HWND _curScintillaHwnd;
	std::map<std::wstring, std::wstring> _mapExt2Lexer;
	std::map<std::string, t_StylerMap> _mapStyles;
	std::map <std::string, std::string[9]> _mapKeywords;
};

extern HiddenLexerInterface gHiddenLexerInterface;
