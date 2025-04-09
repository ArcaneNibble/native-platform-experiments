#include "backend.h"

#include <QRandomGenerator>
#include <KConfigGroup>
#include <KSharedConfig>

#include <cstdio>

Backend::Backend(QObject *parent)
    : QObject(parent)
{
    m_maxRoll = 20;
}

int Backend::maxRoll() const {
    return m_maxRoll;
}
void Backend::setMaxRoll(int newMaxRoll) {
    if (newMaxRoll > 0) {
        m_maxRoll = newMaxRoll;
        Q_EMIT maxRollChanged();

        auto config = KSharedConfig::openConfig();
        auto generalGroup = config->group(QStringLiteral("General"));
        generalGroup.writeEntry("MaxRoll", m_maxRoll);
        config->sync();
    }
}

int Backend::roll()
{
    int roll = QRandomGenerator::global()->bounded(m_maxRoll);
    return roll + 1;
}
