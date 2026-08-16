#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

#include "winrt/Transform3DAnimations.ViewModels.h"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::Transform3DAnimations::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();

        _updateTimer.Interval(std::chrono::seconds(1));
        _updateTimer.Tick({get_weak(), &MainPage::UpdateTimer_Tick});
    }

    void MainPage::UpdateTimer_Tick(
            winrt::Windows::Foundation::IInspectable const&,
            winrt::Windows::Foundation::IInspectable const&)
    {
        UpdateRandomSection();
    }

    void MainPage::UpdateRandomSection()
    {
        // Updating the section triggers a cool animation!
        // See SectionView.xaml and SectionView.xaml.cs
        auto sectionsInView = HeadlinesHub().SectionsInView();
        auto sectionsCount = sectionsInView.Size();

        if (sectionsCount > 0)
        {
            std::uniform_int_distribution<uint32_t>::param_type params(0, sectionsCount - 1);
            auto sectionToUpdate = sectionsInView.GetAt(_random(_gen, params));
            sectionToUpdate.DataContext(ViewModels::HeroArticlesViewModel());
        }
    }

    void MainPage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        _updateTimer.Start();
    }

    void MainPage::OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        _updateTimer.Stop();
    }

    void MainPage::SectionView_ArticleSelected(
                Windows::Foundation::IInspectable const&,
                ViewModels::ArticleViewModel const& e)
    {
        // In a real app, you might pass a unique ID for the article as a navigation parameter.
        // Here we pass the title.
        Frame().Navigate(
                winrt::xaml_typename<winrt::Transform3DAnimations::ArticlePage>(),
                winrt::box_value(e.Headline()));
    }
}
