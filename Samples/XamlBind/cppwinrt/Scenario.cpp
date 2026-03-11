#include "pch.h"
#include "Scenario.h"
#include "Scenario.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario::Scenario(hstring const& title, hstring const& description, hstring const& className)
        : _title(title), _description(description), _className(className)
    {
    }

    hstring Scenario::Title()
    {
        return hstring(_title);
    }

    void Scenario::Title(hstring const& value)
    {
        _title = value;
    }

    hstring Scenario::Description()
    {
        return hstring(_description);
    }

    void Scenario::Description(hstring const& value)
    {
        _description = value;
    }

    hstring Scenario::ClassName()
    {
        return hstring(_className);
    }

    void Scenario::ClassName(hstring const& value)
    {
        _className = value;
    }
}
