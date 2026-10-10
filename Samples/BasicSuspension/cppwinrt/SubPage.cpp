#include "pch.h"
#include "SubPage.h"
#include "SubPage.g.cpp"

#include "Scenario_Suspension.h"

namespace winrt::SDKTemplate::implementation
{
    SubPage::SubPage()
    {
        InitializeComponent();

        _auto_revokeBR = Windows::UI::Core::SystemNavigationManager::GetForCurrentView()
            .BackRequested(auto_revoke_t{}, {get_weak(), &SubPage::Navigation_BackRequested});
    }

    void SubPage::OnNavigatedFrom(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        Windows::UI::Core::SystemNavigationManager::GetForCurrentView()
            .AppViewBackButtonVisibility(Windows::UI::Core::AppViewBackButtonVisibility::Collapsed);
    }

    void SubPage::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        Windows::UI::Core::SystemNavigationManager::GetForCurrentView()
            .AppViewBackButtonVisibility(Windows::UI::Core::AppViewBackButtonVisibility::Visible);

        // The paremeter is the item index. If we instead use the item itself the Get
        auto param = e.Parameter();
        if (param)
        {
            auto index = unbox_value<uint32_t>(param);
            // Retrieve the associated Scenario
            auto scenario = Scenario_Suspension::navigationInstance
                .get().as<SDKTemplate::Scenario_Suspension>();
            // Retrive members
            _item = scenario.Items().GetAt(index);
            TapCountRun().Text(std::to_wstring(_item.Taps()));
        }
    }

    void SubPage::Page_Tapped(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::Input::TappedRoutedEventArgs const&)
    {
        if(!_item)
            return;

        auto tapCount = _item.Taps();
        _item.Taps(++tapCount);
        TapCountRun().Text(std::to_wstring(tapCount));
    }

    void SubPage::Navigation_BackRequested(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Core::BackRequestedEventArgs const& e)
    {
        if (!e.Handled() & Frame().CanGoBack())
        {
            e.Handled(true);
            Frame().GoBack();
        }
    }
}
