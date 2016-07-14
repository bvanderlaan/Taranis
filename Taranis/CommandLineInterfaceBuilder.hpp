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
    class Argument;
    class CommandLineInterface;

    /**
     * @brief The CommandLineInterfaceBuilder class represents a command line interface.
     * Your application will accept command line arguments which are defined in the CommandLineInterfaceBuilder object.
     */
    class CommandLineInterfaceBuilder
    {
        friend class UnitTest::TaranisTestSuite;
    public:
        CommandLineInterfaceBuilder();
        virtual ~CommandLineInterfaceBuilder() {}

        CommandLineInterfaceBuilder& WithName(const QString& name );
        CommandLineInterfaceBuilder& WithVersion(const QString& version );
        CommandLineInterfaceBuilder& WithDescription(const QString& description );
        CommandLineInterfaceBuilder& WithFlag( const QString& flag, const QString& description );
        CommandLineInterfaceBuilder& WithFlag( const QString& flag, const QString& description, std::function<void(QVariant)> action );
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& description );
        CommandLineInterfaceBuilder& WithValue( const QString& name, const QString& description, std::function<void(QVariant)> action );
        CommandLineInterfaceBuilder& WithAction( const QString& name, const QString& description, std::function<void(QVariant)> action );

        operator CommandLineInterface*() const;
        operator CommandLineInterface() const;

        CommandLineInterface getCommandLineInterface() const;

    protected:
        explicit CommandLineInterfaceBuilder(const QString applicationName, const QString version, QStringList arguments);
        virtual QStringList getAcceptedArgumentPrefixes();

    private:
        CommandLineInterface* m_cli;
    };
}

#endif // COMMANDLINEINTERFACEBUILDER_HPP
