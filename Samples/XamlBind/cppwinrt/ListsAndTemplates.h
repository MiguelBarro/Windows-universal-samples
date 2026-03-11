#pragma once
#include "ListsAndTemplates.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct ListsAndTemplates : ListsAndTemplatesT<ListsAndTemplates>
    {
        ListsAndTemplates() = default;

        winrt::xBindSampleModel::DataModel Model();
        void UpdateValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ResetValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::xBindSampleModel::DataModel _model;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct ListsAndTemplates : ListsAndTemplatesT<ListsAndTemplates, implementation::ListsAndTemplates>
    {
    };
}
