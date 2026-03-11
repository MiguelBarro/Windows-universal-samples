#pragma once
#include "Scenario.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Scenario : ScenarioT<Scenario>
    {
        Scenario() = default;

        Scenario(hstring const& title, hstring const& description, hstring const& className);
        hstring Title();
        void Title(hstring const& value);
        hstring Description();
        void Description(hstring const& value);
        hstring ClassName();
        void ClassName(hstring const& value);

        private:
            std::wstring _title, _description, _className;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Scenario : ScenarioT<Scenario, implementation::Scenario>
    {
    };
}
