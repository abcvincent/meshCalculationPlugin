TARGET = v_repExtMeshCalc
TEMPLATE = lib

DEFINES -= UNICODE
CONFIG += shared
CONFIG -= core
CONFIG -= gui

*-msvc* {
    QMAKE_CXXFLAGS += -O2
    QMAKE_CXXFLAGS += -W3
}
*-g++* {
    QMAKE_CXXFLAGS += -O3
    QMAKE_CXXFLAGS += -Wall
    QMAKE_CXXFLAGS += -Wno-unused-parameter
    QMAKE_CXXFLAGS += -Wno-strict-aliasing
    QMAKE_CXXFLAGS += -Wno-empty-body
    QMAKE_CXXFLAGS += -Wno-write-strings

    # Best would be to have a switch based on compiler version, but apparently that doesn't exist. So we use the Qt version..
    greaterThan(QT_MAJOR_VERSION,4): QMAKE_CXXFLAGS += -Wno-unused-but-set-variable
    greaterThan(QT_MAJOR_VERSION,4): QMAKE_CXXFLAGS += -Wno-unused-local-typedefs
    greaterThan(QT_MAJOR_VERSION,4): QMAKE_CXXFLAGS += -Wno-narrowing

    QMAKE_CFLAGS += -O3
    QMAKE_CFLAGS += -Wall
    QMAKE_CFLAGS += -Wno-strict-aliasing
    QMAKE_CFLAGS += -Wno-unused-parameter
    QMAKE_CFLAGS += -Wno-unused-but-set-variable
    QMAKE_CFLAGS += -Wno-unused-local-typedefs
}


win32 {
    DEFINES += WIN_VREP
}

macx {
    INCLUDEPATH += "/usr/local/include"
    DEFINES += MAC_VREP
}

unix:!macx {
    DEFINES += LIN_VREP
}

DEFINES += COMPILING_EXTERNAL_COLL_DIST_DLL
#DEFINES += QT_FRAMEWORK # when using this, make sure you use the exact same compiler and Qt version as the main V-REP library!

INCLUDEPATH += "sourceCode"
INCLUDEPATH += "sourceCode/collDistAlgos"
INCLUDEPATH += "../programming/v_repMath"
INCLUDEPATH += "../programming/include"
INCLUDEPATH += "../programming/common"

HEADERS += sourceCode/collDistAlgos/meshCalcConfig.h \
    sourceCode/collDistAlgos/collDistAlgos.h \
    sourceCode/collDistAlgos/collNode.h \
    sourceCode/collDistAlgos/collInfo.h \
    sourceCode/collDistAlgos/pointCloudInfo.h \
    sourceCode/collDistAlgos/pointCloudNode.h \
    sourceCode/collDistAlgos/octreeInfo.h \
    sourceCode/collDistAlgos/octreeNode.h \
    sourceCode/collDistAlgos/kdTreeInfo.h \
    sourceCode/collDistAlgos/kdTreeNode.h \
    sourceCode/collDistAlgos/linkedListElement.h \
    sourceCode/v_repExtMeshCalc.h \
    ../programming/include/v_repLib.h \
    ../programming/v_repMath/3Vector.h \
    ../programming/v_repMath/4Vector.h \
    ../programming/v_repMath/7Vector.h \
    ../programming/v_repMath/3X3Matrix.h \
    ../programming/v_repMath/4X4Matrix.h \
    ../programming/v_repMath/MyMath.h \

SOURCES += sourceCode/collDistAlgos/collDistAlgos.cpp \
    sourceCode/collDistAlgos/collNode.cpp \
    sourceCode/collDistAlgos/collInfo.cpp \
    sourceCode/collDistAlgos/pointCloudInfo.cpp \
    sourceCode/collDistAlgos/pointCloudNode.cpp \
    sourceCode/collDistAlgos/octreeInfo.cpp \
    sourceCode/collDistAlgos/octreeNode.cpp \
    sourceCode/collDistAlgos/kdTreeInfo.cpp \
    sourceCode/collDistAlgos/kdTreeNode.cpp \
    sourceCode/collDistAlgos/linkedListElement.cpp \
    sourceCode/v_repExtMeshCalc.cpp \
    ../programming/common/v_repLib.cpp \
    ../programming/v_repMath/3Vector.cpp \
    ../programming/v_repMath/4Vector.cpp \
    ../programming/v_repMath/7Vector.cpp \
    ../programming/v_repMath/3X3Matrix.cpp \
    ../programming/v_repMath/4X4Matrix.cpp \
    ../programming/v_repMath/MyMath.cpp \

unix:!symbian {
    maemo5 {
        target.path = /opt/usr/lib
    } else {
        target.path = /usr/lib
    }
    INSTALLS += target
}
