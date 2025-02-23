#pragma once

#include "MainWindow.g.h"

namespace winrt::TimerReminder::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {

        MainWindow()
        {
            // Xaml objects should not call InitializeComponent during construction.
            // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

            ExtendsContentIntoTitleBar(true);

            m_activationEvent = Activated({get_weak(), &MainWindow::MainWindow_Activated});
        }

        void MainWindow_Activated(IInspectable const& sender, Microsoft::UI::Xaml::WindowActivatedEventArgs const& args);

        int32_t MyProperty();
        void MyProperty(int32_t value);

        void myButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        event_token m_activationEvent;

    };
}

namespace winrt::TimerReminder::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
