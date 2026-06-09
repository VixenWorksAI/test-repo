#ifndef TEST_ADDITION_UNIT_H
#define TEST_ADDITION_UNIT_H

#include <QObject>

class TestAdditionUnit : public QObject
{
    Q_OBJECT

private slots:
    void additionOfTwoPositiveNumbers();
    void additionOfTwoNegativeNumbers();
    void additionOfLargeAndSmallPreservesPrecision();
    void additionOverflowClampsToMaxDouble();
    void additionUnderflowClampsToMinDouble();
};

#endif
