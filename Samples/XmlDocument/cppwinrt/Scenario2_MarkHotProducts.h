#pragma once
#include "Scenario2_MarkHotProducts.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario2_MarkHotProducts : Scenario2_MarkHotProductsT<Scenario2_MarkHotProducts>
    {
        Scenario2_MarkHotProducts();

        void OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

        void Scenario2BtnDefault_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

        winrt::fire_and_forget Scenario2BtnSave_Click(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::SDKTemplate::MainPage rootPage_ { nullptr };
        winrt::fire_and_forget Scenario2Init();
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario2_MarkHotProducts : Scenario2_MarkHotProductsT<Scenario2_MarkHotProducts, implementation::Scenario2_MarkHotProducts>
    {
    };
}
