#include <QApplication>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QUrl>
#include <QQuickStyle>
#include <KAboutData>
#include <KConfigGroup>
#include <KSharedConfig>
#include <KLocalizedContext>
#include <KLocalizedString>
#include <KIconTheme>

#include "backend.h"

int main(int argc, char *argv[])
{
    KIconTheme::initTheme();
    QApplication app(argc, argv);
    KLocalizedString::setApplicationDomain("demo-dice");
    QApplication::setOrganizationName(QStringLiteral("ArcaneNibble"));
    QApplication::setOrganizationDomain(QStringLiteral("arcanenibble.com"));
    QApplication::setApplicationName(QStringLiteral("Demo Dice"));
    QApplication::setDesktopFileName(QStringLiteral("com.arcanenibble.KDice"));

    QApplication::setStyle(QStringLiteral("breeze"));
    if (qEnvironmentVariableIsEmpty("QT_QUICK_CONTROLS_STYLE")) {
        QQuickStyle::setStyle(QStringLiteral("org.kde.desktop"));
    }

    KAboutData aboutData(
        QStringLiteral("demo-dice"),
        i18nc("@title", "Demo Dice"),
        QStringLiteral("1.0"),
        i18n("Demo KDE dice app"),
        KAboutLicense::Unknown,
        i18n("© 2025 ArcaneNibble"));
    aboutData.setLicenseText(i18n("0BSD"));
    aboutData.setBugAddress("rqou00@gmail.com");
    aboutData.setOrganizationDomain("arcanenibble.com");
    aboutData.setDesktopFileName(QStringLiteral("com.arcanenibble.KDice"));
    aboutData.addAuthor(
        i18nc("@info:credit", "@ArcaneNibble"),
        i18nc("@info:credit", "Developer"),
        QStringLiteral("rqou00@gmail.com"),
        QStringLiteral("https://arcanenibble.github.io"));
    KAboutData::setApplicationData(aboutData);

    QQmlApplicationEngine engine;

    Backend backend;

    auto config = KSharedConfig::openConfig();
    auto generalGroup = config->group(QStringLiteral("General"));
    backend.setMaxRoll(generalGroup.readEntry("MaxRoll", 20));

    qmlRegisterSingletonInstance<Backend>("com.arcanenibble.demodice", 1, 0, "Backend", &backend);
    qmlRegisterSingletonType(
        "com.arcanenibble.demodice", 1, 0, "About",
        [](QQmlEngine* engine, QJSEngine *) -> QJSValue {
            return engine->toScriptValue(KAboutData::applicationData());
        }
    );


    engine.rootContext()->setContextObject(new KLocalizedContext(&engine));
    engine.loadFromModule("com.arcanenibble.KDice", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }

    return app.exec();
}
