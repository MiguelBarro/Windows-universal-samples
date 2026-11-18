#pragma once

// #include "Windows.ApplicationModel.Background.h"

namespace winrt
{
   using namespace Windows::ApplicationModel::Background;

    hstring to_hstring(BackgroundWorkCostValue const& cost)
    {
        switch (cost)
        {
        case BackgroundWorkCostValue::Low:
            return L"Low";
        case BackgroundWorkCostValue::Medium:
            return L"Medium";
        case BackgroundWorkCostValue::High:
            return L"High";
        default:
            throw hresult_error(E_FAIL, L"Unknown BackgroundWorkCost value");
        }
    }

    hstring to_hstring(BackgroundTaskCancellationReason const& reason)
    {
        switch (reason)
        {
        case BackgroundTaskCancellationReason::Abort:
            return L"Abort";
        case BackgroundTaskCancellationReason::Terminating:
            return L"Terminating";
        case BackgroundTaskCancellationReason::LoggingOff:
            return L"LoggingOff";
        case BackgroundTaskCancellationReason::ServicingUpdate:
            return L"ServicingUpdate";
        case BackgroundTaskCancellationReason::IdleTask:
            return L"IdleTask";
        case BackgroundTaskCancellationReason::Uninstall:
            return L"Uninstall";
        default:
            throw hresult_error(E_FAIL, L"Unknown BackgroundTaskCancellationReason value");
        }
    }
}
