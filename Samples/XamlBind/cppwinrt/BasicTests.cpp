#include "pch.h"
#include "BasicTests.h"
#include "BasicTests.g.cpp"

namespace winrt
{
    hstring to_hstring(xBindSampleModel::IEmployee e)
    {
        return e.Name();
    }
}

namespace winrt::SDKTemplate::implementation
{
    BasicTests::BasicTests()
    {
        InitializeValues();
    }

    void BasicTests::InitializeValues()
    {
        DPOnPage(L"DP on page");
    }

    winrt::xBindSampleModel::DataModel BasicTests::Model()
    {
        return _model;
    }

    winrt::Windows::UI::Xaml::DependencyProperty BasicTests::DPOnPageProperty()
    {
        static auto dp = winrt::Windows::UI::Xaml::DependencyProperty::Register(
            L"DPOnPage",
            winrt::xaml_typename<hstring>(),
            winrt::xaml_typename<winrt::SDKTemplate::BasicTests>(),
            winrt::Windows::UI::Xaml::PropertyMetadata{nullptr});
        return dp;
    }

    hstring BasicTests::DPOnPage()
    {
        return winrt::unbox_value<hstring>(GetValue(DPOnPageProperty()));
    }

    void BasicTests::DPOnPage(hstring const& value)
    {
        SetValue(DPOnPageProperty(), winrt::box_value(value));
    }

    void BasicTests::UpdateValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.UpdateValues();
        DPOnPage( DPOnPage() + L"-");
    }

    void BasicTests::ResetValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.InitializeValues();
        InitializeValues();
    }
}
