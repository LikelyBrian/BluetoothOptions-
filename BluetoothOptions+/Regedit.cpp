#include <windows.h>
#include <string>
#include <stdexcept>
#include <iostream>
#include "pch.h"
#include "Regedit.h"
#include <sddl.h>

RegistryError::RegistryError(const std::string& message, LONG errorCode)
    : std::runtime_error(message), m_errorCode(errorCode) {}

LONG RegistryError::ErrorCode() const {
    return m_errorCode;
}

void SetRegistryValue(std::wstring path, std::wstring newName, std::wstring valName) {
    LONG reg;
    HKEY hkey;

    LPCTSTR sk = (LPCTSTR)path.c_str();
    LONG openRes = RegOpenKeyExA(
        HKEY_LOCAL_MACHINE,
        ConvertWStringToLPCSTR(path),
        0,
        KEY_ALL_ACCESS,
        &hkey
    );

    //LONG openRes = RegOpenKeyEx(
    //    HKEY_LOCAL_MACHINE,
    //    TEXT("SYSTEM\\CurrentControlSet\\Services\\BTHPORT\\Parameters\\Devices\\a438cc1f6100"),
    //    0,
    //    KEY_READ | KEY_WRITE,
    //    &hkey
    //);

    //bool rgaIsTrue = RegistryGrantAll(hkey);
    
    LPCTSTR data = (LPCTSTR)newName.c_str();
    LPBYTE dataTEst = (LPBYTE)data;
    int dwData = 1234;
    if (openRes == ERROR_SUCCESS) {
        reg = RegSetValueExA(
            hkey,
            ConvertWStringToLPCSTR(valName),
            0,
            REG_BINARY,
            WStringToByte(newName),
            newName.length() + 1
        );
        if (reg != ERROR_SUCCESS) {
            RegCloseKey(hkey);
            throw RegistryError("Error1", reg);
        }
        else {
            RegCloseKey(hkey);

        }
    }
    else {
        RegCloseKey(hkey);
        throw RegistryError("Error", openRes);
    }

};

LPCSTR ConvertWStringToLPCSTR(const std::wstring& wstr) {
    int bufferSize = WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, NULL, 0, NULL, NULL);
    char* buffer = new char[bufferSize];
    WideCharToMultiByte(CP_ACP, 0, wstr.c_str(), -1, buffer, bufferSize, NULL, NULL);
    return buffer;
}

void CreateRegKey() {
    LONG lReg;
    HKEY hKey;
    DWORD dwData = 1234;
    std::wstring current_path = L"SYSTEM\\CurrentControlSet\\Services\\BTHPORT\\Parameters\\Devices\\a438cc1f6100\\test";
    LPCSTR lpcPath = ConvertWStringToLPCSTR(current_path);
    lReg = RegCreateKeyExA(
        HKEY_LOCAL_MACHINE,
        lpcPath,
        0,
        NULL,
        REG_OPTION_VOLATILE,
        KEY_ALL_ACCESS,
        NULL,
        &hKey,
        NULL
    );
    if (lReg != ERROR_SUCCESS) {
        throw RegistryError("Error CreateRegKey", lReg);
    }
};

bool RegistryGrantAll(HKEY hKey)
{
    bool bResult = false;

    PSECURITY_DESCRIPTOR sd = nullptr;

    const TCHAR* szSD =
        TEXT("D:")                  // Discretionary ACL
        TEXT("(D;OICI;KA;;;BG)")    // Deny access to built-in guests
        TEXT("(D;OICI;KA;;;AN)")    // Deny access to anonymous logon
        TEXT("(A;OICI;KRKW;;;AU)")  // Allow KEY_READ and KEY_WRITE to authenticated users ("AU")
        TEXT("(A;OICI;KA;;;BA)");   // Allow KEY_ALL_ACCESS to administrators ("BA" = Built-in Administrators)

    if (ConvertStringSecurityDescriptorToSecurityDescriptor((LPCTSTR)szSD, SDDL_REVISION_1, &sd, 0))
    {
        auto result = RegSetKeySecurity(hKey, DACL_SECURITY_INFORMATION, sd);
        if (ERROR_SUCCESS == result)
            bResult = true;
        else
            SetLastError(result);

        // Free the memory allocated for the SECURITY_DESCRIPTOR.
        LocalFree(sd);
    }

    return bResult;
}

BYTE* WStringToByte(const std::wstring& wstr) {
    // Calculate the size of the buffer needed for the multi-byte string
    int size = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    if (size == 0) {
        return nullptr;
    }

    // Allocate the buffer
    BYTE* buffer = new BYTE[size];

    // Convert the wide string to a multi-byte string
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, reinterpret_cast<LPSTR>(buffer), size, nullptr, nullptr);

    return buffer;
}