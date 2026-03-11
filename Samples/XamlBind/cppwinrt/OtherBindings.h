#pragma once
#include "OtherBindings.g.h"

namespace winrt
{
    hstring to_hstring(Windows::UI::Xaml::Visibility v);
}

namespace winrt::SDKTemplate::implementation
{
    struct OtherBindings : OtherBindingsT<OtherBindings>
    {
        OtherBindings() = default;

        winrt::xBindSampleModel::DataModel Model();
        int32_t MyInt();
        void MyInt(int32_t value);
        winrt::xBindSampleModel::IEmployee NullEmployee();
        void UpdateValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ResetValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void UndeferElementClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::xBindSampleModel::DataModel _model;
        int32_t _myint {0};
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct OtherBindings : OtherBindingsT<OtherBindings, implementation::OtherBindings>
    {
    };
}
