#pragma once
#include <string>
#include <windows.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Enumeration.h>

using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Devices::Enumeration;

std::wstring getLast17Chars(const winrt::hstring& input);
std::wstring GetPairedBluetoothLEDevices(IAsyncOperation<DeviceInformationCollection> asyncOp);
std::wstring getAllPairedBluetoothDevices();
