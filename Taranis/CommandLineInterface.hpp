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
#include <functional>
#include "Argument.hpp"

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
        friend class UnitTest::TaranisTestSuite;
    public:
        CommandLineInterface();
        explicit CommandLineInterface(const QString applicationName);
        explicit CommandLineInterface(const QString applicationName, const QString version);
        explicit CommandLineInterface(const QString applicationName, const QString version, QStringList arguments);
        virtual ~CommandLineInterface();

        QString name() const;
        QString version() const;
        QString description() const;

        CommandLineInterface& WithVersion(const QString& version );
        CommandLineInterface& WithDescription(const QString& description );
        CommandLineInterface& WithFlag( const QString& flag, const QString& description );
        CommandLineInterface& WithFlag( const QString& flag, const QString& description, std::function<void(QVariant)> action );
        CommandLineInterface& WithValue( const QString& name, const QString& description );
        CommandLineInterface& WithValue( const QString& name, const QString& description, std::function<void(QVariant)> action );
        CommandLineInterface& WithAction( const QString& name, const QString& description, std::function<void(QVariant)> action );

        virtual CommandLineInterface& process();

        QVariant operator[](const QString key) const;

    protected:
        virtual QString helpMessage() const;
        virtual void doHelpAction() const;
        virtual void doVersionAction() const;
        virtual QString generateTitle() const;
        void addArgument( Argument* arg );

        QStringList m_acceptedArgumentPrefixs;

    private:
        QString m_applicationName;
        QString m_version;
        QString m_description;
        QMap<QString, Argument*> m_arguments;
        QStringList m_inputArguments;
        static const QString VERSIONARGUMENT;
        CommandLineInterface& WithHelp();
    };
}

#endif // COMMANDLINEINTERFACE_HPP
