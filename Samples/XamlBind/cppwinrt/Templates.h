#pragma once
#include "Templates.g.h"

namespace winrt::SDKTemplate::implementation
{
    struct Templates : TemplatesT<Templates>
    {
        Templates() = default;
    };
}
namespace winrt::SDKTemplate::factory_implementation
{
    struct Templates : TemplatesT<Templates, implementation::Templates> {};
}
