#pragma once

#ifdef WINRT_IMPORT_MODULE
#include "winrt/base_macros.h"
import winrt.Windows.UI.Xaml.Controls;
#else // WINRT_IMPORT_MODULE
#include "winrt/Windows.UI.Xaml.Controls.h"
#endif // WINRT_IMPORT_MODULE
namespace winrt::Windows::UI::Xaml::Controls::implementation
{
    struct WINRT_IMPL_EMPTY_BASES ItemClickEventArgs
        : implements<ItemClickEventArgs, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs, composing>,
        impl::require<ItemClickEventArgs, winrt::Windows::UI::Xaml::IRoutedEventArgs>,
        impl::base<ItemClickEventArgs, winrt::Windows::UI::Xaml::RoutedEventArgs>
    {
        using base_type = ItemClickEventArgs;
        using class_type = Windows::UI::Xaml::Controls::ItemClickEventArgs;
        using implements_type = implements<ItemClickEventArgs, winrt::Windows::UI::Xaml::Controls::ItemClickEventArgs, composing>;
        using implements_type::implements_type;
        using composable_base = winrt::Windows::UI::Xaml::RoutedEventArgs;
        hstring GetRuntimeClassName() const override
        {
            return L"Windows.UI.Xaml.Controls.ItemClickEventArgs";
        }

        ItemClickEventArgs(
                winrt::Windows::Foundation::IInspectable const& clickedItem,
                winrt::Windows::Foundation::IInspectable const& originalSource)
            : _clickedItem(clickedItem)
            , _originalSource(originalSource)
        {
        }

        winrt::Windows::Foundation::IInspectable ClickedItem()
        {
            return _clickedItem;
        }

        winrt::Windows::Foundation::IInspectable OriginalSource()
        {
            return _originalSource;
        }

    private:
        winrt::Windows::Foundation::IInspectable _clickedItem{ nullptr };
        winrt::Windows::Foundation::IInspectable _originalSource{ nullptr };
    };
}
