#pragma once

#include "MainWindow.g.h"

namespace winrt::DemoDice::implementation
{
    struct MainWindow : MainWindowT<MainWindow>
    {
        MainWindow()
        {
            m_maxRoll = 20;
        }

        void InitializeComponent();

        void rollButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void setFixedMaxRoll_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction setCustomMaxRoll_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void exit_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        uint32_t m_maxRoll;
        void updateMenuRadios();
    };
}

namespace winrt::DemoDice::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
