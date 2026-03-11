#pragma once
#include "BasicTests.g.h"
#include "winrt/xBindSampleModel.h"

namespace winrt
{
    hstring to_hstring(xBindSampleModel::IEmployee e);
}

namespace winrt::SDKTemplate::implementation
{
    struct BasicTests : BasicTestsT<BasicTests>
    {
        BasicTests();

        winrt::xBindSampleModel::DataModel Model();
        hstring DPOnPage();
        void DPOnPage(hstring const& value);
        void UpdateValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ResetValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::xBindSampleModel::DataModel _model;
        std::wstring _dpOnPage;

        void InitializeValues();
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct BasicTests : BasicTestsT<BasicTests, implementation::BasicTests>
    {
    };
}
