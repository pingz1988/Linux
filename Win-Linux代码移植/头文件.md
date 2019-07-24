```c

#ifndef GARLIC_KBASE_WIN2LINUX_H
#define GARLIC_KBASE_WIN2LINUX_H

#define INVALID_HANDLE_VALUE   -1
#define MAX_PATH           260 /* max. length of full pathname */

//typedef void *HANDLE;
typedef unsigned int   HANDLE;
#define __stdcall
#define __declspec(x)
#define __cdecl
// #undef max
// #undef min
// #define max(a,b)            (((a) > (b)) ? (a) : (b))
// #define min(a,b)            (((a) < (b)) ? (a) : (b))

//-----------------------copy from windows BEGAIN--------------------------//
#define CREATE_NEW          1
#define CREATE_ALWAYS       2
#define OPEN_EXISTING       3
#define OPEN_ALWAYS         4
#define TRUNCATE_EXISTING   5

#define GENERIC_READ                     (0x80000000L)
#define GENERIC_WRITE                    (0x40000000L)
#define GENERIC_EXECUTE                  (0x20000000L)
#define GENERIC_ALL                      (0x10000000L)

#define PAGE_NOACCESS          0x01
#define PAGE_READONLY          0x02
#define PAGE_READWRITE         0x04
#define PAGE_WRITECOPY         0x08
#define PAGE_EXECUTE           0x10
#define PAGE_EXECUTE_READ      0x20
#define PAGE_EXECUTE_READWRITE 0x40
#define PAGE_EXECUTE_WRITECOPY 0x80
#define PAGE_GUARD            0x100
#define PAGE_NOCACHE          0x200
#define PAGE_WRITECOMBINE     0x400

#define SECTION_QUERY                0x0001
#define SECTION_MAP_WRITE            0x0002
#define SECTION_MAP_READ             0x0004
#define SECTION_MAP_EXECUTE          0x0008
#define SECTION_EXTEND_SIZE          0x0010
#define SECTION_MAP_EXECUTE_EXPLICIT 0x0020 // not included in SECTION_ALL_ACCESS

#define FILE_MAP_COPY       SECTION_QUERY
#define FILE_MAP_WRITE      SECTION_MAP_WRITE
#define FILE_MAP_READ       SECTION_MAP_READ
#define FILE_MAP_ALL_ACCESS SECTION_ALL_ACCESS
#define FILE_MAP_EXECUTE    SECTION_MAP_EXECUTE_EXPLICIT    // not included in FILE_MAP_ALL_ACCESS

//
//  Code Page Default Values.
//
#define CP_ACP                    0           // default to ANSI code page
#define CP_OEMCP                  1           // default to OEM  code page
#define CP_MACCP                  2           // default to MAC  code page
#define CP_THREAD_ACP             3           // current thread's ANSI code page
#define CP_SYMBOL                 42          // SYMBOL translations

#define CP_UTF7                   65000       // UTF-7 translation
#define CP_UTF8                   65001       // UTF-8 translation
//-----------------------copy from windows END--------------------------//


// types
#ifndef CONST
    #define CONST               const
#endif

#ifdef __cplusplus
	#define TRUE                true
	#define FALSE               false
#else
	#define TRUE                1
	#define FALSE               0
#endif	// __cplusplus

typedef signed char         INT8, *PINT8;
typedef signed short        INT16, *PINT16;
typedef signed int          INT32, *PINT32;
typedef long long           INT64, *PINT64;
typedef unsigned char       UINT8, *PUINT8;
typedef unsigned short      UINT16, *PUINT16;
typedef unsigned int        UINT32, *PUINT32;
typedef unsigned long long  UINT64, *PUINT64;

//
// The following types are guaranteed to be signed and 32 bits wide.
//

typedef signed int LONG32, *PLONG32;

//
// The following types are guaranteed to be unsigned and 32 bits wide.
//

typedef unsigned int ULONG32, *PULONG32;
typedef unsigned int DWORD32, *PDWORD32;

typedef UINT64 QWORD;
typedef size_t SIZET;

typedef double				DOUBLE;
typedef std::string         KSTRING;
typedef std::wstring        KWSTRING;
typedef char                KCHAR;
typedef char                KBYTE;
typedef wchar_t             KWCHAR;
typedef wchar_t				KCHARW;
typedef std::wstring		KSTRINGW;

typedef char                CHAR;
typedef short               SHORT;
typedef long                LONG;
#if !defined(MIDL_PASS)
typedef int                 INT;
#endif
typedef INT64               LONGLONG;
typedef UINT64              ULONGLONG;
#define MAXLONGLONG         (0x7fffffffffffffff)
#define ULLONG_MAX          (0xffffffffffffffff)
typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;
typedef float               FLOAT;
typedef FLOAT               *PFLOAT;
typedef BOOL                *PBOOL;
typedef BOOL                *LPBOOL;
typedef BYTE                *PBYTE;
typedef BYTE                *LPBYTE;
typedef int                 *PINT;
typedef int                 *LPINT;
typedef WORD                *PWORD;
typedef WORD                *LPWORD;
typedef long                *LPLONG;
typedef DWORD               *PDWORD;
typedef DWORD               *LPDWORD;
typedef void                *LPVOID;
typedef CONST void          *LPCVOID;
typedef char                CHAR;
typedef unsigned char       UCHAR;
typedef int                 INT;
typedef unsigned int        UINT;
typedef unsigned int        *PUINT;

typedef CONST CHAR *LPCSTR, *PCSTR;
typedef CHAR *NPSTR, *LPSTR, *PSTR;

typedef wchar_t WCHAR;    // wc,   16-bit UNICODE character
typedef CONST WCHAR *LPCWSTR, *PCWSTR;
typedef WCHAR *NWPSTR, *LPWSTR, *PWSTR;

#ifdef  _UNICODE
    typedef wchar_t             TCHAR;
    typedef wchar_t				CharBase;
    typedef LPCWSTR PCTSTR, LPCTSTR;
    typedef LPWSTR PTSTR, LPTSTR;
    #define _T(x)               L##x
    #define _TEXT(x)            L##x
    typedef std::wstring        TSTRING;
    typedef std::wfstream       TFSTREAM;
    typedef std::wstring		StringBase;
    typedef std::wostringstream OStringStream;
    typedef std::wistringstream IStringStream;
    typedef std::wofstream		OFileStream;
    typedef std::wifstream		IFileStream;

    // API
    #define _tcscmp                         wcscmp
    #define _tcscpy_s(dest,n,src)           wcsncpy(dest,src,n)
    #define _tcslen                         wcslen
#else
    typedef char                TCHAR;
    typedef char				CharBase;
    typedef LPSTR PTSTR, LPTSTR, PUTSTR, LPUTSTR;
    typedef LPCSTR PCTSTR, LPCTSTR, PCUTSTR, LPCUTSTR;
    #define _T(x)       		x
    #define _TEXT(x)    		x
    typedef std::string         TSTRING;
    typedef std::fstream        TFSTREAM;
    typedef std::string			StringBase;
    typedef std::stringstream	OStringStream;
    typedef std::istringstream  IStringStream;
    typedef std::ofstream		OFileStream;
    typedef std::ifstream		IFileStream;

    // API
    #define _tcscmp                         strcmp
    #define _tcscpy_s(dest,n,src)           strncpy(dest,src,n)
    #define _tcslen                         strlen
#endif	// _UNICODE

//Invalidate value for variables type
static const BYTE  BYTE_INVAL(0xFF);
static const WORD  WORD_INVAL(0XFFFF);
static const DWORD DWORD_INVAL(0XFFFFFFFF );
static const QWORD QWORD_INVAL(0XFFFFFFFFFFFFFFFF);

static const CHAR MAX_INT8(0X7F);
static const INT16 MAX_INT16(0X7FFF);
static const INT32 MAX_INT32(0X7FFFFFFF);
static const INT64 MAX_INT64(0X7FFFFFFFFFFFFFFF);

// Const
static const INT32 KSTRING_MAX = 128;
static const INT32 KSTRING_SIZE = KSTRING_MAX + 1;
static const INT32 KBUFF_MAX = 4096;	//old is 1024 [wp updated 2014-1-13]
static const INT32 KBUFF_SIZE = KBUFF_MAX + 1;
static const INT32 KFORMAT_MAX = 10240;
static const INT32 KFORMAT_SIZE = KFORMAT_MAX + 1;

// Text file header
static const UCHAR KTXT_TYPE_WTEXT[2] = {0xFF, 0xFE};
static const UCHAR KTXT_TYPE_WETEXT[2] = {0xFE, 0xFF};
static const UCHAR KTXT_TYPE_UTF8[3] = {0xEF, 0xBB, 0xBF};

// Common symbols
static const KCHAR COMMA_CHR(_T(','));
static const KCHAR COLON_CHR(_T(':'));
static const KCHAR SEMICOL_CHR(_T(';'));
static const KCHAR SPACE_CHR(_T(' '));
static const KCHAR UNDERLINE_CHR( _T('_'));
static const KCHAR SPOT_CHR( _T('.'));

static const StringBase COMMA_STR(_T(","));
static const StringBase COLON_STR(_T(":"));
static const StringBase SEMICOL_STR(_T(";"));
static const StringBase SPACE_STR(_T(" "));
static const StringBase EMPTY_STR(_T(""));
static const StringBase UNDERLINE_STR( _T("_"));
static const StringBase SPOT_STR( _T("."));


#endif // GARLIC_KBASE_WIN2LINUX_H

```
