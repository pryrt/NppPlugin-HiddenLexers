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
};

extern HiddenLexerInterface gHiddenLexerInterface;
