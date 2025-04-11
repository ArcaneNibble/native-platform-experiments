#include "pch.h"
#include "MainWindow.xaml.h"
#if __has_include("MainWindow.g.cpp")
#include "MainWindow.g.cpp"
#endif

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
        updateMenuRadios();
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
        updateMenuRadios();
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

        updateMenuRadios();
    }

    void MainWindow::updateMenuRadios()
    {
        bool custom = true;
        menuD4().IsChecked(m_maxRoll == 4);
        if (m_maxRoll == 4) custom = false;
        menuD6().IsChecked(m_maxRoll == 6);
        if (m_maxRoll == 6) custom = false;
        menuD8().IsChecked(m_maxRoll == 8);
        if (m_maxRoll == 8) custom = false;
        menuD10().IsChecked(m_maxRoll == 10);
        if (m_maxRoll == 10) custom = false;
        menuD12().IsChecked(m_maxRoll == 12);
        if (m_maxRoll == 12) custom = false;
        menuD20().IsChecked(m_maxRoll == 20);
        if (m_maxRoll == 20) custom = false;
        menuCustom().IsChecked(custom);
    }

    void MainWindow::exit_Click(IInspectable const&, RoutedEventArgs const&)
    {
        Close();
    }
}
