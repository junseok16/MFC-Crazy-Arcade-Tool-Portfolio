#include "pch.h"
#include "FileExplorer.h"
using namespace std;

CString CFileExplorer::ConvertToRelativePath(CString strAbsolutePath)
{
	TCHAR szRelativePath[MAX_PATH] = L"";// ��� ��� ���ڿ�
	TCHAR szCurDirPath[MAX_PATH] = L"";// ���� ��� ���ڿ�

	GetCurrentDirectory(MAX_PATH, szCurDirPath);	// ���� ������Ʈ�� �ִ� ���丮 ��θ� ����

	// PathRelativePathTo : szCurDirPath���� strFullPath�� ���� ����θ� ���ؼ� szRelativePath�� �����ϴ� �Լ�
	// ��, ���� ����̺� �������� ���� ����

	PathRelativePathTo(szRelativePath,
		szCurDirPath,
		FILE_ATTRIBUTE_DIRECTORY,
		strAbsolutePath.GetString(),
		FILE_ATTRIBUTE_DIRECTORY);

	return CString(szRelativePath);
}
