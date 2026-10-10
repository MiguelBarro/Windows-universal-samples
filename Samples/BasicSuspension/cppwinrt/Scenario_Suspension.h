#pragma once
#include "Scenario_Suspension.g.h"

#include "SampleConfiguration.h"

#include <optional>

namespace winrt::SDKTemplate::implementation
{
    struct Scenario_Suspension : Scenario_SuspensionT<Scenario_Suspension>
    {
        Scenario_Suspension();

        void ListView_ItemClick(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e);
        void AddItem();
        void ResetItems();

        Windows::Foundation::Collections::IObservableVector<SDKTemplate::Item> Items();

        Windows::Data::Json::JsonObject SaveState() const;
        void RestoreState(Windows::Data::Json::JsonObject state);

        fire_and_forget OnSuspending(
                Windows::Foundation::IInspectable const& sender,
                Windows::ApplicationModel::SuspendingEventArgs const& args) const;

        void OnAcceleratorKeyActivated(
                Windows::UI::Core::CoreDispatcher const& sender,
                Windows::UI::Core::AcceleratorKeyEventArgs const& args) const;

        void OnMousePointerPressed(
                Windows::UI::Core::ICoreWindow const& sender,
                Windows::UI::Core::PointerEventArgs const& args) const;

     private:
        Windows::Foundation::Collections::IObservableVector<SDKTemplate::Item> _items
            {  winrt::single_threaded_observable_vector<SDKTemplate::Item>() };
        std::optional<uint32_t> _current;
        Windows::UI::Xaml::Application::Suspending_revoker _revoker;
        Windows::UI::Core::CoreAcceleratorKeys::AcceleratorKeyActivated_revoker _keyRevoker;
        Windows::UI::Core::CoreWindow::PointerPressed_revoker _mouseRevoker;

        static constexpr std::wstring_view itemsPropertyName { L"Items" };
        static constexpr std::wstring_view currentPropertyName { L"Current" };
        static constexpr std::wstring_view navigationPropertyName { L"Navigation" };

        static constexpr std::wstring_view sessionStateFilename { L"_sessionState.xml" };
        static bool lastSessionTerminated;
        static weak_ref<Scenario_Suspension> navigationInstance;

        friend void winrt::SDKTemplate::implementation::App_LaunchCompleted(
                Windows::ApplicationModel::Activation::LaunchActivatedEventArgs const& e);
        friend struct SubPage;
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario_Suspension : Scenario_SuspensionT<Scenario_Suspension, implementation::Scenario_Suspension>
    {
    };
}
