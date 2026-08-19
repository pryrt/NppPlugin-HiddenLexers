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

#### Example JSON files

The example `HiddenLexers.json` config files have been moved to a separate [ExampleJsonFiles.md](./ExampleJsonFiles.md) , to avoid overwhelming this README.

#### Known Properties

These are the lexer-specific properties that Lexilla supports -- at least, the ones that I could easily extract from the source code and Lexilla documentation... this list will likely
get out-of-date, and may not be complete, but it gives you a starting place... Always check the
current [lexilla/Lexers/*.cxx](https://github.com/notepad-plus-plus/notepad-plus-plus/tree/master/lexilla/lexers)
for the properties in your desired language.

They have been split off to [KnownProperties.md](./KnownProperties.md) to avoid overwhelming this README.
