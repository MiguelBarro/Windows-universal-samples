#pragma once
#include "Item.g.h"

#include <cstdint>

namespace winrt::SDKTemplate::implementation
{
    struct Item : ItemT<Item>
    {
        Item(std::wstring_view const& name);
        Item(hstring const& name);
        Item(hstring && name);

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
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Item : ItemT<Item, implementation::Item>
    {
    };
}
