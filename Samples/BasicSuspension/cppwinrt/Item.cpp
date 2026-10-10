#include "pch.h"
#include "Item.h"
#include "Item.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Item::Item(std::wstring_view const& name) : Item(hstring(name))
    {
    }

    Item::Item(hstring const& name) : _name(name)
    {
    }

    Item::Item(hstring && name) : _name(std::move(name))
    {
    }

    hstring Item::Name()
    {
        return _name;
    }

    void Item::Name(std::wstring_view const& value)
    {
        Name(hstring(value));
    }

    void Item::Name(hstring const& value)
    {
        _name = value;
    }

    void Item::Name(hstring && value)
    {
        _name = std::move(value);
    }

    void Item::Taps(int32_t value)
    {
        _taps = value;
    }

    int32_t Item::Taps()
    {
        return _taps;
    }

    hstring Item::ToString()
    {
        return Name();
    }
}
