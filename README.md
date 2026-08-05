# !!IN DEVELOPMENT!!

Basic functionality appears to be there, not fully vetted/debugged yet.

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

JSON file to pick which lexers to associate with which extensions, and to associate style and keywords with each lexer.
(TODO: Long-term goal is to also allow setting Lexilla options, but that's not implemented yet.)

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
        - `"keywords": [...]` lists the keywords: the array must contain exactly 9 strings, which are space-separated lists of keywords (similar to what goes in langs.xml)
            - it is up to the user to explore [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers) file(s) to determine what keyword list(s) are needed (and eventually, what options are supported) for your enabled hidden lexers.
        - `"options": {}` is currently empty; TODO: allow option/value pairs inside
            - it is up to the user to explore [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers) file(s) to determine what what options are supported for your enabled hidden lexers.

```
{
  "extensions": {
    "stata": "stata",
    "do": "stata",
    "adoc": "asciidoc"
  },
  "lexers": {
    "asciidoc": {
      "0  SCE_ASCIIDOC_DEFAULT":        { "fgColor": "", "bgColor": "", "fontStyle": "0" },
      "1  SCE_ASCIIDOC_STRONG1":        { "fgColor": "", "bgColor": "", "fontStyle": "1" },
      "2  SCE_ASCIIDOC_STRONG2":        { "fgColor": "", "bgColor": "", "fontStyle": "5" },
      "3  SCE_ASCIIDOC_EM1":            { "fgColor": "", "bgColor": "", "fontStyle": "2" },
      "4  SCE_ASCIIDOC_EM2":            { "fgColor": "", "bgColor": "", "fontStyle": "6" },
      "5  SCE_ASCIIDOC_HEADER1":        { "fgColor": "CC0000", "bgColor": "", "fontStyle": "1" },
      "6  SCE_ASCIIDOC_HEADER2":        { "fgColor": "CC3333", "bgColor": "4F4F4F", "fontStyle": "1" },
      "7  SCE_ASCIIDOC_HEADER3":        { "fgColor": "CC7777", "bgColor": "5F5F5F", "fontStyle": "1" },
      "8  SCE_ASCIIDOC_HEADER4":        { "fgColor": "CCbbbb", "bgColor": "6F6F6F", "fontStyle": "1" },
      "9  SCE_ASCIIDOC_HEADER5":        { "fgColor": "CCffff", "bgColor": "7F7F7F", "fontStyle": "1" },
      "10 SCE_ASCIIDOC_HEADER6":        { "fgColor": "FFFFFF", "bgColor": "8F8F8F", "fontStyle": "1" },
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
      "0" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "0" },
      "1" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "1" },
      "2" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "2" },
      "3" : { "fgColor": "7F9F7F", "bgColor": "3F3F3F", "fontStyle": "3" },
      "4" : { "fgColor": "8CD0D3", "bgColor": "3F3F3F", "fontStyle": "4" },
      "5" : { "fgColor": "9F9D6D", "bgColor": "3F3F3F", "fontStyle": "5" },
      "6" : { "fgColor": "DCDCCC", "bgColor": "3F3F3F", "fontStyle": "6" },
      "7" : { "fgColor": "CC9393", "bgColor": "", "fontStyle": "7" },
      "8" : { "fgColor": "93E0E3", "bgColor": "3F3F3F", "fontStyle": "0" },
      "9" : { "fgColor": "DFC47D", "bgColor": "3F3F3F", "fontStyle": "0" },
      "10" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
      "11" : { "fgColor": "CEDF99", "bgColor": "3F3F3F", "fontStyle": "0" },
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

## Notes

For now, there's not much to note.
