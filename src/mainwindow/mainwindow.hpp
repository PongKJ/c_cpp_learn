#pragma once

#include <QLineEdit>
#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow( QWidget* parent = nullptr );
    ~MainWindow() override;

private:
    QLineEdit* display;

private slots:
    void onButtonClicked();
};
