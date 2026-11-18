#include "pch.h"
#include "Utils.h"
#include "SampleBackgroundTask.h"
#include "SampleBackgroundTask.g.cpp"

namespace winrt::Tasks::implementation
{
    void SampleBackgroundTask::Run(IBackgroundTaskInstance const& taskInstance)
    {
        using namespace Windows::ApplicationModel::Background;
        using namespace Windows::Foundation::Diagnostics;

        _logger.LogMessage(
                L"Background " + taskInstance.Task().Name() + L" Starting...",
                LoggingLevel::Information);

        //
        // Query BackgroundWorkCost
        // Guidance: If BackgroundWorkCost is high, then perform only the minimum amount
        // of work in the background task and return immediately.
        //
        auto cost = BackgroundWorkCost::CurrentBackgroundWorkCost();
        auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
        settings.Values().Insert(L"BackgroundWorkCost", winrt::box_value(to_hstring(cost)));

        //
        // Associate a cancellation handler with the background task.
        //
        _revoker = taskInstance.Canceled(winrt::auto_revoke, { this, &SampleBackgroundTask::OnCanceled });

        //
        // Get the deferral object from the task instance, and take a reference to the taskInstance;
        //
        _deferral = taskInstance.GetDeferral();
        _taskInstance = taskInstance;

        _periodicTimer = Windows::System::Threading::ThreadPoolTimer::CreatePeriodicTimer(
                { this, &SampleBackgroundTask::PeriodicTimerCallback},
                std::chrono::seconds(1));
    }

    void SampleBackgroundTask::OnCanceled(
            IBackgroundTaskInstance const& sender,
            BackgroundTaskCancellationReason const& reason)
    {
        using namespace Windows::Foundation::Diagnostics;

        //
        // Indicate that the background task is canceled.
        //
        _cancelReason = reason;
        _cancelRequested = true;

        _logger.LogMessage(
                L"Background " + sender.Task().Name() + L" Cancel Requested...",
                LoggingLevel::Information);
    }

    void SampleBackgroundTask::PeriodicTimerCallback(Windows::System::Threading::ThreadPoolTimer const&)
    {
        using namespace Windows::Foundation::Diagnostics;

        if (!_cancelRequested && _progress < 100)
        {
            _progress += 10;
            _taskInstance.Progress(_progress);
        }
        else
        {
            _periodicTimer.Cancel();

            //
            // Record that this background task ran.
            //
            auto settings = Windows::Storage::ApplicationData::Current().LocalSettings();
            auto key = _taskInstance.Task().Name();
            auto task_status = _progress < 100 ? L"Canceled with reason: " + to_hstring(_cancelReason) : L"Completed";
            settings.Values().Insert(key, winrt::box_value(task_status));

            _logger.LogMessage(
                    L"Background " + _taskInstance.Task().Name() + task_status,
                    LoggingLevel::Information);

            //
            // Indicate that the background task has completed.
            //
            _deferral.Complete();
        }
    }
}
