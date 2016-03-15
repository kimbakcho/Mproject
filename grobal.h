#ifndef GROBAL
#define GROBAL



typedef BOOL	( *FP_CONNECT					) ( HWND, const char *, int, int, int, int );
typedef BOOL	( *FP_LOGIN					) ( HWND, const char *, const char *, const char *, int, BOOL );
FP_CONNECT					m_fpConnect;
FP_LOGIN					m_fpLogin;

#endif // GROBAL

