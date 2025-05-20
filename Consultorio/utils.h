#pragma once

// WinApi
#include <windows.h>

// <-- Required for std::ofstream and std::ifstream
#include <iostream>
#include <fstream>   

// Strings
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <algorithm> // for std::transform

// For time helper functions
#include <tuple>
#include <ctime>
#include <iomanip>
#include <sstream>

// For ListView
#include <commctrl.h>
#pragma comment(lib, "comctl32.lib")

// Data types
inline std::wstring StringToWString(const std::string& str) {
	int size_needed = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, NULL, 0);
	std::wstring wstrTo(size_needed, 0);
	MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, &wstrTo[0], size_needed);
	return wstrTo;
}

inline std::string wstringToString(const std::wstring& wstr) {
    if (wstr.empty()) return std::string();

    int sizeNeeded = WideCharToMultiByte(
        CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr
    );

    std::string str(sizeNeeded, 0);
    WideCharToMultiByte(
        CP_UTF8, 0, wstr.c_str(), -1, &str[0], sizeNeeded, nullptr, nullptr
    );

    // Remove the null terminator included by WideCharToMultiByte
    if (!str.empty() && str.back() == '\0') {
        str.pop_back();
    }

    return str;
}
        
inline int StringToInt(const std::string& str) {
    try {
        return std::stoi(str);
    }
    catch (...) {
        return 0;
    }
}

inline std::string ToUpper(const std::string& str) {
    std::string result = str;
    std::transform(result.begin(), result.end(), result.begin(), ::toupper);
    return result;
}

inline std::string wcharToChar(const wchar_t* wstr) {
    if (!wstr) return std::string();

    int sizeNeeded = WideCharToMultiByte(CP_UTF8, 0, wstr, -1, nullptr, 0, nullptr, nullptr);
    if (sizeNeeded <= 0) return std::string();

    std::string result(sizeNeeded, 0);
    WideCharToMultiByte(CP_UTF8, 0, wstr, -1, &result[0], sizeNeeded, nullptr, nullptr);

    // Remove null terminator if present
    if (!result.empty() && result.back() == '\0') result.pop_back();

    return result;
}

// DATES
inline std::tuple<int, int, int> dateStrToIntTuple(const std::string date) {
    int day = std::stoi(date.substr(0, 2));
    int month = std::stoi(date.substr(3, 2));
    int year = std::stoi(date.substr(6, 4));
    return { year, month, day };
}

inline std::string getWeekDay(const std::string & fecha) {
	int dia = std::stoi(fecha.substr(0, 2));
	int mes = std::stoi(fecha.substr(3, 2));
	int anio = std::stoi(fecha.substr(6, 4));

	std::tm time_in = {};
	time_in.tm_mday = dia;
	time_in.tm_mon = mes - 1;   // tm_mon: 0 = enero
	time_in.tm_year = anio - 1900; // tm_year: años desde 1900

	std::mktime(&time_in); // Normaliza la estructura y calcula tm_wday

	static const std::vector<std::string> dias = {
		"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"
	};

	return dias[time_in.tm_wday];
}

inline std::string getTodayDate() {
    std::time_t t = std::time(nullptr);
    std::tm local_tm;
    localtime_s(&local_tm, &t);  // thread-safe version

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << local_tm.tm_mday << "-"
        << std::setw(2) << (local_tm.tm_mon + 1) << "-"
        << (local_tm.tm_year + 1900);

    return oss.str();  // "DD-MM-YYYY"
}

inline bool dateValidation(const std::string date){
    std::string today_str = getTodayDate();
	std::tuple<int, int, int> today, d2;
	today = dateStrToIntTuple(today_str);
	d2 = dateStrToIntTuple(date);
    return today <= d2;
}

// Write and Read Strings
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

// Read, Check, Set Boxes
inline bool IsEmpty(const std::string& str) {
	return str.find_first_not_of(" \t\n\r") == std::string::npos;
}
