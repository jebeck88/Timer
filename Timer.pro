TEMPLATE = app
TARGET = Timer

QT += core gui widgets
CONFIG += link_prl

# software folder
SOFTWARE = .

# build folder
CONFIG(debug, debug|release) {
    BUILD_DIR = $$SOFTWARE/build/debug
}
CONFIG(release, debug|release) {
    BUILD_DIR = $$SOFTWARE/build/release
}

# Dependent project folders
BIN_DIR = $$BUILD_DIR/bin
LIB_DIR = $$BUILD_DIR/lib
OBJECTS_DIR = $$BUILD_DIR/obj/$$TARGET
MOC_DIR = $$OBJECTS_DIR/.moc
RCC_DIR = $$OBJECTS_DIR/.rcc
UI_DIR = $$OBJECTS_DIR/.ui
PRECOMPILED_DIR = $$OBJECTS_DIR/.pch

# Set the dest dir
DESTDIR = $$BIN_DIR

# Set the path for dependent libraries
LIBS += -L$$LIB_DIR

# Include files
include(Timer.pri)

# Include resources
RESOURCES += $$SOFTWARE/Timer.qrc 

# Copy dependent QT DLLs to output folder
DEPLOY_ARGS = --no-translations --no-system-d3d-compiler --no-quick-import --no-webkit2 --no-compiler-runtime --no-angle $$DESTDIR
QMAKE_POST_LINK = $$shell_quote($$[QT_INSTALL_DATA]/bin/windeployqt.exe) $$DEPLOY_ARGS