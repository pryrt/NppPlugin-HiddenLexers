#pragma once
#include <string>
#include <Windows.h>

namespace pcjHelper
{
	// delete null characters from padded wstrings
	std::wstring delNull(std::wstring& str);
	std::string delNull(std::string& str);

	// convert wstring to UTF8-encoded bytes in std::string
	std::string wstring_to_utf8(std::wstring& wstr);

	// convert UTF8-encoded bytes in std::string to std::wstring
	std::wstring utf8_to_wstring(std::string& str);

	// recursively create all levels necessary for a given directory
	BOOL RecursiveCreateDirectory(std::wstring wsPath);

	// checks if a given directory is writeable
	bool is_dir_writable(const std::wstring& path);

	// writes the contents to the given path, creating any parent directories as needed
	//	return true on success, false on failure, with MessageBox to explain errors
	bool write_file_wrapper(std::wstring wsPath, std::string sContents);
};

