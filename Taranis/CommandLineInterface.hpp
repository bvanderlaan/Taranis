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
#ifndef COMMANDLINEINTERFACE_HPP
#define COMMANDLINEINTERFACE_HPP

#include <QObject>
#include <QMap>
#include <QVariant>
#include <QStringList>
#include "Argument.hpp"
#include "CommandLineInterfaceBuilder.hpp"

namespace Taranis
{
    namespace UnitTest
    {
        class TaranisTestSuite;
    }

    /**
     * @brief The CommandLineInterface class represents a command line interface.
     * Your application will accept command line arguments which are defined in the CommandLineInterface object.
     */
    class CommandLineInterface
    {
        friend class CommandLineInterfaceBuilder;
        friend class UnitTest::TaranisTestSuite;
    public:
        CommandLineInterface() = delete;
        virtual ~CommandLineInterface();

        QString name() const;
        QString version() const;
        QString description() const;
        QStringList arguments() const;

        /**
         * @brief You can use the index operator to access argument values.
         * @param key is the key or name of the argument whose value you are looking for. This look up is case insensitive.
         * @return Returns the value of an argument or an invalid QVariant if the argument does not exist.
         */
        QVariant operator[](const QString key) const;

        /**
         * @brief build is a static helper method to easily access a builder of CommandLineInterface objects.
         * @return Returns a command line interface builder.
         */
        static CommandLineInterfaceBuilder build();

    protected:
        explicit CommandLineInterface(const QString applicationName, QStringList arguments, QStringList acceptedArgumentPrefixes);

        /**
         * @brief process will read the input arguments and parse them into Argument objects then execute their callbacks.
         */
        virtual CommandLineInterface& process();

        virtual QString helpMessage() const;
        virtual void doHelpAction() const;
        virtual void doVersionAction() const;
        virtual QString generateTitle() const;
        void addArgument( Argument* arg );
        void setVersion( const QString version );
        void setName( const QString name );
        void setDescription( const QString description );
        void addHelpArguments();
        void setValue( const QString key, const QVariant value );
        virtual QString normilizeKey( const QString& key ) const;

    private:
        QString m_applicationName;
        QString m_version;
        QString m_description;
        QMap<QString, Argument*> m_arguments;
        QStringList m_inputArguments;
        QStringList m_acceptedArgumentPrefixs;
        static const QString VERSIONARGUMENT;
    };

    /**
     * @example main.example1.cpp
     * This example shows how to construct a CommandLineInterface object using the static CommandLineInterface::build() method
     * and the CommandLineInterfaceBuilder's fluent interface. Next it shows you how to read the value of the flag from the
     * constructed object.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */
    /**
     * @example main.example2.cpp
     * This example shows how to construct a CommandLineInterface object using the static CommandLineInterface::build() method
     * and the CommandLineInterfaceBuilder's fluent interface. Next it shows how to provide a call back which would be executed
     * if the user provided in this case the mouse flag.
     *
     * In this example you see that there is no need to hold onto the CommandLineInterface object as the call backs
     * are called automatically after construction.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */
    /**
     * @example main.example3.cpp
     * This example shows how to construct a CommandLineInterface object using the static CommandLineInterface::build() method
     * and the CommandLineInterfaceBuilder's fluent interface. Next it shows how to requeste the constructed CommandLineInterface
     * object from the builder. Finally it shows how to access the values the user inputed on the command line.
     *
     * @see main.example1.cpp for a one line way of doing the same thing.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */

    /**
     * @example main.example4.cpp
     * This example shows how to construct a CommandLineInterface object using the static CommandLineInterface::build() method
     * then define a command line interface using the <i>With</i> methods in a traditional way. Finally it then shows how
     * to requeste the CommandLineInterface object from the builder before showing how to access the values the user inputed
     * on the command line.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */
    /**
     * @example main.example5.cpp
     * This example shows how to construct a CommandLineInterfaceBuilder object then how to use it to constructe a
     * CommandLineInterface object using the <i>With</i> methods. Next it show show to request the CommandLineInterface
     * object from the builder before showing how to access the values the user inputed on the command line.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */
    /**
     * @example main.example6.cpp
     * This example shows how to construct a CommandLineInterfaceBuilder object then how to use it to constructe a
     * CommandLineInterface object using the <i>With</i> methods. Next it show show to request the CommandLineInterface
     * object from the builder before showing how to access the values the user inputed on the command line.
     *
     * If you run this example when the user provides the mouse flag such as -mouse, --mouse, -m, /m, /mouse
     * You see see the output <i>Show Mouse? Yes</i> otherwise you'll see <i>Show Mouse? No</i>.
     */
    /**
     * @example main.example7.cpp
     * This example shows how to define a command line interface which contains an argument which accepts values.
     *
     * If you run this example when the user provides the server argument such as --server 1.2.3.4, --server=1.2.3.4,
     * --server:1.2.3.4, --server= 1.2.3.4, or --server: 1.2.3.4 you will see the output <i>Server IP: 1.2.3.4</i>.
     */
    /**
     * @example main.example8.cpp
     * This example shows how to define a command line interface which contains an argument which accepts values and
     * contain a default value.
     *
     * If you have an optional argument which allows the user to input a value you can set a default value for said
     * argument so that you don't have to check if the user inputted it. Just use the value given to you by the
     * CommandLineInterface argument and if the user provided the argument then you'll get the user defined value
     * and if not you'll get your default value.
     *
     * If you run this example when the user provides the server argument such as --server 1.2.3.4, --server=1.2.3.4,
     * --server:1.2.3.4, --server= 1.2.3.4, or --server: 1.2.3.4 you will see the output <i>Server IP: 1.2.3.4</i> otherwise
     * you'll get <i>Server IP: 127.0.0.1</i> with is the default IP provided in the <i>WithValue</i> method.
     */
}

#endif // COMMANDLINEINTERFACE_HPP
