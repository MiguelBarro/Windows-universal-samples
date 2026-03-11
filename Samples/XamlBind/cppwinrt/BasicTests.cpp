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
        _dpOnPage = L"DP on page";
    }

    winrt::xBindSampleModel::DataModel BasicTests::Model()
    {
        return _model;
    }

    hstring BasicTests::DPOnPage()
    {
        return hstring(_dpOnPage);
    }

    void BasicTests::DPOnPage(hstring const& value)
    {
        if (value != _dpOnPage)
            _dpOnPage = value;
    }

    void BasicTests::UpdateValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.UpdateValues();
        _dpOnPage += L"-";
    }

    void BasicTests::ResetValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.InitializeValues();
        InitializeValues();
    }
}
