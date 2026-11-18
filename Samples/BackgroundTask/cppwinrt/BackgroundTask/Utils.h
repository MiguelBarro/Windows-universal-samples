#pragma once

// #include "Windows.ApplicationModel.Background.h"

namespace winrt
{
    hstring to_hstring(
            Windows::ApplicationModel::Background::ApplicationTriggerResult result)
    {
        using namespace Windows::ApplicationModel::Background;

        switch (result)
        {
        case ApplicationTriggerResult::Allowed:
            return L"Allowed";
        case ApplicationTriggerResult::CurrentlyRunning:
            return L"CurrentlyRunning";
        case ApplicationTriggerResult::DisabledByPolicy:
            return L"DisabledByPolicy";
        case ApplicationTriggerResult::UnknownError:
            return L"UnknownError";
        default:
            throw hresult_error(E_FAIL, L"Unknown ApplicationTriggerResult value");
        }
    }

} // namespace winrt
