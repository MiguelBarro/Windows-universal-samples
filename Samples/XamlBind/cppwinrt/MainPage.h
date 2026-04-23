#pragma once
#include "MainPage.g.h"

#include <winrt/Microsoft.UI.Xaml.Controls.h>

namespace winrt::SDKTemplate::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        using xaml_base = MainPageT<MainPage>;

        MainPage();

        static hstring FEATURE_NAME();
        static winrt::Windows::Foundation::Collections::IVector<winrt::SDKTemplate::Scenario> scenarios();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void ScenarioControl_SelectionChanged(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Footer_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void Button_Click(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        void NotifyUser(std::wstring_view strMessage, winrt::SDKTemplate::NotifyType type);
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
