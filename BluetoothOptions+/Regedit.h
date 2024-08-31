#pragma once
#include <windows.h>
#include <string>
#include <stdexcept>

class RegistryError : public std::runtime_error {
public:
    RegistryError(const std::string& message, LONG errorCode);
    LONG ErrorCode() const;

private:
    LONG m_errorCode;
};

void SetRegistryValue(std::wstring path, std::wstring newName, std::wstring valName);

LPCSTR ConvertWStringToLPCSTR(const std::wstring& wstr);

void CreateRegKey();

bool RegistryGrantAll(HKEY hKey);

BYTE* WStringToByte(const std::wstring& wstr);