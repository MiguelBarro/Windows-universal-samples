#pragma once
#include "ServicingComplete.g.h"

namespace winrt::Tasks::implementation
{
    struct ServicingComplete : ServicingCompleteT<ServicingComplete>
    {
        ServicingComplete() = default;

        void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);
    };
}
namespace winrt::Tasks::factory_implementation
{
    struct ServicingComplete : ServicingCompleteT<ServicingComplete, implementation::ServicingComplete>
    {
    };
}
