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
#include <QDir>
#include "CommandLineInterface.hpp"
#include "InputArgument.hpp"

using namespace Taranis;
using action_callback = std::function<void()>;
Q_DECLARE_METATYPE(action_callback)

const QString CommandLineInterface::VERSIONARGUMENT = "version";

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
    : CommandLineInterface( applicationName, version, QCoreApplication::arguments() )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface(const QString applicationName, const QString version, QStringList arguments)
    : m_acceptedArgumentPrefixs( { QStringLiteral("-"), QStringLiteral("--") } ),
      m_applicationName(applicationName),
      m_inputArguments( arguments )
{
    if ( QDir::separator() != QChar('/') )
    {
        m_acceptedArgumentPrefixs.append( QStringLiteral("/") );
    }

    WithVersion( version );
    WithHelp();
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::~CommandLineInterface()
{
//    qDeleteAll( m_arguments );
    m_arguments.clear();
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface& CommandLineInterface::WithVersion(const QString &version)
{
    m_version = version;
    if ( m_version.isEmpty() )
    {
        delete m_arguments.value(VERSIONARGUMENT);
        m_arguments.remove(VERSIONARGUMENT);
    }
    else
    {
        action_callback versionCallback = std::bind( &CommandLineInterface::doVersionAction, this );
        WithAction(VERSIONARGUMENT, "Display version information and exit", versionCallback);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithHelp()
{
    action_callback helpCallback = std::bind( &CommandLineInterface::doHelpAction, this );
    WithAction("help", "Display this help and exit", helpCallback);
    WithAction("?", "Display this help and exit", helpCallback);
    return *this;
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
CommandLineInterface& CommandLineInterface::process()
{
    foreach( QString a, m_inputArguments )
    {
        InputArgument arg( a, m_acceptedArgumentPrefixs );
        if ( arg.isValid() )
        {
            QString key = arg.argument().toLower();
            if ( m_arguments.contains( key ) )
            {
                m_arguments[key]->callback()();
            }
        }
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QVariant CommandLineInterface::operator[](const QString key) const
{
    if ( m_arguments.contains(key) )
    {
        return m_arguments[key]->value();
    }
    else
    {
        return QVariant();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithDescription(const QString &description)
{
    m_description = description;
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithFlag(const QString &flag, const QString &description)
{
    addArgument( new Argument( flag, description, ArgumentType::Boolean, [this, flag](){
        m_arguments[flag]->setValue(true);
    }));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithFlag(const QString &flag, const QString &description, std::function<void ()> action)
{
    addArgument( new Argument( flag, description, ArgumentType::Boolean, action) );
    return *this;
}


////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface &CommandLineInterface::WithAction(const QString &name, const QString &description, std::function<void ()> action)
{
    addArgument( new Argument( name, description, ArgumentType::Action, action) );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::addArgument(Argument* arg)
{
    m_arguments[arg->name()] = arg;
    if ( arg->hasShortName() )
    {
        m_arguments[arg->shortName()] = arg;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::helpMessage() const
{
    QString applicationExecutable = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();
    QString message = generateTitle();

    if ( !message.isEmpty() )
    {
        message += QString(message.length()-1, '=') + QStringLiteral("\n");
    }

    if ( !m_description.isEmpty() )
    {
        message += m_description + QStringLiteral("\n\n");
    }

    message += QString("Usage: %1 [OPTION]\n\n").arg(applicationExecutable);

    QStringList filterArgumentAliases;
    foreach( Argument* arg, m_arguments.values() )
    {
        if ( filterArgumentAliases.contains( arg->name() ) ) continue;
        if ( arg->hasShortName() )
        {
            message += QString( "  -%1, --%2").arg(arg->shortName()).arg(arg->name());
        }
        else
        {
            message += QString( "  -%1").arg(arg->name());
        }

        message += QString("\t%1\n").arg(arg->description());
        filterArgumentAliases.append( arg->name());
    }
    return message;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::generateTitle() const
{
    QString message;
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

    return message;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::doHelpAction() const
{
    printf( helpMessage().toLatin1().data() );
    QCoreApplication::exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::doVersionAction() const
{
    printf( generateTitle().toLatin1().data() );
    QCoreApplication::exit(0);
}
