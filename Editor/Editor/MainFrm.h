#pragma once

class CMainFrame : public CFrameWnd
{
protected:
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

public:

public:

public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

public:
	virtual ~CMainFrame();

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	CToolBar m_wndToolBar;
	CStatusBar m_wndStatusBar;

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

public:
	CSplitterWnd* GetEditorWndSplitter() { return &m_editorWndSplitter; }
	CSplitterWnd* GetSceneWndSplitter() { return &m_sceneWndSplitter; }
	CSplitterWnd* GetInspectorWndSplitter() { return &m_inspectorWndSplitter; }

private:
	CSplitterWnd m_editorWndSplitter;
	CSplitterWnd m_sceneWndSplitter;
	CSplitterWnd m_inspectorWndSplitter;
};


