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
#ifndef COMMANDLINEINTERFACEBUILDER_HPP
#define COMMANDLINEINTERFACEBUILDER_HPP

#include <QVariant>
#include <QStringList>
#include <functional>

namespace Taranis
{
    namespace UnitTest
    {
        class TaranisTestSuite;
    }
    class CommandLineInterface;

    /**
     * @brief The CommandLineInterfaceBuilder class is used to construct a command line interface object.
     * You can specify what arguments your CLI object will process as well as optionally set a name,
     * version, and description of your application which will be displayed in the built in help text.
     *
     * @warning The QApplication object needs to exist before building a CommandLineInterface object. If
     * you try to build a CLI object before the QApplication object exists an exception will be thrown
     * alerting you of this fact.
     */
    class CommandLineInterfaceBuilder
    {
        friend class UnitTest::TaranisTestSuite;
    public:
        CommandLineInterfaceBuilder();
        CommandLineInterfaceBuilder(CommandLineInterfaceBuilder& other);
        CommandLineInterfaceBuilder(CommandLineInterfaceBuilder&& other);
        virtual ~CommandLineInterfaceBuilder();

        CommandLineInterfaceBuilder& operator=(CommandLineInterfaceBuilder& other);
        CommandLineInterfaceBuilder& operator=(CommandLineInterfaceBuilder&& other);
        operator CommandLineInterface() const;

        /**
         * @brief WithName allows you to specify the name of your application.
         * The Taranis CommandLineInterface will generate help text for you and
         * this method allows you to provide the name of your application which
         * will be used in said help text.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithName("My Cool App");
         * @endcode
         *
         * The above code would render the below help text.
         *
         * @code{.unparsed}
         * $ mycoolapp --help
         * My Cool App
         * ===========
         * Usage: mycoolapp [OPTION]
         *   -?         Display this help and exits.
         *   -h, --help Display this help and exits.
         * @endcode
         *
         * @param name is the name of your application.
         */
        CommandLineInterfaceBuilder& WithName(const QString& name );

        /**
         * @brief WithVersion allows you to specify the version of your application.
         * The Taranis CommandLineInterface will generate help text for you and
         * this method allows you to provide the version of your application which
         * will be used in said help text.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithName("My Cool App")
         *                                                         .WithVersion("1.2.3.4-rc1");
         * @endcode
         *
         * The above code would render the below help text.
         *
         * @code{.unparsed}
         * $ mycoolapp --help
         * My Cool App - Version 1.2.3.4-rc1
         * =================================
         * Usage: mycoolapp [OPTION]
         *   -?            Display this help and exits.
         *   -h, --help    Display this help and exits.
         *   -v, --version Display version information and exits.
         * @endcode
         *
         * This method also adds the built in <i>version</i> argument allowing users to query
         * the version of your application from the command line.
         *
         * @code{.unparsed}
         * $ mycoolapp --version
         * My Cool App - Version 1.2.3.4-rc1
         * @endcode
         *
         * @param version is the version of your application and can be any string.
         */
        CommandLineInterfaceBuilder& WithVersion(const QString& version );

        /**
         * @brief WithVersion allows you to specify the version of your application and what action to perform when the <i>version</i> argument is provided.
         * The Taranis CommandLineInterface will generate help text for you and
         * this method allows you to provide the version of your application which
         * will be used in said help text.
         *
         * @code{.cpp}
         *   QString version("1.2.3.4-rc1");
         *   CommandLineInterface cli = CommandLineInterface::build()
         *           .WithName("My Cool App")
         *           .WithVersion(version,
         *                  [&version](QVariant) {
         *                           printf( "%s", QString("Beta Release Version %1.").arg(version).toLatin1().data() );
         *                           exit(0);
         *                  });
         * @endcode
         *
         * The above code would render the below help text.
         *
         * @code{.unparsed}
         * $ mycoolapp --help
         * My Cool App - Version 1.2.3.4-rc1
         * =================================
         * Usage: mycoolapp [OPTION]
         *   -?            Display this help and exits.
         *   -h, --help    Display this help and exits.
         *   -v, --version Display version information and exits.
         * @endcode
         *
         * This method also adds the built in <i>version</i> argument allowing users to query
         * the version of your application from the command line.
         *
         * @code{.unparsed}
         * $ mycoolapp --version
         * Version 1.2.3.4-rc1
         * @endcode
         *
         * The intended use case of this method is to allow you to specify other actions when the user
         * queries for the version like show it in a dialog box vs. the terminal.
         *
         * @param version is the version of your application and can be any string.
         * @param action is the action handler you want performed if the version argument is present.
         */
        CommandLineInterfaceBuilder& WithVersion(const QString& version, std::function<void(QVariant)> action );

        /**
         * @brief WithDescription allows you to specify a description for your application.
         * The Taranis CommandLineInterface will generate help text for you and
         * this method allows you to provide an optional description of your application which
         * will be used in said help text.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithName("My Cool App")
         *                                                         .WithVersion("1.2.3.4-rc1")
         *                                                         .WithDescription("This application is really cool!");
         * @endcode
         *
         * The above code would render the below help text.
         *
         * @code{.unparsed}
         * $ mycoolapp --help
         * My Cool App - Version 1.2.3.4-rc1
         * =================================
         * This application is really cool!
         *
         * Usage: mycoolapp [OPTION]
         *   -?            Display this help and exits.
         *   -h, --help    Display this help and exits.
         *   -v, --version Display version information and exits.
         * @endcode
         *
         * @param description is a description of your application.
         */
        CommandLineInterfaceBuilder& WithDescription(const QString& description );

        /**
         * @return Returns the constructed CommandLineInterface object.
         */
        CommandLineInterface getCommandLineInterface() const;

