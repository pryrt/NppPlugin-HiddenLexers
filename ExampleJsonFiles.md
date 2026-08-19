# Example JSON Files

Here are some example `HiddenLexers.json` config files, to show how the JSON fields should be used (and to use as the basis for your own config files).

## Example: Default (stylers.xml)-compatible Colors
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

## Example: DarkModeDefault-compatible Colors
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
