# !!IN DEVELOPMENT!!

Not useable yet.

# HiddenLexers

A Notepad++ Plugin that allows users to enable 'hidden' Lexilla lexers in Notepad++.

## Explanation

Notepad++ ships with 90+ language "lexers" (syntax highlighters) enabled from the Lexilla library.  But Lexilla actually includes many more that Notepad++ doesn't include.
Based on an old script for the PythonScript plugin, this new Plugin will allow users to configure one or more of those hidden lexers to be used for particular

## Installation

You can install the plugin using Notepad++'s **Plugins Admin**, or by unzipping the appropriate archive from the [latest release](https://github.com/pryrt/NppPlugin-HiddenLexers/releases/latest), so that `HiddenLexers.dll` ends up in the `c:\Program Files\Notepad++\plugins\HiddenLexers\` directory (or equivalent, for your installation's location).  (The files in the `docs\` folder from the zipfile could also be extracted into `c:\Program Files\Notepad++\plugins\HiddenLexers\docs\` directory, but that's not required).

## Config files

The configuration files for the plugin will be in `plugins\config\HiddenLexers\`

### `HiddenLexers.json`

TODO: JSON file to pick which lexers to associate with which extensions

### `HiddenLexersStyles.xml`

TODO: Not sure whether this will stay with the JSON, or be a separate stylers.xml-compatible file.  Depends on the structure I end up needing.

## Notes

For now, there's not much to note.

---------------------------------

## Development Notes

Adapt my PythonScript <C:\Users\pryrt\AppData\Roaming\Notepad++\plugins\Config\PythonScript\scripts\dev\HiddenLexers.py> into a plugin.
- [ ] JSON or INI config file to handle the map_extensions functionality (mapping extension to one of the named lexers)
- [ ] Some sort of table which lists the available
- [ ] JSON or INI or stylerThemes-like-XML for setting colors
- [ ] JSON or INI or langs-like-XML for setting keywords
- [ ] Notification Handling: psuedocode:
    ```pseudocode
    IF(NPPN_LANGCHANGED or NPPN_BUFFERACTIVATED):       # see NppPluginDemo.cpp:beNotified() switch
        # check_lexers
        read active lexer and file_extension
        if !activeLexer and file_extension in map_extensions and self.enabled:
            # init_lexer(file_extension)
            call colorize(file_extension)
                set style colors
                ilexer_ptr = SendMessage(nppHwnd, NPPM_CREATELEXER, 0, wcharptrLexername)
                SendMessage(editorHwnd, SCI_SETLEXER, 0, ilexer_ptr)
                setProperty as needed
                setKeywords for each list, as needed
            update internal lexer name variable (don't know if that's useful outside of PythonScript implementation)
    ```
