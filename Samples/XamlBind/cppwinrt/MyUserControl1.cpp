#include "pch.h"
#include "MyUserControl1.h"
#include "MyUserControl1.g.cpp"

namespace winrt::SDKTemplate::implementation
{
    hstring MyUserControl1::NonDPProperty()
    {
        return hstring(_nonDP);
    }

    void MyUserControl1::NonDPProperty(hstring const& value)
    {
        if ( _nonDP != value)
        {
            _nonDP = value;
            _event(*this, winrt::Windows::UI::Xaml::Data::PropertyChangedEventArgs(L"NonDPProperty"));
        }
    }

    winrt::event_token MyUserControl1::PropertyChanged(winrt::Windows::UI::Xaml::Data::PropertyChangedEventHandler const& handler)
    {
        return _event.add(handler);
    }

    void MyUserControl1::PropertyChanged(winrt::event_token const& token) noexcept
    {
        _event.remove(token);
    }
}
