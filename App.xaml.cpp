#include "pch.h"
#include "App.xaml.h"
#include "MainWindow.xaml.h"

using namespace winrt;
using namespace winrt::Microsoft::UI::Xaml;
using namespace winrt::Windows::Foundation;
using namespace winrt::Microsoft::Windows::AppLifecycle;

using namespace TimerReminder;
using namespace TimerReminder::implementation;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.


/// <summary>
/// Initializes the singleton application object.  This is the first line of authored code
/// executed, and as such is the logical equivalent of main() or WinMain().
/// </summary>
App::App()
{
    // Xaml objects should not call InitializeComponent during construction.
    // See https://github.com/microsoft/cppwinrt/tree/master/nuget#initializecomponent

#if defined _DEBUG && !defined DISABLE_XAML_GENERATED_BREAK_ON_UNHANDLED_EXCEPTION
    UnhandledException([](IInspectable const&, UnhandledExceptionEventArgs const& e)
    {
        if (IsDebuggerPresent())
        {
            auto errorMessage = e.Message();
            __debugbreak();
        }
    });
#endif
}

/// <summary>
/// Invoked when the application is launched.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched([[maybe_unused]] LaunchActivatedEventArgs const& e)
{
    window = make<MainWindow>();
    window.Activate();
}

wil::unique_event redirectEventHandle;

winrt::fire_and_forget Redirect(AppInstance keyInstance, AppActivationArguments args)
{
    //Sets event to trigger on scope exit
    wil::event_set_scope_exit ensure_signaled = wil::SetEvent_scope_exit(redirectEventHandle.get());
    co_await keyInstance.RedirectActivationToAsync(args); //Spawns new routine to handle redirection and waits
}

// Main //////////////////////////////////////////////////////////////////////
int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    winrt::init_apartment(winrt::apartment_type::single_threaded);
    //messages = winrt::single_threaded_observable_vector<IInspectable>();
    //see: https://github.com/microsoft/WindowsAppSDK-Samples/blob/main/Samples/AppLifecycle/Instancing/cpp/cpp-winui-packaged/CppWinUiDesktopInstancing/CppWinUiDesktopInstancing/App.xaml.cpp
    bool isRedirect = false;

    AppActivationArguments args = AppInstance::GetCurrent().GetActivatedEventArgs();
    ExtendedActivationKind kind = args.Kind();
    if (kind == ExtendedActivationKind::Launch)
    {
        //Standard launch
    }
    else if (kind == ExtendedActivationKind::File)
    {
        //Launched from file
    }

    auto instances = AppInstance::GetInstances();
    if (instances.Size() > 1)
    {
        isRedirect = true;
        redirectEventHandle.create();
        Redirect(instances.GetAt(0), args);
        DWORD handleIndex = 0;
        HANDLE rawHandle = redirectEventHandle.get();
        if (CoWaitForMultipleObjects(CWMO_DEFAULT, INFINITE, 1, &rawHandle, &handleIndex) != 0)
        {
            OutputDebugString(L"Failed to wait for event");
        }
    }
    
    if (!isRedirect)
    {
        ::winrt::Microsoft::UI::Xaml::Application::Start(
            [](auto&&)
            {
                ::winrt::make<winrt::TimerReminder::implementation::App>();
            }
        );
    }

    return 0;
}
