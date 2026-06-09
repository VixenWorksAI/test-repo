#ifndef TEST_PLACEHOLDER_RESPONSIVENESS_INTEGRATION_H
#define TEST_PLACEHOLDER_RESPONSIVENESS_INTEGRATION_H

#include <QObject>

class TestPlaceholderResponsivenessIntegration : public QObject
{
    Q_OBJECT

private slots:
    void windowHasUsableMinimumSize();
    void buttonsStayAboveMinimumAtTinyWindowSize();
    void buttonsRemainVisibleAtVeryLargeWindowSize();
    void allPlaceholdersRemainInsideCentralWidget();

private:
    void resizeAndProcess(class MainWindow &window, int width, int height);
};

#endif
