#pragma once
#include "Scenario_Suspension.g.h"

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

     private:
        Windows::Foundation::Collections::IObservableVector<SDKTemplate::Item> _items
            {  winrt::single_threaded_observable_vector<SDKTemplate::Item>() };
    };
}

namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario_Suspension : Scenario_SuspensionT<Scenario_Suspension, implementation::Scenario_Suspension>
    {
    };
}
