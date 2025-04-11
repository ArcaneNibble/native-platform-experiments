#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

#include <sstream>

using namespace winrt;
using namespace Microsoft::UI::Xaml;
using namespace Windows::Foundation;
using namespace Windows::Security::Cryptography;

namespace winrt::DemoDice::implementation
{
    void MainWindow::InitializeComponent()
    {
        MainWindowT::InitializeComponent();
        AppWindow().Resize({ 800, 800 });
    }

    winrt::event_token MainWindow::PropertyChanged(Data::PropertyChangedEventHandler const& handler)
    {
        return m_propertyChanged.add(handler);
    }
    void MainWindow::PropertyChanged(winrt::event_token const& token)
    {
        m_propertyChanged.remove(token);
    }

    hstring MainWindow::AppTitle() const
    {
        std::wostringstream s;
        s << L"Demo Dice - D" << m_maxRoll;
        return hstring(s.str());
    }
    bool MainWindow::IsDice4() const
    {
        return m_maxRoll == 4;
    }
    bool MainWindow::IsDice6() const
    {
        return m_maxRoll == 6;
    }
    bool MainWindow::IsDice8() const
    {
        return m_maxRoll == 8;
    }
    bool MainWindow::IsDice10() const
    {
        return m_maxRoll == 10;
    }
    bool MainWindow::IsDice12() const
    {
        return m_maxRoll == 12;
    }
    bool MainWindow::IsDice20() const
    {
        return m_maxRoll == 20;
    }
    bool MainWindow::IsDiceCustom() const
    {
        if (m_maxRoll == 4) return false;
        if (m_maxRoll == 6) return false;
        if (m_maxRoll == 8) return false;
        if (m_maxRoll == 10) return false;
        if (m_maxRoll == 12) return false;
        if (m_maxRoll == 20) return false;
        return true;
    }

    void MainWindow::rollButton_Click(IInspectable const&, RoutedEventArgs const&)
    {
        uint64_t rand_div = 0x100000000L / m_maxRoll;
        uint64_t rand_cap = rand_div * m_maxRoll;
        uint32_t rand_roll;
        do {
            rand_roll = CryptographicBuffer::GenerateRandomNumber();
        } while (rand_roll >= rand_cap);
        uint32_t dice_roll = (uint32_t)(rand_roll / rand_div + 1);

        rollButton().Content(box_value(dice_roll));
    }

    void MainWindow::setFixedMaxRoll_Click(IInspectable const& sender, RoutedEventArgs const&)
    {
        auto btn = unbox_value<FrameworkElement>(sender);
        auto tag = unbox_value<hstring>(btn.Tag());
        m_maxRoll = wcstol(tag.c_str(), nullptr, 10);
        updateUI();
    }

    IAsyncAction MainWindow::setCustomMaxRoll_Click(IInspectable const&, RoutedEventArgs const&)
    {
        auto dlg = Controls::ContentDialog();
        dlg.XamlRoot(root().XamlRoot());
        dlg.Title(box_value(L"Set Custom Dice"));
        dlg.PrimaryButtonText(L"OK");
        dlg.CloseButtonText(L"Cancel");
        dlg.DefaultButton(Controls::ContentDialogButton::Primary);

        auto box = Controls::NumberBox();
        box.Header(box_value(L"Number of sides"));
        box.PlaceholderText(L"20");
        box.Value(m_maxRoll);
        box.SpinButtonPlacementMode(Controls::NumberBoxSpinButtonPlacementMode::Inline);
        box.Minimum(1);
        dlg.Content(box);

        auto res = co_await dlg.ShowAsync();
        if (res == Controls::ContentDialogResult::Primary)
        {
            auto new_val = box.Value();
            if (!isnan(new_val) && new_val >= 1) {
                m_maxRoll = (int)new_val;
            }
        }

        updateUI();
    }

    void MainWindow::updateUI()
    {
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"AppTitle" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice4" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice6" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice8" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice10" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice12" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDice20" });
        m_propertyChanged(*this, Data::PropertyChangedEventArgs{ L"IsDiceCustom" });
    }

    void MainWindow::exit_Click(IInspectable const&, RoutedEventArgs const&)
    {
        Close();
    }
}
