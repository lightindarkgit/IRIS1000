#ifndef IRISMANAGER_GLOBAL_H
#define IRISMANAGER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(IRISMANAGER_LIBRARY)
#  define IRISMANAGERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define IRISMANAGERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // IRISMANAGER_GLOBAL_H
