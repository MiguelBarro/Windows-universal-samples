#pragma once
#include "ArticlePage.g.h"
#include "ViewModels.ArticleViewModel.h"

namespace winrt::Transform3DAnimations::implementation
{
    struct ArticlePage : ArticlePageT<ArticlePage>
    {
        ArticlePage();

        static Windows::UI::Xaml::DependencyProperty ArticleProperty();
        Transform3DAnimations::ViewModels::ArticleViewModel Article();
        void Article(ViewModels::ArticleViewModel const& value);

        void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);
        void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e);

    private:
        static Windows::UI::Xaml::DependencyProperty ArticleProperty_;

        event_token _token;
        Windows::UI::Xaml::DispatcherTimer _loadTimer;
        Windows::UI::ViewManagement::UISettings _uiSettings;

        void LoadTimer_Tick(
                winrt::Windows::Foundation::IInspectable const&,
                winrt::Windows::Foundation::IInspectable const&);
        void ArticlePage_BackRequested(
                Windows::Foundation::IInspectable const& sender,
                Windows::UI::Core::BackRequestedEventArgs const& e);
    };
}
namespace winrt::Transform3DAnimations::factory_implementation
{
    struct ArticlePage : ArticlePageT<ArticlePage, implementation::ArticlePage>
    {
    };
}
