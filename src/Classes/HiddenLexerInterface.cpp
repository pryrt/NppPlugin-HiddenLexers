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
        // 
    }
}

// set colors for the appropriate lexer
void HiddenLexerInterface::set_colors(std::wstring /*wsLexerName*/)
{
    // TODO: use data structure to decide on colors for right lexer
    // for now, hardcode colors
#define _SCI_RGB(R,G,B) ((R<<0) | (G<<8) | (B<<16))
    const WPARAM
        SCE_STATA_DEFAULT = 0,
        SCE_STATA_COMMENT = 1,
        SCE_STATA_COMMENTLINE = 2,
        SCE_STATA_COMMENTBLOCK = 3,
        SCE_STATA_NUMBER = 4,
        SCE_STATA_OPERATOR = 5,
        SCE_STATA_IDENTIFIER = 6,
        SCE_STATA_STRING = 7,
        SCE_STATA_TYPE = 8,
        SCE_STATA_WORD = 9,
        SCE_STATA_GLOBAL_MACRO = 10,
        SCE_STATA_MACRO = 11
        ;
    LPARAM defFG = ::SendMessage(nppData._nppHandle, NPPM_GETEDITORDEFAULTFOREGROUNDCOLOR, 0, 0);
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_DEFAULT, defFG);
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_COMMENT               , _SCI_RGB(127,159,127)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_COMMENTLINE           , _SCI_RGB(127,159,127)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_COMMENTBLOCK          , _SCI_RGB(127,159,127)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_NUMBER                , _SCI_RGB(140,208,211)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_OPERATOR              , _SCI_RGB(159,157,109)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_IDENTIFIER            , _SCI_RGB(220,220,204)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_STRING                , _SCI_RGB(204,147,147)); //
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_TYPE                  , _SCI_RGB(147,224,227)); //    # KeyWords(1)
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_WORD                  , _SCI_RGB(223,196,125)); //    # KeyWords(0)
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_GLOBAL_MACRO          , _SCI_RGB(206,223,153)); //    # not implemented that I can see in LexStata.cxx
    ::SendMessage(_curScintillaHwnd, SCI_STYLESETFORE, SCE_STATA_MACRO                 , _SCI_RGB(206,223,153)); //    # not implemented that I can see in LexStata.cxx
#undef _SCI_RGB
}

// set keywords for the appropriate lexer
void HiddenLexerInterface::set_keywords(std::wstring /*wsLexerName*/)
{
    // TODO: use data structure to populate keyword sets
    // for now, hardcode keywords
    ::SendMessage(_curScintillaHwnd, SCI_SETKEYWORDS, 0, reinterpret_cast<LPARAM>("anova by ci clear correlate describe diagplot drop edit exit gen generate graph help if infile input list log lookup oneway pcorr plot predict qnorm regress replace save sebarr set sort stem summ summarize tab tabulate test ttest use"));
    ::SendMessage(_curScintillaHwnd, SCI_SETKEYWORDS, 1, reinterpret_cast<LPARAM>("byte int long float double strL str"));

}

// set options for the appropriate lexer
void HiddenLexerInterface::set_options(std::wstring /*wsLexerName*/)
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
        // TODO: similar for the styler info and options
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

