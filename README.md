# HiddenLexers

A Notepad++ Plugin that allows users to enable 'hidden' Lexilla lexers in Notepad++.

## Explanation

Notepad++ ships with 90+ language "lexers" (syntax highlighters) enabled from the Lexilla library.  But Lexilla actually includes many more lexers that Notepad++ doesn't activate. Based on an old script for the PythonScript plugin, this new Plugin will allow users to configure one or more of those hidden lexers to be used for particular.

## Installation

You can install the plugin using Notepad++'s **Plugins Admin** (TODO), or by unzipping the appropriate archive from the [latest release](https://github.com/pryrt/NppPlugin-HiddenLexers/releases/latest), so that `HiddenLexers.dll` ends up in the `c:\Program Files\Notepad++\plugins\HiddenLexers\` directory (or equivalent, for your installation's location).  (The files in the `docs\` folder from the zipfile could also be extracted into `c:\Program Files\Notepad++\plugins\HiddenLexers\docs\` directory, but that's not required).

## Commands

- **Plugins > HiddenLexers > Edit Config File: HiddenLexers.json**: opens the `HiddenLexers.json` config file inside Notepad++, so you can edit the config
    - when you save the file in Notepad++, the plugin should automatically reload the config, so the next time you click in a tab that uses a HiddenLexer, it should use the updated definition
- **Plugins > HiddenLexers > Reload Config**: reload the config file
    - the next time you click in a tab that uses a HiddenLexer, it should use the updated definition
    - useful in case it's been edited outside Notepad++ or in a different instance of Notepad++
- **Plugins > HiddenLexers > About**: show copyright, license, library info, and a link to the plugin's repository

## Config files

The configuration file for the plugin will be in `plugins\config\HiddenLexers\` as `HiddenLexer.json`.  If the directory or file is missing, the plugin will create it when Notepad+++ is launching.

### `HiddenLexers.json`

JSON file to pick which lexers to associate with which extensions, and to associate style and keywords and options with each lexer.

- The `extensions` section needs to be a map of file extension (no dot) to lexer name
    - multiple extensions can point to the same lexer name
    - there cannot be multiple copies of the same extension (each extension can only be handled by one lexer)
- The `lexers` section has the bulk of the data
    - `"lexername": { ... }` holds the info for a given lexer
        - `"0": {...}` holds the StyleID to style-info mapping
            - because JSON doesn't allow comments (and the JSON library I have access to doesn't allow JSONC or JSON5),
              I made it so that the StyleID key can have extra text after the integer part of the string,
              so you can include the SCE_... constant name, if it helps you
            - it is up to the user to explore [SciLexer.h](https://github.com/notepad-plus-plus/notepad-plus-plus/blob/master/lexilla/include/SciLexer.h) to get the values for the `SCE_*` constants
            - `"fgColor": "..."`: leave empty string to inherit the active Theme's default foreground; otherwise, use a standard RRGGBB hex for the foreground color
            - `"bgColor": "..."`: leave empty string to inherit the active Theme's default background; otherwise, use a standard RRGGBB hex for the background color
            - `"fontStyle": "..."`: uses Notepad++'s stylers.xml style integer, so "0" indicates no extra styling, "1" indicates bold, "2" indicates italic, "4" indicates underline, and sums (like "3","5","6","7") indicate combinations (so italic+underline = "2" + "4" = "6").
            - `"eolFilled": "0"`: should be "" or "0" or "1".  If "1", will set lexilla to continue styling past the end-of-line (EOL) to the edge of the editor, if the lexer supports that.
        - `"keywords": [...]` lists the keywords: the array must contain exactly 9 strings, which are space-separated lists of keywords (similar to what goes in langs.xml)
            - it is up to the user to explore [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers) file(s) to determine what keyword list(s) are needed (and eventually, what options are supported) for your enabled hidden lexers.
        - `"options": { ... }` is an object of `"optionName": "optionValue"` pairs.
            - it is up to the user to explore [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers) file(s) to determine what what options are supported for your enabled hidden lexers.

#### Example: Default (stylers.xml)-compatible Colors
```
{
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
```

#### Example: DarkModeDefault-compatible Colors
```
{
  "extensions": {
    "stata": "stata",
    "do": "stata",
    "adoc": "asciidoc",
    "markdown": "markdown"
  },
  "lexers": {
    "asciidoc": {
      "0  SCE_ASCIIDOC_DEFAULT":        { "fgColor": "", "bgColor": "", "fontStyle": "0" },
      "1  SCE_ASCIIDOC_STRONG1":        { "fgColor": "", "bgColor": "", "fontStyle": "1" },
      "2  SCE_ASCIIDOC_STRONG2":        { "fgColor": "", "bgColor": "", "fontStyle": "5" },
      "3  SCE_ASCIIDOC_EM1":            { "fgColor": "", "bgColor": "", "fontStyle": "2" },
      "4  SCE_ASCIIDOC_EM2":            { "fgColor": "", "bgColor": "", "fontStyle": "6" },
      "5  SCE_ASCIIDOC_HEADER1":        { "fgColor": "CC0000", "bgColor": "", "fontStyle": "1", "eolFilled": "1" },
      "6  SCE_ASCIIDOC_HEADER2":        { "fgColor": "CC3333", "bgColor": "4F4F4F", "fontStyle": "1", "eolFilled": "1" },
      "7  SCE_ASCIIDOC_HEADER3":        { "fgColor": "CC7777", "bgColor": "5F5F5F", "fontStyle": "1", "eolFilled": "1" },
      "8  SCE_ASCIIDOC_HEADER4":        { "fgColor": "CCbbbb", "bgColor": "6F6F6F", "fontStyle": "1", "eolFilled": "1" },
      "9  SCE_ASCIIDOC_HEADER5":        { "fgColor": "CCffff", "bgColor": "7F7F7F", "fontStyle": "1", "eolFilled": "1" },
      "10 SCE_ASCIIDOC_HEADER6":        { "fgColor": "FFFFFF", "bgColor": "8F8F8F", "fontStyle": "1", "eolFilled": "1" },
      "11 SCE_ASCIIDOC_ULIST_ITEM":     { "fgColor": "0000CC", "bgColor": "", "fontStyle": "0" },
      "12 SCE_ASCIIDOC_OLIST_ITEM":     { "fgColor": "0000CC", "bgColor": "", "fontStyle": "0" },
      "13 SCE_ASCIIDOC_BLOCKQUOTE":     { "fgColor": "00CC00", "bgColor": "", "fontStyle": "0" },
      "14 SCE_ASCIIDOC_LINK":           { "fgColor": "", "bgColor": "", "fontStyle": "4" },
      "15 SCE_ASCIIDOC_CODEBK":         { "fgColor": "00CC00", "bgColor": "", "fontStyle": "0" },
      "16 SCE_ASCIIDOC_PASSBK":         { "fgColor": "00CC00", "bgColor": "", "fontStyle": "0" },
      "17 SCE_ASCIIDOC_COMMENT":        { "fgColor": "00CC33", "bgColor": "", "fontStyle": "0" },
      "18 SCE_ASCIIDOC_COMMENTBK":      { "fgColor": "00CC33", "bgColor": "", "fontStyle": "0" },
      "19 SCE_ASCIIDOC_LITERAL":        { "fgColor": "CCCC00", "bgColor": "", "fontStyle": "0" },
      "20 SCE_ASCIIDOC_LITERALBK":      { "fgColor": "CCCC00", "bgColor": "", "fontStyle": "0" },
      "21 SCE_ASCIIDOC_ATTRIB":         { "fgColor": "CC00CC", "bgColor": "", "fontStyle": "0" },
      "22 SCE_ASCIIDOC_ATTRIBVAL":      { "fgColor": "CC00CC", "bgColor": "7F7F7F", "fontStyle": "0" },
      "23 SCE_ASCIIDOC_MACRO":          { "fgColor": "FFFF00", "bgColor": "", "fontStyle": "7" },
      "options": {},
      "keywords": [ "", "", "", "", "", "", "", "", "" ]
    },
    "stata": {
      "0  SCE_STATA_DEFAULT"        : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },
      "1  SCE_STATA_COMMENT"        : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "1" },
      "2  SCE_STATA_COMMENTLINE"    : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "2" },
      "3  SCE_STATA_COMMENTBLOCK"   : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "3" },
      "4  SCE_STATA_NUMBER"         : { "fgColor": "8CD0D3", "bgColor": "3F3F3F", "fontStyle": "4" },
      "5  SCE_STATA_OPERATOR"       : { "fgColor": "9F9D6D", "bgColor": "3F3F3F", "fontStyle": "5" },
      "6  SCE_STATA_IDENTIFIER"     : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "6" },
      "7  SCE_STATA_STRING"         : { "fgColor": "CC9393", "bgColor": "", "fontStyle": "7" },
      "8  SCE_STATA_TYPE"           : { "fgColor": "93E0E3", "bgColor": "3F3F3F", "fontStyle": "0" },
      "9  SCE_STATA_WORD"           : { "fgColor": "DFC47D", "bgColor": "3F3F3F", "fontStyle": "0" },
      "10 SCE_STATA_GLOBAL_MACRO"   : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
      "11 SCE_STATA_MACRO"          : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
      "options": {},
      "keywords": [
        "anova by ci clear correlate describe diagplot drop edit exit gen generate graph help if infile input list log lookup oneway pcorr plot predict qnorm regress replace save sebarr set sort stem summ summarize tab tabulate test ttest use",
        "byte int long float double strL str",
        "", "", "", "", "", "", ""
      ]
    },
    "markdown": {
        "0  SCE_MARKDOWN_DEFAULT"    : { "fgColor": "", "bgColor": "", "fontStyle": "0" },
        "1  SCE_MARKDOWN_LINE_BEGIN" : { "fgColor": "DADADA", "bgColor": "", "fontStyle": "0" },
        "2  SCE_MARKDOWN_STRONG1"    : { "fgColor": "EECCAA", "bgColor": "", "fontStyle": "1" },
        "3  SCE_MARKDOWN_STRONG2"    : { "fgColor": "EECCAA", "bgColor": "4F4F4F", "fontStyle": "1" },
        "4  SCE_MARKDOWN_EM1"        : { "fgColor": "AADDFF", "bgColor": "", "fontStyle": "2" },
        "5  SCE_MARKDOWN_EM2"        : { "fgColor": "AADDFF", "bgColor": "4F4F4F", "fontStyle": "2" },
        "6  SCE_MARKDOWN_HEADER1"    : { "fgColor": "FFFFFF", "bgColor": "8F8F8F", "fontStyle": "1", "eolFilled": "1" },
        "7  SCE_MARKDOWN_HEADER2"    : { "fgColor": "CCffff", "bgColor": "7F7F7F", "fontStyle": "1", "eolFilled": "1" },
        "8  SCE_MARKDOWN_HEADER3"    : { "fgColor": "CCbbbb", "bgColor": "6F6F6F", "fontStyle": "1", "eolFilled": "1" },
        "9  SCE_MARKDOWN_HEADER4"    : { "fgColor": "CC7777", "bgColor": "5F5F5F", "fontStyle": "1", "eolFilled": "1" },
        "10 SCE_MARKDOWN_HEADER5"    : { "fgColor": "CC3333", "bgColor": "4F4F4F", "fontStyle": "1", "eolFilled": "1" },
        "11 SCE_MARKDOWN_HEADER6"    : { "fgColor": "CC0000", "bgColor": "474747", "fontStyle": "1", "eolFilled": "1" },
        "12 SCE_MARKDOWN_PRECHAR"    : { "fgColor": "5F5F5F", "bgColor": "4F4F4F", "fontStyle": "0" },
        "13 SCE_MARKDOWN_ULIST_ITEM" : { "fgColor": "0000CC", "bgColor": "4F4F4F", "fontStyle": "0" },
        "14 SCE_MARKDOWN_OLIST_ITEM" : { "fgColor": "0000CC", "bgColor": "4F4F4F", "fontStyle": "0" },
        "15 SCE_MARKDOWN_BLOCKQUOTE" : { "fgColor": "00CC00", "bgColor": "4F4F4F", "fontStyle": "0" },
        "16 SCE_MARKDOWN_STRIKEOUT"  : { "fgColor": "6F6F6F", "bgColor": "", "fontStyle": "0" },
        "17 SCE_MARKDOWN_HRULE"      : { "fgColor": "FFFFFF", "bgColor": "0020C0", "fontStyle": "0" },
        "18 SCE_MARKDOWN_LINK"       : { "fgColor": "8F8FFF", "bgColor": "", "fontStyle": "4" },
        "19 SCE_MARKDOWN_CODE"       : { "fgColor": "FFFF00", "bgColor": "6F6F6F", "fontStyle": "0" },
        "20 SCE_MARKDOWN_CODE2"      : { "fgColor": "FFFF00", "bgColor": "6F6F6F", "fontStyle": "0" },
        "21 SCE_MARKDOWN_CODEBK"     : { "fgColor": "FFFF00", "bgColor": "6F6F6F", "fontStyle": "0" },
        "options": { "lexer.markdown.header.eolfill": "1" },
        "keywords": [ "", "", "", "", "", "", "", "", "" ]
    }

  }
}
```

### Known Properties

These are properties that I could easily extract from the source code... this list will likely
get out-of-date, and may not be complete, but it gives you a starting place... Always check the
current [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers)
for the properties in your desired language.

|	Lexer name								|	Option											|	Description from [SciTEDoc](https://scintilla.org/SciTEDoc.html#property-xml.auto.close.tags)	|
|-------------------------------------------|---------------------------------------------------|-------------------------------------------------|
|	abl										|	fold											|	Folding is turned on by setting fold=1.	|
|	abl										|	fold.abl.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	abl										|	fold.abl.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	abl										|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	abl										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	as, asm									|	fold											|	Folding is turned on by setting fold=1.	|
|	as, asm									|	fold.asm.comment.explicit						|	This option enables folding explicit fold points when using the Asm lexer. Explicit fold points allows adding extra folding by placing a ;{ comment at the start and a ;} at the end of a section that should fold.	|
|	as, asm									|	fold.asm.comment.multiline						|	Set this property to 1 to enable folding multi-line comments.	|
|	as, asm									|	fold.asm.explicit.anywhere						|	Set this property to 1 to enable explicit fold points anywhere, not just in line comments.	|
|	as, asm									|	fold.asm.explicit.end							|	The string to use for explicit fold end points, replacing the standard ;}.	|
|	as, asm									|	fold.asm.explicit.start							|	The string to use for explicit fold start points, replacing the standard ;{.	|
|	as, asm									|	fold.asm.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	as, asm									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	as, asm									|	lexer.as.comment.character						|	Overrides the default comment character (which is ';' for asm and '#' for as).	|
|	as, asm									|	lexer.asm.comment.delimiter						|	Character used for COMMENT directive's delimiter, replacing the standard "~".	|
|	baan									|	fold											|	Folding is turned on by setting fold=1.	|
|	baan									|	fold.baan.inner.level							|	Set this property to 1 to enable folding of inner levels of select statements.Disabled by default. case and if statements are also eligible	|
|	baan									|	fold.baan.keywords.based						|	Set this property to 0 to disable keywords based folding, which is folding based on for, if, on (case), repeat, select, while and fold ends based on endfor, endif, endcase, until, endselect, endwhile respectively.Also folds declarations which are grouped together.	|
|	baan									|	fold.baan.sections								|	Set this property to 0 to disable folding of Main Sections as well as Sub Sections.	|
|	baan									|	fold.baan.syntax.based							|	Set this property to 0 to disable syntax based folding, which is folding based on '{' &amp; '('.	|
|	baan									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	baan									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	baan									|	fold.preprocessor								|	This option enables folding preprocessor directives when using the C++ lexer. Includes C#'s explicit #region and #endregion folding directives.	|
|	baan									|	lexer.baan.styling.within.preprocessor			|	For Baan code, determines whether all preprocessor code is styled in the preprocessor style (0, the default) or only from the initial # to the end of the command word(1).	|
|	bash									|	fold											|	Folding is turned on by setting fold=1.	|
|	bash									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	bash									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	bash									|	lexer.bash.command.substitution					|	Set how to highlight $() command substitution. 0 (the default) highlighted as backticks. 1 highlighted inside. 2 highlighted inside with extra scope tracking.	|
|	bash									|	lexer.bash.nested.backticks						|	Set this property to 0 to disable nested backquoted command substitution.	|
|	bash									|	lexer.bash.special.parameter					|	Set shell (default is Bash) special parameters.	|
|	bash									|	lexer.bash.styling.inside.backticks				|	Set this property to 1 to highlight shell expansions inside backticks.	|
|	bash									|	lexer.bash.styling.inside.heredoc				|	Set this property to 1 to highlight shell expansions inside here document.	|
|	bash									|	lexer.bash.styling.inside.parameter				|	Set this property to 1 to highlight shell expansions inside ${} parameter expansion.	|
|	bash									|	lexer.bash.styling.inside.string				|	Set this property to 1 to highlight shell expansions inside string.	|
|	blitzbasic, purebasic, freebasic		|	fold											|	Folding is turned on by setting fold=1.	|
|	blitzbasic, purebasic, freebasic		|	fold.basic.comment.explicit						|	This option enables folding explicit fold points when using the Basic lexer. Explicit fold points allows adding extra folding by placing a ;{ (BB/PB) or '{ (FB) comment at the start and a ;} (BB/PB) or '} (FB) at the end of a section that should be folded.	|
|	blitzbasic, purebasic, freebasic		|	fold.basic.explicit.anywhere					|	Set this property to 1 to enable explicit fold points anywhere, not just in line comments.	|
|	blitzbasic, purebasic, freebasic		|	fold.basic.explicit.end							|	The string to use for explicit fold end points, replacing the standard ;} (BB/PB) or '} (FB).	|
|	blitzbasic, purebasic, freebasic		|	fold.basic.explicit.start						|	The string to use for explicit fold start points, replacing the standard ;{ (BB/PB) or '{ (FB).	|
|	blitzbasic, purebasic, freebasic		|	fold.basic.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	blitzbasic, purebasic, freebasic		|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	cil										|	fold											|	Folding is turned on by setting fold=1.	|
|	cil										|	fold.cil.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	cil										|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	cil										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	coffeescript							|	fold.coffeescript.comment						|	Set to 1 to allow folding of comment blocks in CoffeeScript.	|
|	cpp, cppnocase							|	fold											|	Folding is turned on by setting fold=1.	|
|	cpp, cppnocase							|	fold.at.else									|	This option enables C++ folding on a "} else {" line of an if statement.	|
|	cpp, cppnocase							|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	cpp, cppnocase							|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	cpp, cppnocase							|	fold.cpp.comment.explicit						|	Set this property to 0 to disable folding explicit fold points when fold.comment=1.	|
|	cpp, cppnocase							|	fold.cpp.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	cpp, cppnocase							|	fold.cpp.explicit.anywhere						|	Set this property to 1 to enable explicit fold points anywhere, not just in line comments.	|
|	cpp, cppnocase							|	fold.cpp.explicit.end							|	The string to use for explicit fold end points, replacing the standard //}.	|
|	cpp, cppnocase							|	fold.cpp.explicit.start							|	The string to use for explicit fold start points, replacing the standard //{.	|
|	cpp, cppnocase							|	fold.cpp.preprocessor.at.else					|	This option enables folding on a preprocessor #else or #endif line of an #if statement.	|
|	cpp, cppnocase							|	fold.cpp.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	cpp, cppnocase							|	fold.preprocessor								|	This option enables folding preprocessor directives when using the C++ lexer. Includes C#'s explicit #region and #endregion folding directives.	|
|	cpp, cppnocase							|	lexer.cpp.allow.dollars							|	Set to 0 to disallow the '$' character in identifiers with the cpp lexer.	|
|	cpp, cppnocase							|	lexer.cpp.allow.hashes							|	Set to 1 to allow the '#' character in identifiers.	|
|	cpp, cppnocase							|	lexer.cpp.backquoted.strings					|	Set how to highlighting back-quoted strings. 0 (the default) no highlighting. 1 highlighted as Go raw string. 2 highlighted as JavaScript template literal.	|
|	cpp, cppnocase							|	lexer.cpp.enable.preprocessor					|	Set to 0 to disable recognition of preprocessor directives.	|
|	cpp, cppnocase							|	lexer.cpp.escape.sequence						|	Set to 1 to enable highlighting of escape sequences in strings	|
|	cpp, cppnocase							|	lexer.cpp.hashquoted.strings					|	Set to 1 to enable highlighting of hash-quoted strings.	|
|	cpp, cppnocase							|	lexer.cpp.track.preprocessor					|	Set to 1 to interpret #if/#else/#endif to grey out code that is not active.	|
|	cpp, cppnocase							|	lexer.cpp.triplequoted.strings					|	Set to 1 to enable highlighting of triple-quoted strings.	|
|	cpp, cppnocase							|	lexer.cpp.update.preprocessor					|	Set to 1 to update preprocessor definitions when #define found.	|
|	cpp, cppnocase							|	lexer.cpp.verbatim.strings.allow.escapes		|	Set to 1 to allow verbatim strings to contain escape sequences.	|
|	cpp, cppnocase							|	styling.within.preprocessor						|	For C++ code, determines whether all preprocessor code is styled in the preprocessor style (0, the default) or only from the initial # to the end of the command word(1).	|
|	css										|	lexer.css.hss.language							|	Set to 1 for HSS (.hss)	|
|	css										|	lexer.css.less.language							|	Set to 1 for Less CSS (.less)	|
|	css										|	lexer.css.scss.language							|	Set to 1 for Sassy CSS (.scss)	|
|	d										|	fold											|	Folding is turned on by setting fold=1.	|
|	d										|	fold.at.else									|	This option enables C++ folding on a "} else {" line of an if statement.	|
|	d										|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	d										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	d										|	fold.d.comment.explicit							|	Set this property to 0 to disable folding explicit fold points when fold.comment=1.	|
|	d										|	fold.d.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	d										|	fold.d.explicit.anywhere						|	Set this property to 1 to enable explicit fold points anywhere, not just in line comments.	|
|	d										|	fold.d.explicit.end								|	The string to use for explicit fold end points, replacing the standard //}.	|
|	d										|	fold.d.explicit.start							|	The string to use for explicit fold start points, replacing the standard //{.	|
|	d										|	fold.d.syntax.based								|	Set this property to 0 to disable syntax based folding.	|
|	d										|	lexer.d.fold.at.else							|	This option enables D folding on a "} else {" line of an if statement.	|
|	dart									|	fold											|	Folding is turned on by setting fold=1.	|
|	dataflex								|	fold.dataflex.compilerlist						|	Set to 1 for enabling the code folding feature in *.prn files	|
|	edifact									|	lexer.edifact.highlight.un.all					|	Set to 0 to highlight only UNA segments, or 1 to highlight all UNx segments.	|
|	errorlist								|	lexer.errorlist.escape.sequences				|	Set to 1 to interpret escape sequences.	|
|	errorlist								|	lexer.errorlist.value.separate					|	For lines in the output pane that are matches from Find in Files or GCC-stylediagnostics, style the path and line number separately from the rest of theline with style 21 used for the rest of the line.This allows matched text to be more easily distinguished from its location.	|
|	escseq									|	lexer.escseq.colour.text						|	Set to 1 to colour text following the escape sequences.	|
|	flagship								|	lexer.flagship.styling.within.preprocessor		|	For Harbour code, determines whether all preprocessor code is styled in the preprocessor style (0) or only from the initial # to the end of the command word(1, the default). It also determines how to present text, dump, and disabled code.	|
|	fsharp									|	fold											|	Folding is turned on by setting fold=1.	|
|	fsharp									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	fsharp									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	fsharp									|	fold.fsharp.comment.multiline					|	Setting this option to 0 disables folding of grouped line comments in F# files when fold.comment=1.	|
|	fsharp									|	fold.fsharp.comment.stream						|	Setting this option to 0 disables folding of ML-style comments in F# files when fold.comment=1.	|
|	fsharp									|	fold.fsharp.imports								|	Setting this option to 0 disables folding of F# import declarations.	|
|	fsharp									|	fold.fsharp.preprocessor						|	Setting this option to 1 enables folding of F# compiler directives.	|
|	fsharp									|	fold.fsharp.quotes								|	Setting this option to 1 enables folding of multi-line strings in F# files.	|
|	gdscript								|	fold											|	Folding is turned on by setting fold=1.	|
|	gdscript								|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	gdscript								|	fold.gdscript.quotes							|	This option enables folding multi-line quoted strings when using the GDScript lexer.	|
|	gdscript								|	lexer.gdscript.keywords2.no.sub.identifiers		|	When enabled, it will not style keywords2 items that are used as a sub-identifier. Example: when set, will not highlight "foo.open" when "open" is a keywords2 item.	|
|	gdscript								|	lexer.gdscript.literals.binary					|	Set to 0 to not recognise binary and octal literals: 0b1011 0o712.	|
|	gdscript								|	lexer.gdscript.strings.over.newline				|	Set to 1 to allow strings to span newline characters.	|
|	gdscript								|	lexer.gdscript.unicode.identifiers				|	Set to 0 to not recognise Unicode identifiers.	|
|	gdscript								|	lexer.gdscript.whinge.level						|	For GDScript code, checks whether indenting is consistent. The default, 0 turns off indentation checking, 1 checks whether each line is potentially inconsistent with the previous line, 2 checks whether any space characters occur before a tab character in the indentation, 3 checks whether any spaces are in the indentation, and 4 checks for any tab characters in the indentation. 1 is a good level to use.	|
|	haskell, literatehaskell				|	fold											|	Folding is turned on by setting fold=1.	|
|	haskell, literatehaskell				|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	haskell, literatehaskell				|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	haskell, literatehaskell				|	fold.haskell.imports							|	Set to 1 to enable folding of import declarations	|
|	haskell, literatehaskell				|	lexer.haskell.allow.hash						|	Set to 0 to disallow the '#' character at the end of identifiers and literals with the haskell lexer (GHC -XMagicHash extension)	|
|	haskell, literatehaskell				|	lexer.haskell.allow.questionmark				|	Set to 1 to allow the '?' character at the start of identifiers with the haskell lexer (GHC &amp; Hugs -XImplicitParams extension)	|
|	haskell, literatehaskell				|	lexer.haskell.allow.quotes						|	Set to 0 to disable highlighting of Template Haskell name quotations and promoted constructors (GHC -XTemplateHaskell and -XDataKinds extensions)	|
|	haskell, literatehaskell				|	lexer.haskell.cpp								|	Set to 0 to disable C-preprocessor highlighting (-XCPP extension)	|
|	haskell, literatehaskell				|	lexer.haskell.import.safe						|	Set to 0 to disallow "safe" keyword in imports (GHC -XSafe, -XTrustworthy, -XUnsafe extensions)	|
|	haskell, literatehaskell				|	styling.within.preprocessor						|	For C++ code, determines whether all preprocessor code is styled in the preprocessor style (0, the default) or only from the initial # to the end of the command word(1).	|
|	hollywood								|	fold											|	Folding is turned on by setting fold=1.	|
|	hollywood								|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	hypertext, xml, phpscript				|	asp.default.language							|	Script in ASP code is initially assumed to be in JavaScript. To change this to VBScript set asp.default.language to 2. Python is 3.	|
|	hypertext, xml, phpscript				|	fold											|	Folding is turned on by setting fold=1.	|
|	hypertext, xml, phpscript				|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	hypertext, xml, phpscript				|	fold.html										|	Folding is turned on or off for HTML and XML files with this option. The fold option must also be on for folding to occur.	|
|	hypertext, xml, phpscript				|	fold.html.preprocessor							|	Folding is turned on or off for scripts embedded in HTML files with this option. The default is on.	|
|	hypertext, xml, phpscript				|	fold.hypertext.comment							|	Allow folding for comments in scripts embedded in HTML. The default is off.	|
|	hypertext, xml, phpscript				|	fold.hypertext.heredoc							|	Allow folding for heredocs in scripts embedded in HTML. The default is off.	|
|	hypertext, xml, phpscript				|	fold.xml.at.tag.open							|	Enable folding for XML at the start of open tag. The default is off.	|
|	hypertext, xml, phpscript				|	html.tags.case.sensitive						|	For XML and HTML, setting this property to 1 will make tags match in a case sensitive way which is the expected behaviour for XML and XHTML.	|
|	hypertext, xml, phpscript				|	lexer.html.allow.asp							|	Set to 0 to disable ASP in HTML.	|
|	hypertext, xml, phpscript				|	lexer.html.allow.php							|	Set to 0 to disable PHP in HTML, 1 to accept &lt;?php and &lt;?=, 2 to also accept &lt;?.The default is 2.	|
|	hypertext, xml, phpscript				|	lexer.html.django								|	Set to 1 to enable the django template language.	|
|	hypertext, xml, phpscript				|	lexer.html.mako									|	Set to 1 to enable the mako template language.	|
|	hypertext, xml, phpscript				|	lexer.xml.allow.asp								|	Set to 0 to disable ASP in XML.	|
|	hypertext, xml, phpscript				|	lexer.xml.allow.php								|	Set to 0 to disable PHP in XML, 1 to accept &lt;?php and &lt;?=, 2 to also accept &lt;?.The default is 2.	|
|	hypertext, xml, phpscript				|	lexer.xml.allow.scripts							|	Set to 0 to disable scripts in XML.	|
|	hypertext, xml, phpscript				|	xml.auto.close.tags								|	For XML and HTML, setting this property to 1 will automatically insert the corresponding end tag when '&gt;' is typed to end a start tag. Type "&lt;td&gt;" and the result will be "&lt;td&gt;&lt;/td&gt;" with the caret placed between the tags.	|
|	json									|	fold											|	Folding is turned on by setting fold=1.	|
|	json									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	json									|	lexer.json.allow.comments						|	Set to 1 to enable highlighting of line/block comments in JSON	|
|	json									|	lexer.json.escape.sequence						|	Set to 1 to enable highlighting of escape sequences in strings	|
|	julia									|	fold											|	Folding is turned on by setting fold=1.	|
|	julia									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	julia									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	julia									|	fold.julia.docstring							|	Fold multiline triple-doublequote strings, usually used to document a function or type above the definition.	|
|	julia									|	fold.julia.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	julia									|	lexer.julia.highlight.lexerror					|	This option enables highlighting of syntax error int character or number definition.	|
|	julia									|	lexer.julia.highlight.typeannotation			|	This option enables highlighting of the type identifier after `::`.	|
|	lua										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	markdown								|	lexer.markdown.header.eolfill					|	Set to 1 to highlight all ATX header text.	|
|	nim										|	fold											|	Folding is turned on by setting fold=1.	|
|	nim										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	nim										|	lexer.nim.raw.strings.highlight.ident			|	Set to 1 to enable highlighting generalized raw string identifiers. Generalized raw string identifiers are anything other than r (or R).	|
|	nix										|	fold											|	Folding is turned on by setting fold=1.	|
|	nsis									|	nsis.ignorecase									|	Set to 1 to ignore case for NSIS.	|
|	nsis									|	nsis.uservars									|	Set to 1 to recognise user defined variables in NSIS.	|
|	pascal									|	lexer.pascal.smart.highlighting					|	Set to 0 to not completely handle some complex features like 'property'.	|
|	perl									|	fold											|	Folding is turned on by setting fold=1.	|
|	perl									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	perl									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	perl									|	fold.perl.at.else								|	This option enables Perl folding on a "} else {" line of an if statement.	|
|	perl									|	fold.perl.comment.explicit						|	Set to 0 to disable explicit folding.	|
|	perl									|	fold.perl.package								|	Set to 0 to disable folding packages when using the Perl lexer.	|
|	perl									|	fold.perl.pod									|	Set to 0 to disable folding Pod blocks when using the Perl lexer.	|
|	props									|	lexer.props.allow.initial.spaces				|	For properties files, set to 0 to style all lines that start with whitespace in the default style. This is not suitable for SciTE .properties files which use indentation for flow control but can be used for RFC2822 text where indentation is used for continuation lines.	|
|	ps										|	ps.level										|	Define level (0..3) of PostScript handled and thus set of keywords. Default is 3.	|
|	python									|	fold											|	Folding is turned on by setting fold=1.	|
|	python									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	python									|	fold.quotes.python								|	This option enables folding multi-line quoted strings when using the Python lexer.	|
|	python									|	lexer.python.decorator.attributes				|	Set to 1 to recognise Python decorator attributes.	|
|	python									|	lexer.python.identifier.attributes				|	Set to 1 to recognise Python identifier attributes.	|
|	python									|	lexer.python.keywords2.no.sub.identifiers		|	When enabled, it will not style keywords2 items that are used as a sub-identifier. Example: when set, will not highlight "foo.open" when "open" is a keywords2 item.	|
|	python									|	lexer.python.literals.binary					|	Set to 0 to not recognise Python 3 binary and octal literals: 0b1011 0o712.	|
|	python									|	lexer.python.strings.b							|	Set to 0 to not recognise Python 3 bytes literals b"x".	|
|	python									|	lexer.python.strings.f							|	Set to 0 to not recognise Python 3.6 f-string literals f"var={var}".	|
|	python									|	lexer.python.strings.f.pep.701					|	Set to 0 to use pre-PEP 701 / Python 3.12 f-string lexing.	|
|	python									|	lexer.python.strings.over.newline				|	Set to 1 to allow strings to span newline characters.	|
|	python									|	lexer.python.strings.t							|	Set to 0 to not recognise Python 3.14 t-string literals t"var={var}".	|
|	python									|	lexer.python.strings.u							|	Set to 0 to not recognise Python Unicode literals u"x" as used before Python 3.	|
|	python									|	lexer.python.unicode.identifiers				|	Set to 0 to not recognise Python 3 Unicode identifiers.	|
|	python									|	tab.timmy.whinge.level							|	For Python code, checks whether indenting is consistent. The default, 0 turns off indentation checking, 1 checks whether each line is potentially inconsistent with the previous line, 2 checks whether any space characters occur before a tab character in the indentation, 3 checks whether any spaces are in the indentation, and 4 checks for any tab characters in the indentation. 1 is a good level to use.	|
|	r										|	lexer.r.escape.sequence							|	Set to 1 to enable highlighting of escape sequences in strings.	|
|	raku									|	fold											|	Folding is turned on by setting fold=1.	|
|	raku									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	raku									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	raku									|	fold.raku.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	raku									|	fold.raku.comment.pod							|	Set this property to 0 to disable folding POD comments when fold.comment=1.	|
|	registry								|	fold											|	Folding is turned on by setting fold=1.	|
|	registry								|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	ruby									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	ruby									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	rust									|	fold											|	Folding is turned on by setting fold=1.	|
|	rust									|	fold.at.else									|	This option enables C++ folding on a "} else {" line of an if statement.	|
|	rust									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	rust									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	rust									|	fold.rust.comment.explicit						|	Set this property to 0 to disable folding explicit fold points when fold.comment=1.	|
|	rust									|	fold.rust.comment.multiline						|	Set this property to 0 to disable folding multi-line comments when fold.comment=1.	|
|	rust									|	fold.rust.explicit.anywhere						|	Set this property to 1 to enable explicit fold points anywhere, not just in line comments.	|
|	rust									|	fold.rust.explicit.end							|	The string to use for explicit fold end points, replacing the standard //}.	|
|	rust									|	fold.rust.explicit.start						|	The string to use for explicit fold start points, replacing the standard //{.	|
|	rust									|	fold.rust.syntax.based							|	Set this property to 0 to disable syntax based folding.	|
|	rust									|	lexer.rust.fold.at.else							|	This option enables Rust folding on a "} else {" line of an if statement.	|
|	sql										|	fold											|	Folding is turned on by setting fold=1.	|
|	sql										|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	sql										|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	sql										|	fold.sql.at.else								|	This option enables SQL folding on a "ELSE" and "ELSIF" line of an IF statement.	|
|	sql										|	fold.sql.only.begin								|	Set to 1 to only fold on 'begin' but not other keywords.	|
|	sql										|	lexer.sql.allow.dotted.word						|	Set to 1 to colourise recognized words with dots (recommended for Oracle PL/SQL objects).	|
|	sql										|	lexer.sql.backticks.identifier					|	Recognise backtick quoting of identifiers.	|
|	sql										|	lexer.sql.numbersign.comment					|	If "lexer.sql.numbersign.comment" property is set to 0 a line beginning with '#' will not be a comment.	|
|	sql										|	sql.backslash.escapes							|	Enables backslash as an escape character in SQL.	|
|	vb, vbscript							|	fold											|	Folding is turned on by setting fold=1.	|
|	vb, vbscript							|	lexer.vb.strings.multiline						|	Set to 1 to allow strings to continue over line ends.	|
|	verilog									|	fold.at.else									|	This option enables C++ folding on a "} else {" line of an if statement.	|
|	verilog									|	fold.comment									|	This option enables folding multi-line comments and explicit fold points when using the C++ lexer. Explicit fold points allows adding extra folding by placing a //{ comment at the start and a //} at the end of a section that should fold.	|
|	verilog									|	fold.compact									|	Folding is turned on by setting fold=1.	|
|	verilog									|	fold.preprocessor								|	This option enables folding preprocessor directives when using the C++ lexer. Includes C#'s explicit #region and #endregion folding directives.	|
|	verilog									|	fold.verilog.flags								|	This option enables folding module definitions. Typically source files contain only one module definition so this option is somewhat useless.	|
|	verilog									|	lexer.verilog.allupperkeywords					|	Set to 1 to style identifiers that are all uppercase as documentation keyword.	|
|	verilog									|	lexer.verilog.fold.preprocessor.else			|	This option enables folding on `else and `elsif preprocessor directives.	|
|	verilog									|	lexer.verilog.portstyling						|	Set to 1 to style input, output, and inout ports differently from regular keywords.	|
|	verilog									|	lexer.verilog.track.preprocessor				|	Set to 1 to interpret `if/`else/`endif to grey out code that is not active.	|
|	verilog									|	lexer.verilog.update.preprocessor				|	Set to 1 to update preprocessor definitions when `define, `undef, or `undefineall found.	|
|	visualprolog							|	lexer.visualprolog.backquoted.strings			|	Set to 1 to enable using back quotes (``) to delimit strings.	|
|	visualprolog							|	lexer.visualprolog.verbatim.strings				|	Set to 0 to disable highlighting verbatim strings using '@'.	|
|	yaml									|	fold.comment.yaml								|	Set to 1 to allow folding of comment blocks in YAML.	|
|	zig										|	fold											|	Folding is turned on by setting fold=1.	|

