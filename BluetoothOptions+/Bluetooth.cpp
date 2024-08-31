#include <Bluetooth.h>
#include <vector>
#include <string>

#include "pch.h"
//#pragma comment(lib, "Bthprops.lib")

#include <windows.h>
#include <winrt/Windows.Devices.Enumeration.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <iostream>

std::wstring ListPairedBluetoothDevices() {
    std::wstring list = L"";
    winrt::init_apartment();

    auto deviceSelector = winrt::Windows::Devices::Bluetooth::BluetoothDevice::GetDeviceSelector();
    auto devices = winrt::Windows::Devices::Enumeration::DeviceInformation::FindAllAsync(deviceSelector).get();

    for (const auto& device : devices) {
        std::wstring deviceName = device.Name().c_str();
        std::wstring id = device.Id().c_str();
        list += L"Name: " + deviceName;
        list += L"\tId: " + id + L"\n";
    }
    return list;
}