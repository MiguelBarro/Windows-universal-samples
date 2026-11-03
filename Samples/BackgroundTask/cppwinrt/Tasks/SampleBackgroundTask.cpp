#include "pch.h"
#include "SampleBackgroundTask.h"
#include "SampleBackgroundTask.g.cpp"

namespace winrt::Tasks::implementation
{
    void SampleBackgroundTask::Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance)
    {
        throw hresult_not_implemented();
    }
}
