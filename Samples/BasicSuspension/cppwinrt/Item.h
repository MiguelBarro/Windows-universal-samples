#pragma once
#include "Item.g.h"

#include <cstdint>

namespace winrt::SDKTemplate::implementation
{
    struct Item : ItemT<Item>
    {
        Item(std::wstring_view const& name, int32_t taps = 0);
        Item(hstring const& name, int32_t taps = 0);
        Item(hstring && name, int32_t taps = 0);
        Item(Windows::Data::Json::JsonObject const& state);

        Windows::Data::Json::JsonObject ToJsonObject();

        hstring Name();
        void Name(hstring const& value);
        void Name(hstring && value);
        void Name(std::wstring_view const& value);
        void Taps(int32_t value);
        int32_t Taps();
        hstring ToString();

    private:
        hstring _name;
        int32_t _taps {};

        static constexpr std::wstring_view namePropertyName { L"Name" };
        static constexpr std::wstring_view tapsPropertyName { L"Taps" };
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
