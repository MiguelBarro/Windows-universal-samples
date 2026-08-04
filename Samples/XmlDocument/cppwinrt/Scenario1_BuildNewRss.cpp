#include "pch.h"
#include "SampleConfiguration.h"
#include "Scenario1_BuildNewRss.h"
#include "Scenario1_BuildNewRss.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    Scenario1_BuildNewRss::Scenario1_BuildNewRss()
    {
        InitializeComponent();
        Scenario1Init();
    }

    void Scenario1_BuildNewRss::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    winrt::fire_and_forget Scenario1_BuildNewRss::Scenario1Init() try
    {
        auto doc = co_await LoadXmlFile(L"buildRss", L"rssTemplate.xml");
        RichEditBoxSetMsg(scenario1OriginalData(), doc.GetXml(), true);
    }
    catch (hresult_error const& e)
    {
        RichEditBoxSetError(scenario1Result(), e.message());
        rootPage_.NotifyUser(L"Exception occured while loading xml file!", NotifyType::ErrorMessage);
    }

    void Scenario1_BuildNewRss::Scenario1BtnDefault_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        auto rss = scenario1RssInput().Text();
        if (rss.empty())
        {
            RichEditBoxSetError(scenario1Result(), L"Please type in RSS content in the [RSS Content] box firstly.");
        }
        else
        {
            winrt::hstring xml;
            winrt::Windows::Data::Xml::Dom::XmlDocument doc;

            scenario1OriginalData().Document().GetText(
                    winrt::Windows::UI::Text::TextGetOptions::None,
                    xml);
            doc.LoadXml(xml);

            // create a rss CDataSection and insert into DOM tree
            auto cdata = doc.CreateCDataSection(rss);
            auto element = doc.GetElementsByTagName(L"content").Item(0);
            element.AppendChild(cdata);

            RichEditBoxSetMsg(scenario1Result(), doc.GetXml(), true);
        }
    }
}
