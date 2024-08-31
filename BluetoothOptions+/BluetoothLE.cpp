#include "pch.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <windows.h>
#include <BluetoothLE.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Devices.Bluetooth.h>
#include <winrt/Windows.Devices.Enumeration.h>

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Devices::Bluetooth;
using namespace Windows::Devices::Enumeration;

std::wstring getLast17Chars(const winrt::hstring& input) {
    std::wstring wstr = input.c_str();
    if (wstr.length() > 17) {
        return wstr.substr(wstr.length() - 17);
    }
    else {
        return wstr;
    }
}

std::wstring GetPairedBluetoothLEDevices(DeviceInformationCollection devices) {
    std::vector<std::wstring> deviceNames;

    for (auto& device : devices) {
        std::wstring deviceName = device.Name().c_str();
        deviceName += L"\t ID: " + getLast17Chars(device.Id());
        deviceNames.push_back(deviceName); // Store the name in the vector
    }

    // Combine all names into a single wstring, separated by newlines
    std::wstringstream combinedNames;
    for (const auto& name : deviceNames) {
        combinedNames << name << L"\n";
    }
    return combinedNames.str();
}

std::wstring getAllPairedBluetoothDevices() {
    std::wstring deviceNames = L""; // Vector to store device names

    // Explicitly specify the return type of the asynchronous operation
    IAsyncOperation<DeviceInformationCollection> asyncOp = DeviceInformation::FindAllAsync(BluetoothDevice::GetDeviceSelector());
    // Wait for the async operation to complete and get the result
    DeviceInformationCollection devices = asyncOp.get();
    deviceNames += GetPairedBluetoothLEDevices(devices);

    IAsyncOperation<DeviceInformationCollection> asyncOpLE = DeviceInformation::FindAllAsync(BluetoothLEDevice::GetDeviceSelector());
    DeviceInformationCollection devicesLE = asyncOpLE.get();
    deviceNames += GetPairedBluetoothLEDevices(devicesLE);

    return deviceNames;
}

