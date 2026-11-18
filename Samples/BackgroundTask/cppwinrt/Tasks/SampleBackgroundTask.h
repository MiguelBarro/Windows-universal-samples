#pragma once
#include "SampleBackgroundTask.g.h"

namespace winrt::Tasks::implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask>
    {
        using IBackgroundTaskInstance = Windows::ApplicationModel::Background::IBackgroundTaskInstance;
        using BackgroundTaskDeferral = Windows::ApplicationModel::Background::BackgroundTaskDeferral;
        using BackgroundTaskCancellationReason
            = Windows::ApplicationModel::Background::BackgroundTaskCancellationReason;
        using LoggingChannel = Windows::Foundation::Diagnostics::LoggingChannel;

        SampleBackgroundTask() = default;

        void Run(IBackgroundTaskInstance const& taskInstance);
        void OnCanceled(IBackgroundTaskInstance const& sender, BackgroundTaskCancellationReason const& reason);
        void PeriodicTimerCallback(Windows::System::Threading::ThreadPoolTimer const& timer);

    private:
        BackgroundTaskDeferral _deferral { nullptr };
        IBackgroundTaskInstance _taskInstance { nullptr };
        IBackgroundTaskInstance::Canceled_revoker _revoker;
        LoggingChannel _logger { winrt::get_class_name(*this) };
        Windows::System::Threading::ThreadPoolTimer _periodicTimer { nullptr };
        BackgroundTaskCancellationReason _cancelReason { BackgroundTaskCancellationReason::Abort };
        uint32_t _progress { 0 };
        std::atomic_bool _cancelRequested { false };
    };
}
namespace winrt::Tasks::factory_implementation
{
    struct SampleBackgroundTask : SampleBackgroundTaskT<SampleBackgroundTask, implementation::SampleBackgroundTask>
    {
    };
}
