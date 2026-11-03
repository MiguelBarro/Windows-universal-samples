#include "pch.h"
#include <winrt/SDKTemplate.h>
#include "MainPage.h"
#include "SampleConfiguration.h"

using namespace winrt;
using namespace Windows::Foundation::Collections;
using namespace SDKTemplate;

hstring implementation::MainPage::FEATURE_NAME()
{
    return L"Background tasks";
}

IVector<Scenario> implementation::MainPage::scenariosInner = winrt::single_threaded_observable_vector<Scenario>(
{
    Scenario{ L"Background Task", xaml_typename<SDKTemplate::SampleBackgroundTask>() },
    Scenario{ L"Background Task with Condition", xaml_typename<SDKTemplate::SampleBackgroundTaskWithCondition>() },
    Scenario{ L"Servicing Complete Task", xaml_typename<SDKTemplate::ServicingCompleteTask>() },
    Scenario{ L"Background Task with Time Trigger", xaml_typename<SDKTemplate::TimeTriggeredTask>() },
    Scenario{ L"Background Task with Application Trigger", xaml_typename<SDKTemplate::ApplicationTriggerTask>() },
    Scenario{ L"Grouped Background Task", xaml_typename<SDKTemplate::GroupedBackgroundTask>() }
});
