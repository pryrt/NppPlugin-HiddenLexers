#include "HiddenLexerInterface.h"
#include "ConfigFromJson.h"

HiddenLexerInterface::HiddenLexerInterface(void)
{
    _mapExt2Lexer.clear();
    _mapStyles.clear();
    _curScintillaHwnd = nullptr;
}

// launch the hidden lexer interface, so it will start handling the lexers for the active
//		(keep this separate from instantiation, so that code can control when certain setup occurs)

void HiddenLexerInterface::launch(void)
{
    gNppMetaInfo.populate();
    // read config file (if it exists) and populate intitial data structures
    configure();
}

void HiddenLexerInterface::check_lexers(Sci_NotifyHeader* notifyHeader)
{
    // Get the current scintilla
    int which = -1;
    ::SendMessage(nppData._nppHandle, NPPM_GETCURRENTSCINTILLA, 0, (LPARAM)&which);
    if (which == -1)
        return;
    _curScintillaHwnd = (which == 0) ? nppData._scintillaMainHandle : nppData._scintillaSecondHandle;

    // Get Lexer Name
    size_t sz = static_cast<size_t>(::SendMessage(_curScintillaHwnd, SCI_GETLEXERLANGUAGE, 0, static_cast<LPARAM>(NULL)));
    std::string sOldLexer(sz + 1, '\0');
    sz = ::SendMessage(_curScintillaHwnd, SCI_GETLEXERLANGUAGE, 0, reinterpret_cast<LPARAM>(sOldLexer.data()));
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

    // check if extension found in map:
    pcjHelper::delNull(wsFileName);
    pcjHelper::delNull(wsFileExt);
    if (!wsFileExt.empty()) {
        if (wsFileExt.data()[0] == L'.')
            wsFileExt.erase(0, 1);      // remove
        auto map_iter = _mapExt2Lexer.find(wsFileExt);
        if (map_iter != _mapExt2Lexer.end()) {
            // if found, apply that lexer
            apply_lexer(map_iter->second);
        }
    }
}

// apply the appropriate lexer
void HiddenLexerInterface::apply_lexer(std::wstring wsLexerName)
{
    // must create it every time (tried caching it, and it complained)
    LPARAM iLexer = ::SendMessage(nppData._nppHandle, NPPM_CREATELEXER, 0, reinterpret_cast<LPARAM>(wsLexerName.data()));
    // if it's found now (either inherit original find, or inherit the second find after being created)
    if (iLexer) {
        // then use it
        ::SendMessage(_curScintillaHwnd, SCI_SETILEXER, 0, iLexer);
        set_colors(wsLexerName);
        set_keywords(wsLexerName);
        set_options(wsLexerName);
        ::SendMessage(nppData._nppHandle, NPPM_SETSTATUSBAR, STATUSBAR_DOC_TYPE, reinterpret_cast<LPARAM>(wsLexerName.data()));
        // 
        ::SendMessage(_curScintillaHwnd, SCI_COLOURISE, 0, -1);
    }
}

// set colors for the appropriate lexer
void HiddenLexerInterface::set_colors(std::wstring wsLexerName)
{
    std::string sLexerName = pcjHelper::wstring_to_utf8(wsLexerName);
    set_colors(sLexerName);
}

