#include "pch.h"

#include "Scenario2_MarkHotProducts.h"
#include "Scenario2_MarkHotProducts.g.cpp"

#include <format>

#include "SampleConfiguration.h"

namespace winrt::SDKTemplate::implementation
{
    Scenario2_MarkHotProducts::Scenario2_MarkHotProducts()
    {
        InitializeComponent();
        Scenario2Init();
    }

    void Scenario2_MarkHotProducts::OnNavigatedTo(winrt::Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        rootPage_ = MainPage::Current();
    }

    winrt::fire_and_forget Scenario2_MarkHotProducts::Scenario2Init() try
    {
        auto doc = co_await LoadXmlFile(L"markHotProducts", L"products.xml");
        RichEditBoxSetMsg(scenario2OriginalData(), doc.GetXml(), true);
    }
    catch (hresult_error const& e)
    {
        RichEditBoxSetError(scenario2Result(), e.message());
        rootPage_.NotifyUser(L"Exception occured while loading xml file!", NotifyType::ErrorMessage);
    }

    void Scenario2_MarkHotProducts::Scenario2BtnDefault_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::hstring xml;
        scenario2OriginalData().Document().GetText(
                winrt::Windows::UI::Text::TextGetOptions::None,
                xml);

        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXml(xml);

        // Mark 'hot' attribute to '1' if 'sell10days' is greater than 'InStore'
        auto hotAttributes = doc.SelectNodes(L"/products/product[Sell10day>InStore]/@hot");
        for (auto const& hotAttribute : hotAttributes)
            hotAttribute.NodeValue(winrt::box_value(L"1"));

        RichEditBoxSetMsg(scenario2Result(), doc.GetXml(), true);
        scenario2BtnSave().IsEnabled(true); // enable Save button
    }

    winrt::fire_and_forget Scenario2_MarkHotProducts::Scenario2BtnSave_Click(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::UI::Xaml::RoutedEventArgs const&)
    {
        winrt::hstring xml;
        scenario2Result().Document().GetText(
                winrt::Windows::UI::Text::TextGetOptions::None,
                xml);

        winrt::Windows::Data::Xml::Dom::XmlDocument doc;
        doc.LoadXml(xml);

        // save xml to a file
        auto file = co_await winrt::Windows::Storage::ApplicationData::Current().LocalFolder().CreateFileAsync(
                L"HotProducts.xml",
                winrt::Windows::Storage::CreationCollisionOption::GenerateUniqueName);
        co_await doc.SaveToFileAsync(file);

        RichEditBoxSetMsg(
                scenario2Result(),
                winrt::hstring(std::format(L"Save to \"{}\" successfully.", file.Path())),
                true);
        scenario2BtnSave().IsEnabled(false);
    }
}
