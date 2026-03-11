#include "pch.h"
#include "ListsAndTemplates.h"
#include "ListsAndTemplates.g.cpp"

#include "winrt/xBindSampleModel.h"

namespace winrt::SDKTemplate::implementation
{
    winrt::xBindSampleModel::DataModel ListsAndTemplates::Model()
    {
        return _model;
    }
    void ListsAndTemplates::UpdateValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.UpdateValues();
    }
    void ListsAndTemplates::ResetValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.InitializeValues();
    }
}
