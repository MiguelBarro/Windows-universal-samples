#pragma once
#include "SampleBackgroundTask.g.h"

namespace winrt::Tasks::implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask>
    {
        SampleBackgroundTask() = default;

        void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);
    };
}
namespace winrt::Tasks::factory_implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask, implementation::SampleBackgroundTask>
    {
    };
}
