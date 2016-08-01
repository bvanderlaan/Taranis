/**
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Brad van der Laan
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
#ifndef TARANISEXCEPTIONS_HPP
#define TARANISEXCEPTIONS_HPP

#include <QtGlobal>
#include <QString>
#include <exception>

namespace Taranis
{
    /**
     * @brief The TaranisException class is the base general exception class.
     */
    class TaranisException : public std::exception
    {
    public:
        TaranisException( const QString& message );
        virtual ~TaranisException() throw() {}
        const char *what() const throw() Q_DECL_OVERRIDE;

    private:
        QString m_message;
    };

    /**
     * @brief The QApplicationDoesNotExsistException class defines an exception which is thrown if the CommandLineInterface object is created without a QApplication object.
     * If you build the CommandLineInterface object before Instantiating a QApplication object then the CLI won't have access to the command line arguments and thus won't
     * work. This exception will be thrown to alert you of this fact as quickly as possible.
     *
     * @code{.cpp}
     * using namespace Taranis;
     *  int main(int argc, char *argv[])
     *  {
     *      CommandLineInterface::build()
     *                          .WithName("My Cool App")
     *                          .WithVersion("1.2.3.4-abc")
     *                          .WithFlag("mouse", "Force mouse to be displayed in release build.");
     *
     *      QCoreApplication a(argc, argv);
     *      return a.exec();
     *  }
     * @endcode
     *
     * The above will result in this exception being thrown. Instantiate QCoreApplicaiton <i>before</i> building the CLI object.
     */
    class QApplicationDoesNotExsistException : public TaranisException
    {
    public:
        QApplicationDoesNotExsistException();
        virtual ~QApplicationDoesNotExsistException() throw() {}
    };

    /**
     * @brief The ShortNameCollisionException class is an exception which occures when two arguments have the same short name.
     * So if the user defines a CLI with two arguments which both have the same starting character this exception will be thrown
     * because both arguments will have the same short name.
     *
     * @code{.cpp}
     * CommandLineInterface::build()
     *              .WithValue("server", "Set the server ip address.")
     *              .WithValue("serial", "Set the serial number.");
     * @endcode
     *
     * The above would generate this exception becuase both arguments would want to use
     * the same short name <b>-s</b>.
     *
     * @param newArgName is the name of the argument being added which collides with a pre-existing argument.
     * @param existingArgName is the name of the argument which already exists that is being collided with.
     *
     */
    class ShortNameCollisionException : public TaranisException
    {
    public:
        ShortNameCollisionException(const QString& newArgName, const QString& existingArgName);
        ShortNameCollisionException(const QString& message);
        virtual ~ShortNameCollisionException() throw() {}
    };

    /**
     * @brief The ArgumentRedefinitionException class is an exception which occures when two arguments have the same name.
     * So if the user defines a CLI with two arguments which both have the same name this exception will be thrown.
     *
     * @code{.cpp}
     * CommandLineInterface::build()
     *              .WithValue("server", "Set the server ip address.")
     *              .WithValue("server", "Set the server name.");
     * @endcode
     *
     * The above would generate this exception becuase both arguments have the same name.
     *
     * @param argName is the name of the argument which has been declared more then once.
     */
    class ArgumentRedefinitionException : public TaranisException
    {
    public:
        ArgumentRedefinitionException(const QString& argName);
        virtual ~ArgumentRedefinitionException() throw() {}
    };

    /**
     * @brief The HelpShortNameCollisionException class is an exception which occures when an argument is defined which will collide with the help short name.
     *
     * @code{.cpp}
     * CommandLineInterface::build()
     *              .WithValue("here", "Canada", "Set current location.");
     * @endcode
     *
     * The above would generate this exception becuase the short name for <i>here</i> is
     * <i>h</i> which collides with the short name for the built in <i>help</i> argument.
     *
     * @param argumentName is the name of the argument whose short name collides with the build in <i>help</i> argument.
     */
    class HelpShortNameCollisionException : public ShortNameCollisionException
    {
    public:
        HelpShortNameCollisionException(const QString& argumentName);
        virtual ~HelpShortNameCollisionException() throw() {}
    };

    /**
     * @brief The VersionShortNameCollisionException class is an exception which occures when an argument is defined which will collide with the version short name.
     *
     * @code{.cpp}
     * CommandLineInterface::build()
     *              .WithVersion("1.2.3.4-abc")
     *              .WithFlag("verbose", "Enables verbose logging.");
     * @endcode
     *
     * The above would generate this exception becuase the short name for <i>verbose</i> is
     * <i>v</i> which collides with the short name for the built in <i>version</i> argument.
     * @note This exception is only thrown if the version argument exists. If the user does
     * not provide a version then no collision will occure therefore no exception will be thrown.
     *
     * @param argName is the name of the argument whose short name collides with the build in <i>version</i> argument.
     */
    class VersionShortNameCollisionException : public ShortNameCollisionException
    {
    public:
        VersionShortNameCollisionException(const QString& argName);
        virtual ~VersionShortNameCollisionException() throw() {}

    };

}

#endif // TARANISEXCEPTIONS_HPP
