unix:!android {
    isEmpty(target.path) {
        qnx {
            target.path = /tmp/$${TARGET}/bin
        } else {
#            target.path = /opt/$${TARGET}/bin
            target.path = /home/root
        }
        export(target.path)
    }
    INSTALLS += target
}

export(INSTALLS)

