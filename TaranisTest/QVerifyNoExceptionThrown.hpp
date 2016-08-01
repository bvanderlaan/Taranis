/**
 * The MIT License (MIT)
 *

 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

/**
 * The below code was based off of QVERIFY_EXCEPTION_THROWN from qtestcase.h
 */

#ifndef QVERIFYNOEXCEPTIONTHROWN_HPP
#define QVERIFYNOEXCEPTIONTHROWN_HPP

#ifndef QT_NO_EXCEPTIONS

#  define QVERIFY_NO_EXCEPTION_THROWN(expression) \
    do {\
        QT_TRY {\
            expression;\
            return;\
        } QT_CATCH (const std::exception &e) {\
            QByteArray msg = QByteArray() + "Expected no exception thrown but std::exception caught with message: " + e.what(); \
            QTest::qFail(msg.constData(), __FILE__, __LINE__);\
            return;\
        } QT_CATCH (...) {\
            QTest::qFail("Expected no exception thrown" \
                         " but unknown exception caught", __FILE__, __LINE__);\
            return;\
        }\
    } while (0)

#else // QT_NO_EXCEPTIONS

/*
 * The expression passed to the macro should not throw an exception and we can't
 * check it because Qt has been compiled without exception support. We can't
 * skip the expression because it may have side effects and must be executed.
 * So, users must use Qt with exception support enabled if they use exceptions
 * in their code.
 */
#  define QVERIFY_NO_EXCEPTION_THROWN(expression) \
    Q_STATIC_ASSERT_X(false, "Support of exceptions is disabled")

#endif // !QT_NO_EXCEPTIONS

#endif // QVERIFYNOEXCEPTIONTHROWN_HPP
