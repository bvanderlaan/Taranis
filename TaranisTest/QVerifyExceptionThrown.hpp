/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the QtTest module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL21$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see http://www.qt.io/terms-conditions. For further
** information use the contact form at http://www.qt.io/contact-us.
**
** GNU Lesser General Public License Usage
** Alternatively, this file may be used under the terms of the GNU Lesser
** General Public License version 2.1 or version 3 as published by the Free
** Software Foundation and appearing in the file LICENSE.LGPLv21 and
** LICENSE.LGPLv3 included in the packaging of this file. Please review the
** following information to ensure the GNU Lesser General Public License
** requirements will be met: https://www.gnu.org/licenses/lgpl.html and
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** As a special exception, The Qt Company gives you certain additional
** rights. These rights are described in The Qt Company LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** $QT_END_LICENSE$
**
****************************************************************************/

/**
 * This is lifted from qtestcase.h as of Qt 5.3
 * I'm using Ubuntu 14 (Trusty) on Travis-ci however it caps out at Qt 5.2.x
 * This macro was not added to Qt until 5.3 so in order to make it accessble for
 * my Travis builds I'm pulling it over since this is only used in my unit tests and
 * is only a macro.
 */
#ifndef QVERIFYEXCEPTIONTHROWN_HPP
#define QVERIFYEXCEPTIONTHROWN_HPP

#if QT_VERSION < QT_VERSION_CHECK(5, 3, 0)

#ifndef QT_NO_EXCEPTIONS

#  define QVERIFY_EXCEPTION_THROWN(expression, exceptiontype) \
    do {\
        QT_TRY {\
            QT_TRY {\
                expression;\
                QTest::qFail("Expected exception of type " #exceptiontype " to be thrown" \
                             " but no exception caught", __FILE__, __LINE__);\
                return;\
            } QT_CATCH (const exceptiontype &) {\
            }\
        } QT_CATCH (const std::exception &e) {\
            QByteArray msg = QByteArray() + "Expected exception of type " #exceptiontype \
                             " to be thrown but std::exception caught with message: " + e.what(); \
            QTest::qFail(msg.constData(), __FILE__, __LINE__);\
            return;\
        } QT_CATCH (...) {\
            QTest::qFail("Expected exception of type " #exceptiontype " to be thrown" \
                         " but unknown exception caught", __FILE__, __LINE__);\
            return;\
        }\
    } while (0)

#else // QT_NO_EXCEPTIONS

/*
 * The expression passed to the macro should throw an exception and we can't
 * catch it because Qt has been compiled without exception support. We can't
 * skip the expression because it may have side effects and must be executed.
 * So, users must use Qt with exception support enabled if they use exceptions
 * in their code.
 */
#  define QVERIFY_EXCEPTION_THROWN(expression, exceptiontype) \
    Q_STATIC_ASSERT_X(false, "Support of exceptions is disabled")

#endif // !QT_NO_EXCEPTIONS

#endif // QT VERSION CHECK

#endif // QVERIFYEXCEPTIONTHROWN_HPP
