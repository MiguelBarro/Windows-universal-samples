#include "pch.h"
#include "Functions.h"
#include "ColorEntry.g.cpp"
#include "Functions.g.cpp"

#include "winrt/windows.ui.h"
#include "winrt/xBindSampleModel.h"

namespace winrt
{
    hstring to_hstring(::winrt::Windows::UI::Color c)
    {
        return Windows::UI::ColorHelper::ToDisplayName(c);
    }
}

namespace winrt::SDKTemplate::implementation
{
    winrt::Windows::UI::Xaml::Media::SolidColorBrush ColorEntry::Brushify(winrt::Windows::UI::Color const& c)
    {
        return winrt::Windows::UI::Xaml::Media::SolidColorBrush(c);
    }

    hstring ColorEntry::ColorName()
    {
        return hstring(_colorname);
    }

    void ColorEntry::ColorName(hstring const& value)
    {
        _colorname = value;
    }

    winrt::Windows::UI::Color ColorEntry::Color()
    {
        return _color;
    }

    void ColorEntry::Color(winrt::Windows::UI::Color const& value)
    {
        _color = value;
    }

    Functions::Functions()
    {
        _colorEntries = winrt::multi_threaded_observable_vector<winrt::SDKTemplate::ColorEntry>();
    }

    winrt::Windows::Foundation::Collections::IObservableVector<winrt::SDKTemplate::ColorEntry> Functions::ColorEntries()
    {
        return _colorEntries;
    }

    winrt::xBindSampleModel::DataModel Functions::Model()
    {
        return _model;
    }

    winrt::Windows::UI::Xaml::Media::SolidColorBrush Functions::TextColor(winrt::Windows::UI::Color const& c)
    {
        return winrt::Windows::UI::Xaml::Media::SolidColorBrush(
                ((c.R * 0.299 + c.G * 0.587 + c.B * 0.114) > 150)
                    ? winrt::Windows::UI::Colors::Black()
                    : winrt::Windows::UI::Colors::White());
    }

    hstring Functions::GetTime()
    {
        winrt::Windows::Globalization::Calendar calendar;
        return _longTimeFormatter.Format(calendar.GetDateTime());
    }

    hstring Functions::Display(hstring const& stringArg, uint32_t intArg, double floatArg, bool boolArg)
    {
        WCHAR longString[1024];
        HRESULT hr = S_OK;
        hr = StringCchPrintf(longString, _countof(longString),
                L"String is: %s, Integer is: %d, Float is: %f, Boolean is %s",
                stringArg.data(), intArg, floatArg, (boolArg ? L"true" : L"false"));
        check_hresult(hr);

        return {longString};
    }

    hstring Functions::countVowels(hstring const& words)
    {
        int count = 0;
        PCWSTR wordsData = words.data();
        for (UINT i = 0; i < words.size(); i++ )
        {
            WCHAR ch = wordsData[i];
            if (ch == 'a' || ch == 'A' ||
                    ch == 'e' || ch == 'E' ||
                    ch == 'i' || ch == 'I' ||
                    ch == 'o' || ch == 'O' ||
                    ch == 'u' || ch == 'U')
            {
                count++;
            }
        }

        return winrt::to_hstring(count);
    }

    winrt::Windows::UI::Xaml::Media::SolidColorBrush Functions::MakeColor(double red, double green, double blue)
    {
        return winrt::Windows::UI::Xaml::Media::SolidColorBrush(
                Windows::UI::ColorHelper::FromArgb(255, (byte)red, (byte)green, (byte)blue));
    }

    hstring Functions::ColorValue(double red, double green, double blue)
    {
        WCHAR longString[1024];
        HRESULT hr = S_OK;
        hr = StringCchPrintf(longString, _countof(longString), L"#%02X%02X%02X",(int)red, (int)green, (int)blue);
        check_hresult(hr);
        return {longString};
    }

    winrt::Windows::UI::Xaml::Visibility Functions::ShowPlaceholder(uint32_t count)
    {
        return count > 0 ? Windows::UI::Xaml::Visibility::Collapsed : Windows::UI::Xaml::Visibility::Visible;
    }

