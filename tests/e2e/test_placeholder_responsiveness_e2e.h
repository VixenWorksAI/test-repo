#ifndef TEST_PLACEHOLDER_RESPONSIVENESS_E2E_H
#define TEST_PLACEHOLDER_RESPONSIVENESS_E2E_H

#include <QObject>
#include <QRect>
#include <QSize>
#include <QVector>

class MainWindow;

class TestPlaceholderResponsivenessE2E : public QObject
{
    Q_OBJECT

private slots:
    void placeholdersRemainConsistentAcrossResolutions();
    void placeholdersFormUniformGridAcrossResolutions();
    void minimumSizeConstraintHoldsAcrossResolutions();

private:
    struct Snapshot {
        QSize windowSize;
        QVector<QRect> buttonRects;
    };

    Snapshot captureSnapshot(MainWindow &window, int width, int height);
    void resizeAndProcess(MainWindow &window, int width, int height);
};

#endif
