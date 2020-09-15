#include <Windows.h>

#include "Utils.h"

void DebugOut(wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugString(dbg_out);
}

vector<string> split(string line, string delimeter)
{
	vector<string> tokens;
	size_t last = 0; size_t next = 0;
	while ((next = line.find(delimeter, last)) != string::npos)
	{
		tokens.push_back(line.substr(last, next - last));
		last = next + 1;
	}
	tokens.push_back(line.substr(last));

	return tokens;
}

/*
char * string to wchar_t* string.
*/
wstring ToWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring wstr(wcstring);

	// delete wcstring   // << can I ? 
	return wstr;
}

/*
	Convert char* string to wchar_t* string.
*/
LPCWSTR ToLPCWSTR(string st)
{
	const char* str = st.c_str();

	size_t newsize = strlen(str) + 1;
	wchar_t* wcstring = new wchar_t[newsize];
	size_t convertedChars = 0;
	mbstowcs_s(&convertedChars, wcstring, newsize, str, _TRUNCATE);

	wstring* w = new wstring(wcstring);

	// delete wcstring   // << can I ? 
	return w->c_str();
}

//void MultipleMatrix(D3DXVECTOR3 &p)
//{
//	int sum;
//	//khoi tao ma tran trung gian transform p
//	D3DXMATRIX ret;
//	D3DXMatrixIdentity(&ret);
//	ret(0, 0) = -1;	//flip x
//	ret(3, 0) = p.x * 2; //dich x 1 doan 2x
//	
//	//phep nhan ma tran
//	for (int i = 0; i <= 2; i++) {
//		for (int j = 0; j <= 2; j++) {
//			sum = 0;
//			for (int k = 0; k <= 2; k++) {
//				sum = sum + a[i][k] * b[k][j];
//			}
//			c[i][j] = sum;
//		}
//	}
//}