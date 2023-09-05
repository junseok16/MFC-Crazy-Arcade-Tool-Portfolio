#pragma once

class CFileExplorer final
{
public:
	CFileExplorer() = default;
	~CFileExplorer() = default;

public:
	static CString ConvertToRelativePath(CString strAbsolutePath);
};

