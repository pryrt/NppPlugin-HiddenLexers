//this file is part of notepad++
//Copyright (C)2022 Don HO <don.h@free.fr>
//
//This program is free software; you can redistribute it and/or
//modify it under the terms of the GNU General Public License
//as published by the Free Software Foundation; either
//version 2 of the License, or (at your option) any later version.
//
//This program is distributed in the hope that it will be useful,
//but WITHOUT ANY WARRANTY; without even the implied warranty of
//MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//GNU General Public License for more details.
//
//You should have received a copy of the GNU General Public License
//along with this program; if not, write to the Free Software
//Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

#include "PluginDefinition.h"
#include "menuCmdID.h"

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE /*hModule*/)
{
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of your plugin commands
// You should fill your plugins commands here
void commandMenuInit()
{

    //--------------------------------------------//
    //-- STEP 3. CUSTOMIZE YOUR PLUGIN COMMANDS --//
    //--------------------------------------------//
    // with function :
    // setCommand(int index,                      // zero based number to indicate the order of command
    //            TCHAR *commandName,             // the command name that you want to see in plugin menu
    //            PFUNCPLUGINCMD functionPointer, // the symbol of function (function pointer) associated with this command. The body should be defined below. See Step 4.
    //            ShortcutKey *shortcut,          // optional. Define a shortcut to trigger this command
    //            bool check0nInit                // optional. Make this menu item be checked visually
    //            );
    setCommand(0, TEXT("Hello Notepad++"), hello, NULL, false);
    setCommand(1, TEXT("Hello (with dialog)"), helloDlg, NULL, false);
}

//
// Here you can do the clean up (especially for the shortcut)
//
void commandMenuCleanUp()
{
	// Don't forget to deallocate your shortcut here
}


//
// This function help you to initialize your plugin commands
//
bool setCommand(size_t index, TCHAR *cmdName, PFUNCPLUGINCMD pFunc, ShortcutKey *sk, bool check0nInit) 
{
    if (index >= nbFunc)
        return false;

    if (!pFunc)
        return false;

    lstrcpy(funcItem[index]._itemName, cmdName);
    funcItem[index]._pFunc = pFunc;
    funcItem[index]._init2Check = check0nInit;
    funcItem[index]._pShKey = sk;

    return true;
}

//----------------------------------------------//
//-- STEP 4. DEFINE YOUR ASSOCIATED FUNCTIONS --//
//----------------------------------------------//
void hello()
{
    // Open a new document
    ::SendMessage(nppData._nppHandle, NPPM_MENUCOMMAND, 0, IDM_FILE_NEW);

    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0)?nppData._scintillaMainHandle:nppData._scintillaSecondHandle;

    // Say hello now :
    // Scintilla control has no Unicode mode, so we use (char *) here
    ::SendMessage(curScintilla, SCI_SETTEXT, 0, (LPARAM)"Hello, Notepad++!");
}

void helloDlg()
{
    ::MessageBox(NULL, TEXT("Hello, Notepad++!"), TEXT("HiddenLexer helloDlg()"), MB_OK);
}

#include <string>
// checks if current document is of interest
void check_lexers(Sci_NotifyHeader* notifyHeader)
{
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    // Get Lexer Name
    size_t sz = static_cast<size_t>(::SendMessage(curScintilla, SCI_GETLEXERLANGUAGE, 0, static_cast<LPARAM>(NULL)));
    std::string sOldLexer(sz+1, '\0');
    sz = ::SendMessage(curScintilla, SCI_GETLEXERLANGUAGE, 0, reinterpret_cast<LPARAM>(sOldLexer.data()));
    //bool has_no_lexer_assigned = sOldLexer == "null";

    // Debug Lexer Name and use notifyHeader
    char cMsg[100] = "";
    sprintf_s(cMsg, "NPPN(hwndFrom:%08p, idFrom:%u, code:%u) => %s", notifyHeader->hwndFrom, (unsigned)notifyHeader->idFrom, notifyHeader->code, sOldLexer.data());
    //::MessageBoxA(NULL, cMsg, "HiddenLexer check_lexers", MB_OK);

    // get file name
    std::wstring wsFileName(MAX_PATH + 1, '\0');
    size_t szfn = static_cast<size_t>(::SendMessage(nppData._nppHandle, NPPM_GETFILENAME, static_cast<WPARAM>(MAX_PATH), reinterpret_cast<LPARAM>(wsFileName.data())));
    if (!szfn) {
        wsFileName.resize(2 * MAX_PATH + 1);
        szfn = static_cast<size_t>(::SendMessage(nppData._nppHandle, NPPM_GETFILENAME, static_cast<WPARAM>(MAX_PATH), reinterpret_cast<LPARAM>(wsFileName.data())));
    }
    if (!szfn)
        return;

    // get file ext
    // N++ API BUG: returns "." rather than "md" or "py" or similar.
    //// std::string sFileExt(MAX_PATH + 1, '\0');
    //// size_t szex = static_cast<size_t>(::SendMessage(nppData._nppHandle, NPPM_GETEXTPART, static_cast<WPARAM>(MAX_PATH), reinterpret_cast<LPARAM>(sFileExt.data())));
    //// if (!szex) {
    ////     wsFileName.resize(2 * MAX_PATH + 1);
    ////     szex = static_cast<size_t>(::SendMessage(nppData._nppHandle, NPPM_GETEXTPART, static_cast<WPARAM>(MAX_PATH), reinterpret_cast<LPARAM>(sFileExt.data())));
    //// }
    //// if (!szex)
    ////     return;

}

