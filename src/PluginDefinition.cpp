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
#include "NppMetaClass.h"
#include "HiddenLexerInterface.h"
#include "Version.h"
#include "AboutDialog.h"
#include <pathcch.h>

static HANDLE _hModule;

//
// The plugin data that Notepad++ needs
//
FuncItem funcItem[nbFunc];

//
// The data of Notepad++ that you can use in your plugin commands
//
NppData nppData;

//
// Instantiate global NppMetaInfo object, passing in name of plugin
//
NppMetaInfo gNppMetaInfo(VERSION_NAME_WS);

// Instantiate global HiddenLexerInterface
HiddenLexerInterface gHiddenLexerInterface;

//
// Initialize your plugin data here
// It will be called while plugin loading   
void pluginInit(HANDLE hModule)
{
    _hModule = hModule;
}

//
// Here you can do the clean up, save the parameters (if any) for the next session
//
void pluginCleanUp()
{
}

//
// Initialization of metadata useful to the program
//      must come _after_ nppData global is initialized in setInfo
void metaInfoInit()
{
    gNppMetaInfo.populate();
    gHiddenLexerInterface.launch();
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
    setCommand(1, TEXT("Reread Config"), cmdReloadJson, NULL, false);
    setCommand(0, TEXT("Edit Config File: HiddenLexers.json"), cmdEditJson, NULL, false);
    setCommand(2, TEXT(""), NULL, NULL, false);
    setCommand(3, TEXT("About HiddenLexers"), cmdAboutModal, NULL, false);
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
void cmdTBD()
{
    ::MessageBox(NULL, TEXT("Have not yet implemented the action for that command.\nSorry."), TEXT("HiddenLexers: Action Command TBD"), MB_OK);
}

void cmdAboutModal()
{
    // modal freezes the parent
    DialogBoxParam((HINSTANCE)_hModule, MAKEINTRESOURCE(IDD_ABOUTDLG), nppData._nppHandle, (DLGPROC)abtDlgProc, (LPARAM)NULL);
    return;
}

void cmdEditJson()
{
    gHiddenLexerInterface.edit_json();
}

void cmdReloadJson()
{
    gHiddenLexerInterface.launch();
}
