#pragma once

#include "App.xaml.g.h"

namespace winrt::TimerReminder::implementation
{
    struct App : AppT<App>
    {
        App();

        void OnLaunched(Microsoft::UI::Xaml::LaunchActivatedEventArgs const&);

    private:
        winrt::Microsoft::UI::Xaml::Window window{ nullptr };
    };

}

//extern winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Foundation::IInspectable> messages;