    int GetHexDigit(const WCHAR hexDigit)
    {
        if( hexDigit >= 'a' && hexDigit <= 'f')
        {
            return 10 + hexDigit - 'a';
        }
        if (hexDigit >= 'A' && hexDigit <= 'F')
        {
            return 10 + hexDigit - 'A';
        }
        if (isdigit(hexDigit))
        {
            return hexDigit - '0';
        }

        throw std::invalid_argument("Invalid hex digit");
    }

    int ParseColorDoubleByte(PCWSTR colorString, int start)
    {
        int firstDigit = GetHexDigit(colorString[start]);
        int secondDigit = GetHexDigit(colorString[start +1]);

        return firstDigit * 16 + secondDigit;
    }

    void Functions::ProcessColor(hstring const& value)
    {
        PCWSTR colorString = value.data();
        if (value.size() == 7 && colorString[0] == '#')
        {
            int red = ParseColorDoubleByte(colorString, 1);
            int green = ParseColorDoubleByte(colorString, 3);
            int blue = ParseColorDoubleByte(colorString, 5);

            RedSlider().Value(red);
            GreenSlider().Value(green);
            BlueSlider().Value(blue);
        }
        else
        {
            throw std::invalid_argument("Color value must be in the format #RRGGBB");
        }
    }

    const wchar_t* _colorNames[] =
    {
        L"AliceBlue", L"AntiqueWhite", L"Aqua", L"Aquamarine", L"Azure", L"Beige", L"Bisque", L"Black", L"BlanchedAlmond", L"Blue", L"BlueViolet", L"Brown", L"BurlyWood", L"CadetBlue", L"Chartreuse", L"Chocolate", L"Coral", L"CornflowerBlue", L"Cornsilk", L"Crimson", L"Cyan", L"DarkBlue", L"DarkCyan", L"DarkGoldenrod",
        L"DarkGray", L"DarkGreen", L"DarkKhaki", L"DarkMagenta", L"DarkOliveGreen", L"DarkOrange", L"DarkOrchid", L"DarkRed", L"DarkSalmon", L"DarkSeaGreen", L"DarkSlateBlue", L"DarkSlateGray", L"DarkTurquoise", L"DarkViolet", L"DeepPink", L"DeepSkyBlue", L"DimGray", L"DodgerBlue", L"Firebrick", L"FloralWhite",
        L"ForestGreen", L"Fuchsia", L"Gainsboro", L"GhostWhite", L"Gold", L"Goldenrod", L"Gray", L"Green", L"GreenYellow", L"Honeydew", L"HotPink", L"IndianRed", L"Indigo", L"Ivory", L"Khaki", L"Lavender", L"LavenderBlush", L"LawnGreen", L"LemonChiffon", L"LightBlue", L"LightCoral", L"LightCyan", L"LightGoldenrodYellow",
        L"LightGray", L"LightGreen", L"LightPink", L"LightSalmon", L"LightSeaGreen", L"LightSkyBlue", L"LightSlateGray", L"LightSteelBlue", L"LightYellow", L"Lime", L"LimeGreen", L"Linen", L"Magenta", L"Maroon", L"MediumAquamarine", L"MediumBlue", L"MediumOrchid", L"MediumPurple", L"MediumSeaGreen", L"MediumSlateBlue",
        L"MediumSpringGreen", L"MediumTurquoise", L"MediumVioletRed", L"MidnightBlue", L"MintCream", L"MistyRose", L"Moccasin", L"NavajoWhite", L"Navy", L"OldLace", L"Olive", L"OliveDrab", L"Orange", L"OrangeRed", L"Orchid", L"PaleGoldenrod", L"PaleGreen", L"PaleTurquoise", L"PaleVioletRed", L"PapayaWhip", L"PeachPuff",
        L"Peru", L"Pink", L"Plum", L"PowderBlue", L"Purple", L"Red", L"RosyBrown", L"RoyalBlue", L"SaddleBrown", L"Salmon", L"SandyBrown", L"SeaGreen", L"SeaShell", L"Sienna", L"Silver", L"SkyBlue", L"SlateBlue", L"SlateGray", L"Snow", L"SpringGreen", L"SteelBlue", L"Tan", L"Teal", L"Thistle", L"Tomato", L"Transparent",
        L"Turquoise", L"Violet", L"Wheat", L"White", L"WhiteSmoke", L"Yellow", L"YellowGreen"
    };

