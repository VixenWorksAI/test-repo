#ifndef TEST_PLACEHOLDER_RESPONSIVENESS_UNIT_H
#define TEST_PLACEHOLDER_RESPONSIVENESS_UNIT_H

#include <QObject>

class TestPlaceholderResponsivenessUnit : public QObject
{
    Q_OBJECT

private slots:
    void gridHasEqualColumnStretches();
    void gridHasEqualRowStretches();
    void gridHasPerColumnMinimumWidths();
    void gridHasPerRowMinimumHeights();
    void centralLayoutEnforcesMinimumSizeConstraint();
    void placeholderButtonsAreExpanding();
    void displayIsExpanding();
};

#endif
