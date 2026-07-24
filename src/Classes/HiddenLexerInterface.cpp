#include "HiddenLexerInterface.h"
// nlohmann/json.hpp
#include "json.hpp"

HiddenLexerInterface::HiddenLexerInterface(void)
{
	gNppMetaInfo.populate();
	// TODO: read config file (if it exists) and populate intitial data structures
}

void HiddenLexerInterface::check_lexers(Sci_NotifyHeader* notifyHeader)
{
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    HWND curScintilla = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    // Get Lexer Name
    size_t sz = static_cast<size_t>(::SendMessage(curScintilla, SCI_GETLEXERLANGUAGE, 0, static_cast<LPARAM>(NULL)));
    std::string sOldLexer(sz + 1, '\0');
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
    // N++ NPPM_GETEXTPART BUG: returns "." rather than "md" or "py" or similar, so just use PathCch instead.
    PCWSTR extensionPtr = nullptr;
    HRESULT hr = PathCchFindExtension(wsFileName.data(), wsFileName.length(), &extensionPtr);
    if (hr != S_OK)
        return;
    std::wstring wsFileExt = extensionPtr;

    // make a debug string
    pcjHelper::delNull(wsFileName);
    pcjHelper::delNull(wsFileExt);
    std::wstring wsMsg = wsFileName;
    if (!wsFileExt.empty()) {
        if (wsFileExt.data()[0] == L'.')
            wsFileExt.erase(0, 1);      // remove
        wsMsg += std::wstring(L" => ") + wsFileExt;
    }
    ::MessageBox(nppData._nppHandle, wsMsg.data(), L"HiddenLexer check_lexers", MB_OK);
}
