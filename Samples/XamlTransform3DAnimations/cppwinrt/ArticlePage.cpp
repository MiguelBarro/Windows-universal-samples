#include "pch.h"
#include "ArticlePage.h"
#include "ArticlePage.g.cpp"
#include "ViewModels.ArticleViewModel.h"

namespace winrt::Transform3DAnimations::implementation
{
    /*static*/
    Windows::UI::Xaml::DependencyProperty ArticlePage::ArticleProperty_ =
            Windows::UI::Xaml::DependencyProperty::Register(
                    L"Article",
                    xaml_typename<Transform3DAnimations::ViewModels::ArticleViewModel>(),
                    xaml_typename<Transform3DAnimations::ArticlePage>(),
                    Windows::UI::Xaml::PropertyMetadata{nullptr});

    /*static*/
    Windows::UI::Xaml::DependencyProperty ArticlePage::ArticleProperty()
    {
        return ArticleProperty_;
    }

    Transform3DAnimations::ViewModels::ArticleViewModel ArticlePage::Article()
    {
        return GetValue(ArticleProperty_).as<Transform3DAnimations::ViewModels::ArticleViewModel>();
    }

    void ArticlePage::Article(Transform3DAnimations::ViewModels::ArticleViewModel const& value)
    {
        SetValue(ArticleProperty_, box_value(value));
    }

    ArticlePage::ArticlePage()
    {
        InitializeComponent();

        Windows::UI::Xaml::VisualStateManager::GoToState(
                get_strong().as<winrt::Windows::UI::Xaml::Controls::UserControl>(),
                L"ContentNotLoadedState", false);

        // Simulate asynchronous loading of content
        _loadTimer.Interval(std::chrono::milliseconds(550));
        _loadTimer.Tick({get_weak(), &ArticlePage::LoadTimer_Tick});
    }

    void ArticlePage::LoadTimer_Tick(
            Windows::Foundation::IInspectable const&,
            Windows::Foundation::IInspectable const&)
    {
        // Play content entrance animation
        Windows::UI::Xaml::VisualStateManager::GoToState(
                get_strong().as<Windows::UI::Xaml::Controls::UserControl>(),
                L"ContentLoadedState",
                _uiSettings.AnimationsEnabled());
    }

    void ArticlePage::ArticlePage_BackRequested(
            Windows::Foundation::IInspectable const&,
            Windows::UI::Core::BackRequestedEventArgs const& e)
    {
        e.Handled(true);
        Frame().GoBack();
    }

    void ArticlePage::OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs const& e)
    {
        ViewModels::ArticleViewModel article;
        article.Headline(unbox_value<hstring>(e.Parameter()));
        Article(article);

        _loadTimer.Start();

        auto systemNavigationManager = Windows::UI::Core::SystemNavigationManager::GetForCurrentView();
        _token = systemNavigationManager.BackRequested({get_weak(), &ArticlePage::ArticlePage_BackRequested});
        systemNavigationManager.AppViewBackButtonVisibility(Windows::UI::Core::AppViewBackButtonVisibility::Visible);
    }

    void ArticlePage::OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs const&)
    {
        auto systemNavigationManager = Windows::UI::Core::SystemNavigationManager::GetForCurrentView();
        systemNavigationManager.BackRequested(_token);
        systemNavigationManager.AppViewBackButtonVisibility(Windows::UI::Core::AppViewBackButtonVisibility::Collapsed);
    }
}
