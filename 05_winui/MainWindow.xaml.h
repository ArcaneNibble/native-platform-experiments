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

        winrt::event_token PropertyChanged(Microsoft::UI::Xaml::Data::PropertyChangedEventHandler const& value);
        void PropertyChanged(winrt::event_token const& token);

        winrt::hstring AppTitle() const;
        bool IsDice4() const;
        bool IsDice6() const;
        bool IsDice8() const;
        bool IsDice10() const;
        bool IsDice12() const;
        bool IsDice20() const;
        bool IsDiceCustom() const;

        void rollButton_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void setFixedMaxRoll_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        Windows::Foundation::IAsyncAction setCustomMaxRoll_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);
        void exit_Click(IInspectable const& sender, Microsoft::UI::Xaml::RoutedEventArgs const& args);

    private:
        uint32_t m_maxRoll;
        winrt::event<Microsoft::UI::Xaml::Data::PropertyChangedEventHandler> m_propertyChanged;
        Microsoft::Windows::ApplicationModel::Resources::ResourceLoader m_resx;

        void updateUI();
    };
}

namespace winrt::DemoDice::factory_implementation
{
    struct MainWindow : MainWindowT<MainWindow, implementation::MainWindow>
    {
    };
}
