#include "pch.h"
#include "Scenario_Suspension.h"
#include "Scenario_Suspension.g.cpp"

#include "Item.h"

namespace winrt::SDKTemplate::implementation
{
    Scenario_Suspension::Scenario_Suspension()
    {
        InitializeComponent();

        // Populate the ItemList with some default items.
        for (int i = 0; i < 5; ++i)
            AddItem();

        // Associate the ListView control with the ItemList instance.
        list().ItemsSource(_items);
    }

    Windows::Foundation::Collections::IObservableVector<SDKTemplate::Item> Scenario_Suspension::Items()
    {
        return _items;
    }

    void Scenario_Suspension::ListView_ItemClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs const& e)
    {
        Frame().Navigate(winrt::xaml_typename<SDKTemplate::SubPage>(), e.ClickedItem());
    }

    void Scenario_Suspension::AddItem()
    {
        _items.Append(winrt::make<Item>(L"Item " + std::to_wstring(_items.Size() + 1)));
    }

    void Scenario_Suspension::ResetItems()
    {
        _items.Clear();
        // Associate the ListView control with the new ItemList instance.
        list().ItemsSource(_items);
    }
}
