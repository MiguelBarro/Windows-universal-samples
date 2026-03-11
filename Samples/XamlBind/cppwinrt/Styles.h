#pragma once
#include "Styles.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Styles : StylesT<Styles>
    {
        Styles() = default;

    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Styles : StylesT<Styles, implementation::Styles>
    {
    };
}
