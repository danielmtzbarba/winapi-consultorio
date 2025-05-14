#pragma once

#include <windows.h>
#include <iostream>
#include <fstream>   // <-- Required for std::ofstream and std::ifstream
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>


inline void writeString(std::ofstream& out, const std::string& str) {
	size_t length = str.size();
	out.write(reinterpret_cast<const char*>(&length), sizeof(length));
	out.write(str.c_str(), length);
}

inline std::string readString(std::ifstream& in) {
	size_t length;
	in.read(reinterpret_cast<char*>(&length), sizeof(length));
	std::string str(length, '\0');
	in.read(&str[0], length);
	return str;
}

inline std::wstring StringToWString(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstrTo[0], size_needed);
	return wstrTo;
}

inline char* wcharToChar(const wchar_t* wstr) {
    // Calculate the size of the converted string (in bytes)
    int len = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, NULL, 0, NULL, NULL);
    if (len == 0) {
        return NULL;  // Conversion failed
    }

    // Allocate memory for the converted string
    char* str = (char*)malloc(len * sizeof(char));
    if (str == NULL) {
        return NULL;  // Memory allocation failed
    }

    // Perform the conversion
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, str, len, NULL, NULL);

    return str;
}

inline std::string ReadTextBox(HWND hwnd, int ID_TEXTBOX) {
        wchar_t buffer[256];
        HWND hwndEdit = GetDlgItem(hwnd, ID_TEXTBOX); 
        GetWindowTextW(hwndEdit, buffer, sizeof(buffer));
        std::string str = wcharToChar(buffer);
        return str;
}

inline void CenterWindow(HWND hwnd) {
    RECT rc;
    GetWindowRect(hwnd, &rc);

    int winWidth = rc.right - rc.left;
    int winHeight = rc.bottom - rc.top;

    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    int x = (screenWidth - winWidth) / 2;
    int y = (screenHeight - winHeight) / 2;

    MoveWindow(hwnd, x, y, winWidth, winHeight, TRUE);
}
