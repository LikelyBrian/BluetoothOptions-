#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"
#include <BluetoothLE.h>
#include <Regedit.h>
#include <Bluetooth.h>

using namespace std;
using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::BluetoothOptions_::implementation
{
    int32_t MainPage::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainPage::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainPage::ClickHandler(IInspectable const&, RoutedEventArgs const&)
    {
        std::wstring result = L"";
        try {
            std::wstring subKey = L"SYSTEM\\CurrentControlSet\\Services\\BTHPORT\\Parameters\\Devices\\a438cc1f6100";
            std::wstring valueName = L"Name";
            std::vector<BYTE> newValue = { 'N', 'i', 'n', 't', 'e', 'n', 'd', 'o', 'P', 'r', 'o', 0x0 }; // Replace with the desired new binary value

            SetRegistryValue(L"SYSTEM\\CurrentControlSet\\Services\\BTHPORT\\Parameters\\Devices\\a438cc1f6100", L"Nintendo Pro Controller", valueName);
            //CreateRegKey();

            //std::wcout << L"Registry value changed successfully." << std::endl;
            result += L"Registry value changed successfully.";
        }
        catch (const RegistryError& e) {
            //std::wcerr << L"Error: " << e.what() << L" (Code: " << e.ErrorCode() << L")" << std::endl;
            result += L"Error: ";
        }


        
        //result += GetPairedBluetoothLEDevices();

        //result += ChangeRegistryValue(id, valueName, newValue);
         
        output1().Text(result);

        //myButton().Content(box_value(result));
    }

    void MainPage::ClickHandler2(IInspectable const&, RoutedEventArgs const&)
    {
        std::wstring result = L"";
        //result += RegistryGrantAll();
        result += getAllPairedBluetoothDevices();
        //result += ListPairedBluetoothDevices();
        output1().Text(result);
        //myButton2().Content(box_value(result));
    }
}


void winrt::BluetoothOptions_::implementation::MainPage::TextBlock_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e)
{

}
