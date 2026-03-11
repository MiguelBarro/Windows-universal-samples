#pragma once
#include "ColorEntry.g.h"
#include "Functions.g.h"

#include "winrt/windows.ui.xaml.shapes.h"

namespace winrt
{
    hstring to_hstring(::winrt::Windows::UI::Color c);
}

namespace winrt::SDKTemplate::implementation
{
    struct ColorEntry : ColorEntryT<ColorEntry>
    {
        ColorEntry() = default;

        static winrt::Windows::UI::Xaml::Media::SolidColorBrush Brushify(winrt::Windows::UI::Color const& c);
        hstring ColorName();
        void ColorName(hstring const& value);
        winrt::Windows::UI::Color Color();
        void Color(winrt::Windows::UI::Color const& value);

    private:
        std::wstring _colorname;
        winrt::Windows::UI::Color _color;
    };

    struct Functions : FunctionsT<Functions>
    {
        Functions();

        static winrt::Windows::UI::Xaml::Media::SolidColorBrush TextColor(winrt::Windows::UI::Color const& c);
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::SDKTemplate::ColorEntry> ColorEntries();
        winrt::xBindSampleModel::DataModel Model();
        hstring GetTime();
        hstring Display(hstring const& stringArg, uint32_t intArg, double floatArg, bool boolArg);
        hstring countVowels(hstring const& words);
        winrt::Windows::UI::Xaml::Media::SolidColorBrush MakeColor(double red, double green, double blue);
        hstring ColorValue(double red, double green, double blue);
        winrt::Windows::UI::Xaml::Visibility ShowPlaceholder(uint32_t count);
        void ProcessColor(hstring const& value);
        void PopulateColorsClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ClearColorsClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void UpdateValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
        void ResetValuesClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);

    private:
        winrt::xBindSampleModel::DataModel _model;
        winrt::Windows::Foundation::Collections::IObservableVector<winrt::SDKTemplate::ColorEntry> _colorEntries;
        winrt::Windows::Globalization::DateTimeFormatting::DateTimeFormatter _longTimeFormatter{ L"longtime" };
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct ColorEntry : ColorEntryT<ColorEntry, implementation::ColorEntry> {};
    struct Functions : FunctionsT<Functions, implementation::Functions> {};
}
