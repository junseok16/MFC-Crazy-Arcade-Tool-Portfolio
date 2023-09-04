#pragma once

/***************
	심볼릭 상수
***************/
const int32 IWINCX = 800;
const int32 IWINCY = 600;

const float FWINCX = 800.0f;
const float FWINCY = 600.0f;

const int32 ITILECX = 130;
const int32 ITILECY = 68;

const float FTILECX = 130.0f;
const float FTILECY = 68.0f;

const int32 ITILEX = 20;
const int32 ITILEY = 30;


#define		OBJ_NOEVENT		0
#define		OBJ_DEAD		1

#define		VK_MAX			0xff

#define		MIN_STR			64
#define		MAX_STR			256

#define		RUBY			0x01		// -> 0001
#define		DIAMOND			0x02		// -> 0010
#define		SAPPHIRE		0x04		// -> 0100

/***************
	전처리기
***************/
// VERIFY NULLPTR
#define VERIFY_NULLPTR(_ptr) if (_ptr == nullptr) { return; }

// ERROR MESSAGE
#define ERR_MSG(message) ::MessageBox(nullptr, message, L"error", MB_OK)

// DELETE COPY CTOR, OPERATOR
#define DELETE_COPY(ClassName);						\
ClassName(const ClassName&) = delete;				\
ClassName(ClassName&&) = delete;					\
ClassName& operator=(const ClassName&) = delete;	\
ClassName& operator=(ClassName&&) = delete;			\

// DECLARE SINGLETON
#define DECLARE_SINGLETON(ClassName)				\
	DELETE_COPY(ClassName)							\
													\
public:												\
	static ClassName* GetInstance();				\
	static void		  DestroyInstance();			\
													\
private:											\
	static ClassName* m_pInstance;

// IMPLEMENT SINGLETON
#define IMPLEMENT_SINGLETON(ClassName)				\
ClassName* ClassName::m_pInstance = nullptr;		\
													\
ClassName* ClassName::GetInstance()					\
{													\
	if (m_pInstance == nullptr)						\
	{												\
		m_pInstance = new ClassName;				\
	}												\
	return m_pInstance;								\
}													\
													\
void ClassName::DestroyInstance()					\
{													\
	if(m_pInstance != nullptr)						\
	{												\
		delete m_pInstance;							\
		m_pInstance = nullptr;						\
	}												\
}

extern HWND		g_hWnd;
