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
#include <QCoreApplication>
#include <QFileInfo>
#include "CommandLineInterface.hpp"

using namespace Taranis;

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface() :
    CommandLineInterface(QStringLiteral(""))
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface(const QString applicationName)
    : CommandLineInterface(applicationName, QStringLiteral(""))
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface(const QString applicationName, const QString version)
    : m_applicationName(applicationName),
      m_version(version)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::name() const
{
    return m_applicationName;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::version() const
{
    return m_version;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::description() const
{
    return m_description;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::process() const
{
    foreach( QString arg, QCoreApplication::arguments() )
    {
        if ( arg.toLower() == "-h" )
        {
            printf( helpMessage().toLatin1().data() );
            QCoreApplication::exit(0);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface& CommandLineInterface::WithVersion(const QString &version)
{
    m_version = version;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithDescription(const QString &description)
{
    m_description = description;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::helpMessage() const
{
    QString message;
    QString applicationExecutable = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();

    if ( !m_applicationName.isEmpty() && !m_version.isEmpty() )
    {
        message += QString("%1 - Version %2\n").arg(m_applicationName).arg(m_version);
    }
    else if ( !m_applicationName.isEmpty() )
    {
        message += QString("%1\n").arg(m_applicationName);
    }
    else if ( !m_version.isEmpty() )
    {
        message += QString("Version %1\n").arg(m_version);
    }

    if ( !message.isEmpty() )
    {
        message += QString(message.length()-1, '=') + QStringLiteral("\n");
    }

    if ( !m_description.isEmpty() )
    {
        message += m_description + QStringLiteral("\n\n");
    }

    message += QString("Usage: %1 [OPTION]\n"
            "\n"
            "  -h, -?, --help\tDisplay this help and exit\n").arg(applicationExecutable);

    if ( !m_version.isEmpty() )
    {
        message += QStringLiteral("  -v, --version\tDisplay version information and exit\n");
    }

    return message;
}
