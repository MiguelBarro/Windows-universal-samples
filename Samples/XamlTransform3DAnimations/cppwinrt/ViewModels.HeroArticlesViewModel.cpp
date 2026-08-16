#include "pch.h"
#include "ViewModels.HeroArticlesViewModel.h"
#include "ViewModels.HeroArticlesViewModel.g.cpp"

namespace winrt::Transform3DAnimations::ViewModels::implementation
{
    Transform3DAnimations::ViewModels::ArticleViewModel HeroArticlesViewModel::Article0()
    {
        return _a0;
    }

    void HeroArticlesViewModel::Article0(Transform3DAnimations::ViewModels::ArticleViewModel const& value)
    {
        if (_a0 != value)
        {
            _a0 = value;
            _propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Article0" });
        }
    }

    Transform3DAnimations::ViewModels::ArticleViewModel HeroArticlesViewModel::Article1()
    {
        return _a1;
    }

    void HeroArticlesViewModel::Article1(Transform3DAnimations::ViewModels::ArticleViewModel const& value)
    {
        if (_a1 != value)
        {
            _a1 = value;
            _propertyChanged(*this, Windows::UI::Xaml::Data::PropertyChangedEventArgs{ L"Article1" });
        }
    }

    event_token HeroArticlesViewModel::PropertyChanged(Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return _propertyChanged.add(handler);
    }

    void HeroArticlesViewModel::PropertyChanged(event_token const& token) noexcept
    {
        _propertyChanged.remove(token);
    }
}
