#include "mainwindow.hpp"

#include <qcontainerfwd.h>

#include <QGridLayout>

MainWindow::MainWindow( QWidget* parent ) : QMainWindow( parent ) {
    // 设置窗口标题和大小
    setWindowTitle( "简易计算器" );
    setFixedSize( 300, 400 );

    // 创建主部件和布局
    auto* centralWidget = new QWidget( this );
    setCentralWidget( centralWidget );
    auto* layout = new QGridLayout( centralWidget );

    // 创建显示区域
    display = new QLineEdit();
    display->setReadOnly( true );
    display->setAlignment( Qt::AlignRight );
    display->setMaxLength( 15 );

    QFont font = display->font();
    font.setPointSize( 20 );
    display->setFont( font );

    layout->addWidget( display, 0, 0, 1, 4 );

    // 创建按钮
    QStringList buttonLabels = { "sin", "cos", "sqrt", "^", "7", "8", "9", "/", "4", "5",
                                 "6",   "*",   "1", "2",  "3", "-", "0", "C", "=", "+" };

    // 添加按钮到布局
    for ( int i = 0; i < buttonLabels.size(); ++i ) {
        int row = i / 4 + 1;
        int col = i % 4;

        auto* button = new QPushButton( buttonLabels[ i ] );
        button->setFixedSize( 60, 60 );
        font.setPointSize( 16 );
        button->setFont( font );

        layout->addWidget( button, row, col );

        // 连接按钮点击信号到槽函数
        connect( button, &QPushButton::clicked, this, &MainWindow::onButtonClicked );
    }
}

MainWindow::~MainWindow() = default;

void MainWindow::onButtonClicked() {
    auto* button = qobject_cast< QPushButton* >( sender() );
    if ( !button )
        return;

    QString buttonText  = button->text();
    QString displayText = display->text();

    if ( buttonText == "C" ) {
        display->clear();
    }
    else if ( buttonText == "=" ) {
        // 这里可以添加计算逻辑
        // 目前只是简单显示
        display->setText( displayText + " = " );
    }
    else {
        display->setText( displayText + buttonText );
    }
}
