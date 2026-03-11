#include "pch.h"
#include "OtherBindings.h"
#include "OtherBindings.g.cpp"

#include "winrt/xBindSampleModel.h"

namespace winrt
{
    hstring to_hstring(Windows::UI::Xaml::Visibility v)
    {
        switch (v)
        {
            case Windows::UI::Xaml::Visibility::Visible:
                return L"Visible";
            case Windows::UI::Xaml::Visibility::Collapsed:
                return L"Collapsed";
            default:
                throw std::invalid_argument("Invalid value for the Windows::UI::Xaml::Visibility enum.");
        }
    }
}

namespace winrt::SDKTemplate::implementation
{
    winrt::xBindSampleModel::DataModel OtherBindings::Model()
    {
        return _model;
    }

    int32_t OtherBindings::MyInt()
    {
        return _myint;
    }

    void OtherBindings::MyInt(int32_t value)
    {
        _myint = value;
    }

    winrt::xBindSampleModel::IEmployee OtherBindings::NullEmployee()
    {
        return {};
    }

    void OtherBindings::UpdateValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.UpdateValues();
        _myint += 1;
    }

    void OtherBindings::ResetValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.InitializeValues();
        _myint = 0;
    }

    void OtherBindings::UndeferElementClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        FindName(L"deferedTextBlock");
    }
}
