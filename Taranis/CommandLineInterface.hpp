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
        ~CommandLineInterface() {}

        QString name() const;
        QString version() const;
        QString description() const;
        void process() const;

        CommandLineInterface& WithVersion(const QString& version );
        CommandLineInterface &WithDescription(const QString& description );

    protected:
        QString helpMessage() const;

    private:
        QString m_applicationName;
        QString m_version;
        QString m_description;
        QList<QString> m_acceptedArgumentPrefixs;
    };
}

#endif // COMMANDLINEINTERFACE_HPP
