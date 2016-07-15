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
         * @param key is the key or name of the argument whose value you are looking for.
         * @return Returns the value of an argument or an invalid QVariant if the argument does not exist.
         */
        QVariant operator[](const QString key) const;

        /**
         * @brief build is a static helper method to easily access a builder of CommandLineInterface objects.
         * @return Returns a pointer to a builder.
         * @warning The pointer is yours.
         */
        static CommandLineInterfaceBuilder build();

    protected:
        explicit CommandLineInterface(const QString applicationName, QStringList arguments, QStringList acceptedArgumentPrefixes);
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

    private:
        QString m_applicationName;
        QString m_version;
        QString m_description;
        QMap<QString, Argument*> m_arguments;
        QStringList m_inputArguments;
        QStringList m_acceptedArgumentPrefixs;
        static const QString VERSIONARGUMENT;
    };
}

#endif // COMMANDLINEINTERFACE_HPP
