#include "pch.h"
#include "Item.h"
#include "Item.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Item::Item(std::wstring_view const& name, int32_t taps)
        : Item(hstring(name), taps)
    {
    }

    Item::Item(hstring const& name, int32_t taps)
        : _name(name)
        , _taps(taps)
    {
    }

    Item::Item(hstring && name, int32_t taps)
        : _name(std::move(name))
        , _taps(taps)
    {
    }

    Item::Item(Windows::Data::Json::JsonObject const& state)
        : _name(state.GetNamedString(namePropertyName))
        , _taps(static_cast<int32_t>(
                    state.GetNamedNumber(tapsPropertyName)))
    {
    }

    Windows::Data::Json::JsonObject Item::ToJsonObject()
    {
        Windows::Data::Json::JsonObject state;
        state.SetNamedValue(
                namePropertyName,
                Windows::Data::Json::JsonValue::CreateStringValue(_name)
                );
        state.SetNamedValue(
                tapsPropertyName,
                Windows::Data::Json::JsonValue::CreateNumberValue(static_cast<double>(_taps))
                );
        return state;
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
