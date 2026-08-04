#include "pch.h"

#include "Scenario4_GiftDispatch.h"

#include <array>
#include <format>

#include "SampleConfiguration.h"
#include "Scenario4_GiftDispatch.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario4_GiftDispatch::Scenario4_GiftDispatch()
    {
        InitializeComponent();
        Scenario4Init();
    }

    winrt::fire_and_forget Scenario4_GiftDispatch::Scenario4Init() try
    {
        auto doc = co_await LoadXmlFile(L"giftDispatch", L"employees.xml");
            RichEditBoxSetMsg(scenario4OriginalData(), doc.GetXml(), true);
    }
    catch (hresult_error const&)
    {
        RichEditBoxSetError(scenario4Result(), L"Exception occured while loading xml file!");
    }

    void Scenario4_GiftDispatch::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    void Scenario4_GiftDispatch::Scenario4BtnDefault_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::hstring xml;
        scenario4OriginalData().Document().GetText(
                winrt::Windows::UI::Text::TextGetOptions::None,
                xml);

        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXml(xml);

        unsigned int thisYear = 2012;    // Here we don't use DateTime.Now.Year to get the current year so that all gifts can be delivered.
        auto previousOneYear = thisYear - 1;
        auto previousFiveYear = thisYear - 5;
        auto previousTenYear = thisYear - 10;

        std::array<std::wstring, 3> xpathArray {
            std::format(L"descendant::employee[startyear <= {} and startyear > {}]", previousOneYear, previousFiveYear),
            std::format(L"descendant::employee[startyear <= {} and startyear > {}]", previousFiveYear, previousTenYear),
            std::format(L"descendant::employee[startyear <= {}]", previousTenYear)
        };
        std::array<winrt::hstring, 3> Gifts { L"Gift Card", L"XBOX", L"Windows Phone" };
        std::wstring output;
        unsigned int i = 0;

        for (auto& xpath : xpathArray)
        {
            for (auto employee : doc.SelectNodes(xpath))
            {
                auto employeeName = employee.SelectSingleNode(L"descendant::name");
                auto department = employee.SelectSingleNode(L"descendant::department");
                output += std::format(
                        L"[{}]/[{}]/[{}]\n",
                        winrt::unbox_value<winrt::hstring>(employeeName.FirstChild().NodeValue()),
                        winrt::unbox_value<winrt::hstring>(department.FirstChild().NodeValue()),
                        Gifts[(++i) % 3]);
            }
        }

        RichEditBoxSetMsg(scenario4Result(), winrt::hstring(output), true);
    }
}