// set colors for the appropriate lexer
void HiddenLexerInterface::set_colors(std::string sLexerName)
{
    auto map_iter = _mapStyles.find(sLexerName);
    if (map_iter == _mapStyles.end())
        return;

    auto rrggbb2ul = [](std::string rrggbb) {
        std::string bbggrr = { rrggbb[4], rrggbb[5], rrggbb[2], rrggbb[3], rrggbb[0], rrggbb[1] };
        return std::stoul(bbggrr, nullptr, 16);
    };

    LPARAM defFG = ::SendMessage(nppData._nppHandle, NPPM_GETEDITORDEFAULTFOREGROUNDCOLOR, 0, 0);
    LPARAM defBG = ::SendMessage(nppData._nppHandle, NPPM_GETEDITORDEFAULTBACKGROUNDCOLOR, 0, 0);

    for (const auto& styleRow : _mapStyles[sLexerName]) {
        std::string sStyleID = styleRow.first;
        WPARAM ulStyleID = static_cast<WPARAM>(std::stoul(sStyleID, nullptr, 10));
        auto oStyleInfo = styleRow.second;
        LPARAM fgVal = (oStyleInfo.fgColor != "") ? static_cast<LPARAM>(rrggbb2ul(oStyleInfo.fgColor)) : defFG;
        LPARAM bgVal = (oStyleInfo.bgColor != "") ? static_cast<LPARAM>(rrggbb2ul(oStyleInfo.bgColor)) : defBG;

        ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, ulStyleID, fgVal);
        ::SendMessage(_curScintillaHwnd, SCI_STYLESETBACK, ulStyleID, bgVal);
        ::SendMessage(_curScintillaHwnd, SCI_STYLESETBOLD, ulStyleID, oStyleInfo.isBold);
        ::SendMessage(_curScintillaHwnd, SCI_STYLESETITALIC, ulStyleID, oStyleInfo.isItalic);
        ::SendMessage(_curScintillaHwnd, SCI_STYLESETUNDERLINE, ulStyleID, oStyleInfo.isUnderline);
    }
}

// set keywords for the appropriate lexer
void HiddenLexerInterface::set_keywords(std::wstring wsLexerName)
{
    std::string sLexerName = pcjHelper::wstring_to_utf8(wsLexerName);
    set_keywords(sLexerName);
}

// set keywords for the appropriate lexer
void HiddenLexerInterface::set_keywords(std::string sLexerName)
{
    // TODO: use data structure to populate keyword sets
    // for now, hardcode keywords
    //::SendMessage(_curScintillaHwnd, SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>("anova by ci clear correlate describe diagplot drop edit exit gen generate graph help if infile input list log lookup oneway pcorr plot predict qnorm regress replace save sebarr set sort stem summ summarize tab tabulate test ttest use"));
    //::SendMessage(_curScintillaHwnd, SCI_SETKEYWORDS, 1, reinterpret_cast<LPARAM>("byte int long float double strL str"));

    auto map_iter = _mapKeywords.find(sLexerName);
    if (map_iter == _mapKeywords.end())
        return;

    for (WPARAM i = 0; i < 9; i++) {
        ::SendMessage(_curScintillaHwnd, SCI_SETKEYWORDS, i, reinterpret_cast<LPARAM>(_mapKeywords[sLexerName][i].c_str()));
    }

}

// set options for the appropriate lexer
void HiddenLexerInterface::set_options(std::wstring wsLexerName)
{
    std::string sLexerName = pcjHelper::wstring_to_utf8(wsLexerName);
    set_options(sLexerName);
}

// set options for the appropriate lexer
void HiddenLexerInterface::set_options(std::string /*sLexerName*/)
{
    return;
}

// read plugin config file and apply to the HiddenLexerInterface map structures
bool HiddenLexerInterface::configure(void)
{
    ConfigFromJson oCfgReader;
    if (oCfgReader.get_status()) {
        _mapExt2Lexer = oCfgReader.getExt2Lex();
        _mapStyles = oCfgReader.getStyles();
        _mapKeywords = oCfgReader.getKeywords();
        // TODO: similar for the styler options
        return true;
    }
    return false;
}

// return the style info for a given lexer and styleID
ts_StyleInfo& HiddenLexerInterface::get_style_info_for_lexer(std::wstring wsLexer, std::wstring wsStyleID)
{
    std::string sLexer = pcjHelper::wstring_to_utf8(wsLexer);
    std::string sStyleID = pcjHelper::wstring_to_utf8(wsStyleID);
    return get_style_info_for_lexer(sLexer, sStyleID);
}

// return the style info for a given lexer and styleID
ts_StyleInfo& HiddenLexerInterface::get_style_info_for_lexer(std::string sLexer, std::string sStyleID)
{
    auto map_iter =  _mapStyles.find(sLexer);
    if (map_iter == _mapStyles.end())
        return lexerInfoNotFound;

    auto style_iter = _mapStyles[sLexer].find(sStyleID);
    if (style_iter == _mapStyles[sLexer].end())
        return lexerInfoNotFound;

    return _mapStyles[sLexer][sStyleID];
}

