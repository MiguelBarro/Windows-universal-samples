#pragma once

#include "MainPage.g.h"

namespace winrt::Transform3DAnimations::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void SectionView_ArticleSelected(
                Windows::Foundation::IInspectable const& sender,
                Transform3DAnimations::ViewModels::ArticleViewModel const& e);

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const&);

    private:
        std::mt19937 _gen {42};
        std::uniform_int_distribution<uint32_t> _random;
        winrt::Windows::UI::Xaml::DispatcherTimer _updateTimer;

        void UpdateTimer_Tick(
                winrt::Windows::Foundation::IInspectable const& sender,
                winrt::Windows::Foundation::IInspectable const& e);

        void UpdateRandomSection();
    };
}

namespace winrt::Transform3DAnimations::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}
