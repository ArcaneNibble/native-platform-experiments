#pragma once

#include <QObject>

class Backend : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int maxRoll READ maxRoll WRITE setMaxRoll NOTIFY maxRollChanged)

public:
    explicit Backend(QObject *parent = nullptr);
    int maxRoll() const;
    void setMaxRoll(int newMaxRoll);
    Q_SIGNAL void maxRollChanged();
    Q_INVOKABLE int roll();

private:
    int m_maxRoll;
};
