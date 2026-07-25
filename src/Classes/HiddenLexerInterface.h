#pragma once
#include "PluginDefinition.h"
#include "menuCmdID.h"
#include "NppMetaClass.h"
#include "Version.h"
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

	// check if the active file needs to use a hidden lexer
	void check_lexers(Sci_NotifyHeader* notifyHeader);

	// apply the appropriate lexer
	void apply_lexer(std::wstring wsLexerName);

	// set colors for the appropriate lexer
	void set_colors(std::wstring wsLexerName);

	// set keywords for the appropriate lexer
	void set_keywords(std::wstring wsLexerName);

	// set options for the appropriate lexer
	void set_options(std::wstring wsLexerName);

private:
	HWND _curScintillaHwnd;
	std::map<std::wstring, std::wstring> _mapExt2Lexer;
};

extern HiddenLexerInterface gHiddenLexerInterface;