    winrt::Windows::UI::Color _colors[] =
    {
        winrt::Windows::UI::Colors::AliceBlue(), winrt::Windows::UI::Colors::AntiqueWhite(), winrt::Windows::UI::Colors::Aqua(), winrt::Windows::UI::Colors::Aquamarine(), winrt::Windows::UI::Colors::Azure(), winrt::Windows::UI::Colors::Beige(), winrt::Windows::UI::Colors::Bisque(), winrt::Windows::UI::Colors::Black(), winrt::Windows::UI::Colors::BlanchedAlmond(),
        winrt::Windows::UI::Colors::Blue(), winrt::Windows::UI::Colors::BlueViolet(), winrt::Windows::UI::Colors::Brown(), winrt::Windows::UI::Colors::BurlyWood(), winrt::Windows::UI::Colors::CadetBlue(), winrt::Windows::UI::Colors::Chartreuse(), winrt::Windows::UI::Colors::Chocolate(), winrt::Windows::UI::Colors::Coral(), winrt::Windows::UI::Colors::CornflowerBlue(),
        winrt::Windows::UI::Colors::Cornsilk(), winrt::Windows::UI::Colors::Crimson(), winrt::Windows::UI::Colors::Cyan(), winrt::Windows::UI::Colors::DarkBlue(), winrt::Windows::UI::Colors::DarkCyan(), winrt::Windows::UI::Colors::DarkGoldenrod(), winrt::Windows::UI::Colors::DarkGray(), winrt::Windows::UI::Colors::DarkGreen(), winrt::Windows::UI::Colors::DarkKhaki(),
        winrt::Windows::UI::Colors::DarkMagenta(), winrt::Windows::UI::Colors::DarkOliveGreen(), winrt::Windows::UI::Colors::DarkOrange(), winrt::Windows::UI::Colors::DarkOrchid(), winrt::Windows::UI::Colors::DarkRed(), winrt::Windows::UI::Colors::DarkSalmon(), winrt::Windows::UI::Colors::DarkSeaGreen(), winrt::Windows::UI::Colors::DarkSlateBlue(),
        winrt::Windows::UI::Colors::DarkSlateGray(), winrt::Windows::UI::Colors::DarkTurquoise(), winrt::Windows::UI::Colors::DarkViolet(), winrt::Windows::UI::Colors::DeepPink(), winrt::Windows::UI::Colors::DeepSkyBlue(), winrt::Windows::UI::Colors::DimGray(), winrt::Windows::UI::Colors::DodgerBlue(), winrt::Windows::UI::Colors::Firebrick(),
        winrt::Windows::UI::Colors::FloralWhite(), winrt::Windows::UI::Colors::ForestGreen(), winrt::Windows::UI::Colors::Fuchsia(), winrt::Windows::UI::Colors::Gainsboro(), winrt::Windows::UI::Colors::GhostWhite(), winrt::Windows::UI::Colors::Gold(), winrt::Windows::UI::Colors::Goldenrod(), winrt::Windows::UI::Colors::Gray(), winrt::Windows::UI::Colors::Green(),
        winrt::Windows::UI::Colors::GreenYellow(), winrt::Windows::UI::Colors::Honeydew(), winrt::Windows::UI::Colors::HotPink(), winrt::Windows::UI::Colors::IndianRed(), winrt::Windows::UI::Colors::Indigo(), winrt::Windows::UI::Colors::Ivory(), winrt::Windows::UI::Colors::Khaki(), winrt::Windows::UI::Colors::Lavender(), winrt::Windows::UI::Colors::LavenderBlush(),
        winrt::Windows::UI::Colors::LawnGreen(), winrt::Windows::UI::Colors::LemonChiffon(), winrt::Windows::UI::Colors::LightBlue(), winrt::Windows::UI::Colors::LightCoral(), winrt::Windows::UI::Colors::LightCyan(), winrt::Windows::UI::Colors::LightGoldenrodYellow(), winrt::Windows::UI::Colors::LightGray(), winrt::Windows::UI::Colors::LightGreen(),
        winrt::Windows::UI::Colors::LightPink(), winrt::Windows::UI::Colors::LightSalmon(), winrt::Windows::UI::Colors::LightSeaGreen(), winrt::Windows::UI::Colors::LightSkyBlue(), winrt::Windows::UI::Colors::LightSlateGray(), winrt::Windows::UI::Colors::LightSteelBlue(), winrt::Windows::UI::Colors::LightYellow(), winrt::Windows::UI::Colors::Lime(),
        winrt::Windows::UI::Colors::LimeGreen(), winrt::Windows::UI::Colors::Linen(), winrt::Windows::UI::Colors::Magenta(), winrt::Windows::UI::Colors::Maroon(), winrt::Windows::UI::Colors::MediumAquamarine(), winrt::Windows::UI::Colors::MediumBlue(), winrt::Windows::UI::Colors::MediumOrchid(), winrt::Windows::UI::Colors::MediumPurple(),
        winrt::Windows::UI::Colors::MediumSeaGreen(), winrt::Windows::UI::Colors::MediumSlateBlue(), winrt::Windows::UI::Colors::MediumSpringGreen(), winrt::Windows::UI::Colors::MediumTurquoise(), winrt::Windows::UI::Colors::MediumVioletRed(), winrt::Windows::UI::Colors::MidnightBlue(), winrt::Windows::UI::Colors::MintCream(), winrt::Windows::UI::Colors::MistyRose(),
        winrt::Windows::UI::Colors::Moccasin(), winrt::Windows::UI::Colors::NavajoWhite(), winrt::Windows::UI::Colors::Navy(), winrt::Windows::UI::Colors::OldLace(), winrt::Windows::UI::Colors::Olive(), winrt::Windows::UI::Colors::OliveDrab(), winrt::Windows::UI::Colors::Orange(), winrt::Windows::UI::Colors::OrangeRed(), winrt::Windows::UI::Colors::Orchid(),
        winrt::Windows::UI::Colors::PaleGoldenrod(), winrt::Windows::UI::Colors::PaleGreen(), winrt::Windows::UI::Colors::PaleTurquoise(), winrt::Windows::UI::Colors::PaleVioletRed(), winrt::Windows::UI::Colors::PapayaWhip(), winrt::Windows::UI::Colors::PeachPuff(), winrt::Windows::UI::Colors::Peru(), winrt::Windows::UI::Colors::Pink(), winrt::Windows::UI::Colors::Plum(),
        winrt::Windows::UI::Colors::PowderBlue(), winrt::Windows::UI::Colors::Purple(), winrt::Windows::UI::Colors::Red(), winrt::Windows::UI::Colors::RosyBrown(), winrt::Windows::UI::Colors::RoyalBlue(), winrt::Windows::UI::Colors::SaddleBrown(), winrt::Windows::UI::Colors::Salmon(), winrt::Windows::UI::Colors::SandyBrown(), winrt::Windows::UI::Colors::SeaGreen(),
        winrt::Windows::UI::Colors::SeaShell(), winrt::Windows::UI::Colors::Sienna(), winrt::Windows::UI::Colors::Silver(), winrt::Windows::UI::Colors::SkyBlue(), winrt::Windows::UI::Colors::SlateBlue(), winrt::Windows::UI::Colors::SlateGray(), winrt::Windows::UI::Colors::Snow(), winrt::Windows::UI::Colors::SpringGreen(), winrt::Windows::UI::Colors::SteelBlue(),
        winrt::Windows::UI::Colors::Tan(), winrt::Windows::UI::Colors::Teal(), winrt::Windows::UI::Colors::Thistle(), winrt::Windows::UI::Colors::Tomato(), winrt::Windows::UI::Colors::Transparent(), winrt::Windows::UI::Colors::Turquoise(), winrt::Windows::UI::Colors::Violet(), winrt::Windows::UI::Colors::Wheat(), winrt::Windows::UI::Colors::White(),
        winrt::Windows::UI::Colors::WhiteSmoke(), winrt::Windows::UI::Colors::Yellow(), winrt::Windows::UI::Colors::YellowGreen()
    };

    void Functions::PopulateColorsClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _ASSERT(_countof(_colors) == _countof(_colorNames));
        for (int i = 0; i < _countof(_colors); i++)
        {
            winrt::SDKTemplate::ColorEntry ce;
            ce.ColorName(_colorNames[i]);
            ce.Color(_colors[i]);
            _colorEntries.Append(ce);
        }
    }

    void Functions::ClearColorsClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _colorEntries.Clear();
    }

    void Functions::UpdateValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.UpdateValues();
    }

    void Functions::ResetValuesClick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        _model.InitializeValues();
    }
}
