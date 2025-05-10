#include <qwidget.h>
#define DBG_MACRO_NO_WARNING
#include <dbg.h>
#include <fmt/core.h>
#include <json/json.h>
#include <qapplication.h>
#include <spdlog/common.h>
#include <spdlog/spdlog.h>

#include <CLI/CLI.hpp>
#include <QWidget>
#include <internal_use_only/config.hpp>

#include "mainwindow.hpp"

int main( int argc, char* argv[] ) {
    QApplication app( argc, argv );
    MainWindow w;
    w.show();
    return QApplication::exec();
}