        /**
         * @brief WithFlag will add a flag to your CLI.
         * You can access the flag value, which will be true if the user used the flag when starting
         * your application or false if not, by using the index operator with the flags name.
         *
         * @code{.cpp}
         * CommandLineInterface myCLI = CommandLineInterface::build().WithFlag("force", "Will force a refresh.");
         * if ( myCLI["force"] == true ) {...}
         * @endcode
         *
         * @param flag is the name of the argument, example 'force'. You will get a short name, i.e. 'f', automatically.
         * @param description is the description of this argument which will be displaied in the help.
         */
        CommandLineInterfaceBuilder& WithFlag( const QString& flag, const QString& description );

        /**
         * @brief WithFlag will add a flag to your CLI.
         * You can have a handler executed if the user starts your application with this flag.
         *
         * @code{.cpp}
         * CommandLineInterface myCLI = CommandLineInterface::build().WithFlag("force", "Will force a refresh.",
         *                                          [this](QVariant) {
         *                                                this->refresh();
         *                                          });
         * @endcode
         *
         * For flags the QVariant returned will be set to true all the time because this handler is _only_ executed
         * if the flag is present.
         *
         * @param flag is the name of the argument, example 'force'. You will get a short name, i.e. 'f', automatically.
         * @param description is the description of this argument which will be displaied in the help.
         * @param action is the action handler you want performed if the argument is present.
         */
        CommandLineInterfaceBuilder& WithFlag( const QString& flag, const QString& description, std::function<void(QVariant)> action );

        /**
         * @brief WithValue will add an agrument which expects a value to your CLI.
         * You can access the argument value by using the index operator with the arguments name.
         *
         * * @code{.cpp}
         * CommandLineInterface myCLI = CommandLineInterface::build().WithValue("address", "Sets the address of the device to communicate with.");
         * device->setAddress( myCLI["address"].toString() );
         * @endcode
         *
         * @param name is the name of the argument, example 'address'. You will get a short name, i.e. 'a', automatically.
         * @param description is the description of this argument which will be displaied in the help.
         */
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& description );

        /**
         * @brief WithValue will add an agrument which expects a value to your CLI.
         * You can have a handler executed if the user starts your application with this argument and have the value they provided passed in.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithValue("address", "Sets the address of the device to communicate with.",
         *                                          [&device](QVariant address) {
         *                                                device->setAddress( address.toString() );
         *                                          });
         * @endcode
         *
         * @param name is the name of the argument, example 'address'. You will get a short name, i.e. 'a', automatically.
         * @param description is the description of this argument which will be displaied in the help.
         * @param action is the action handler you want performed if the argument is present.
         */
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& description, std::function<void(QVariant)> action );

        /**
         * @brief WithValue will add an agrument which expects a value to your CLI.
         * You can access the argument value by using the index operator with the arguments name.
         *
         * * @code{.cpp}
         * CommandLineInterface myCLI = CommandLineInterface::build().WithValue("address", "127.0.0.1", "Sets the address of the device to communicate with.");
         * device->setAddress( myCLI["address"].toString() );
         * @endcode
         *
         * @param name is the name of the argument, example 'address'. You will get a short name, i.e. 'a', automatically.
         * @param defaultValue is the value to assign the argument if none is provided on the CLI.
         * @param description is the description of this argument which will be displaied in the help.
         */
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& defaultValue, const QString& description );

        /**
         * @brief WithValue will add an agrument which expects a value to your CLI.
         * You can have a handler executed if the user starts your application with this argument and have the value they provided passed in.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithValue("address", "127.0.0.1", "Sets the address of the device to communicate with.",
         *                                          [&device](QVariant address) {
         *                                                device->setAddress( address.toString() );
         *                                          });
         * @endcode
         *
         * @param name is the name of the argument, example 'address'. You will get a short name, i.e. 'a', automatically.
         * @param defaultValue is the value to assign the argument if none is provided on the CLI.
         * @param description is the description of this argument which will be displaied in the help.
         * @param action is the action handler you want performed if the argument is present.
         */
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& defaultValue, const QString& description, std::function<void(QVariant)> action );


        /**
         * @brief WithAction will add an argument which when present will trigger an action to be performed.
         * This works similar to flags as in the handler is only executed if the argument was provided when the application started
         * but conseptually this type of argument is not about values and more about initiating an action. For example the
         * 'version' argument is not about setting the version or turning on a version flag but rather about executing the display
         * version action so the user can see the version of your application on screen.
         *
         * No values will be stored for this argument type and an action handler is required to specify which action should be
         * executed when this argument is provided.
         *
         * @code{.cpp}
         * CommandLineInterface cli = CommandLineInterface::build().WithAction("restart", "Will restart the service.",
         *                                          [this](QVariant) {
         *                                                this->restart();
         *                                          });
         * @endcode
         *
         * @param name is the name of the argument, example 'restart'. You will get a short name , i.e. 'r', automatically.
         * @param description is the description of this argument which will be displaied in the help.
         * @param action is the action handler you want performed if the argument is present.
         */
        CommandLineInterfaceBuilder& WithAction( const QString& name, const QString& description, std::function<void(QVariant)> action );


    protected:
        explicit CommandLineInterfaceBuilder(const QString applicationName, QStringList arguments);
        /**
         * @brief getAcceptedArgumentPrefixes returns a list of argument prefixes, such as -, --, or /
         * @note Only arguments which have one of these prefixes will be parsed by the CLI.
         * @return Returns a list of argument prefixes that the CLI will accept.
         */
        virtual QStringList getAcceptedArgumentPrefixes();

    private:
        CommandLineInterface* m_cli;
    };
}

#endif // COMMANDLINEINTERFACEBUILDER_HPP
