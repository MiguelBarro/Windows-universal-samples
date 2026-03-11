#include "pch.h"
#include "EventTests.h"
#include "EventTests.g.cpp"

#include "winrt/Windows.UI.Popups.h"

using namespace winrt::Windows::UI::Popups;

namespace winrt::SDKTemplate::implementation
{
    winrt::xBindSampleModel::DataModel EventTests::Model()
    {
        return _model;
    }

    void EventTests::Click_RegularArgs(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        MessageDialog dlg{ L"Clicked - Regular Args" };
        dlg.ShowAsync();
    }

    void EventTests::Click_NoArgs()
    {
        MessageDialog dlg{ L"Clicked - No Args" };
        dlg.ShowAsync();
    }

    void EventTests::Click_BaseArgs(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::Foundation::IInspectable const&)
    {
        MessageDialog dlg{ L"Clicked - Base Args" };
        dlg.ShowAsync();
    }
}
