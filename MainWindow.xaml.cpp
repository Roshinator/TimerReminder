#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winrt::TimerReminder::implementation
{
    void MainWindow::MainWindow_Activated(IInspectable const& sender, WindowActivatedEventArgs const& e)
    {
        if (e.WindowActivationState() == WindowActivationState::Deactivated)
        {
            TitleBarTextBlock().Foreground(
                Application::Current().Resources()
                .Lookup(winrt::box_value(L"WindowCaptionForegroundDisabled"))
                .as<Media::Brush>()
            );
        }
        else
        {
            TitleBarTextBlock().Foreground(
                Application::Current().Resources()
                .Lookup(winrt::box_value(L"WindowCaptionForeground"))
                .as<Media::Brush>()
            );
        }
    }

    int32_t MainWindow::MyProperty()
    {
        throw hresult_not_implemented();
    }

    void MainWindow::MyProperty(int32_t /* value */)
    {
        throw hresult_not_implemented();
    }

    void MainWindow::myButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        myButton().Content(box_value(L"Clicked"));
    }
}
