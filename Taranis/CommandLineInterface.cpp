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
#include <functional>
#include "CommandLineInterface.hpp"
#include "InputArgument.hpp"
#include "TaranisExceptions.hpp"

using namespace Taranis;
using action_callback = std::function<void(QVariant)>;

const QString CommandLineInterface::VERSIONARGUMENT = "version";
const QString CommandLineInterface::HELPARGUMENT = "help";

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface(const QString applicationName, QStringList arguments, QStringList acceptedArgumentPrefixes)
    : m_applicationName(applicationName),
      m_inputArguments( arguments ),
      m_acceptedArgumentPrefixs( acceptedArgumentPrefixes )
{
    addHelpArguments();
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::~CommandLineInterface()
{
//    qDeleteAll( m_arguments );
    m_arguments.clear();
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
QStringList CommandLineInterface::arguments() const
{
    return m_arguments.keys();
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface& CommandLineInterface::process()
{  
    int numOfArguments = m_inputArguments.count();
    for( int i = 0; i < numOfArguments; ++i )
    {
        InputArgument* arg = new InputArgument( m_inputArguments.at(i), m_acceptedArgumentPrefixs );
        if ( ( numOfArguments > 1 ) && (i < numOfArguments - 1 ) && arg->isValid() && !arg->hasValue() )
        {
            bool isNextArgumentValid = InputArgument( m_inputArguments.at(i+1), m_acceptedArgumentPrefixs ).isValid();
            if ( !isNextArgumentValid )
            {
                QString multiPartInput = QString("%1%2%3")
                                                .arg(m_inputArguments.at(i))
                                                .arg( arg->nameValueSeperator().isEmpty() ? ":" : "" )
                                                .arg(m_inputArguments.at(i+1));

                delete arg;
                arg = new InputArgument( multiPartInput , m_acceptedArgumentPrefixs );
                ++i;
            }
        }

        if ( arg->isValid() )
        {
            QString key = normilizeKey( arg->name() );
            if ( m_arguments.contains( key ) )
            {
                m_arguments[key]->callback()(arg->value());
            }
        }
        delete arg;
    }

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::normilizeKey(const QString &key) const
{
    return key.toLower();
}

////////////////////////////////////////////////////////////////////////////////////////////////
QVariant CommandLineInterface::operator[](const QString key) const
{
    QString normilizedKey = normilizeKey( key );
    if ( m_arguments.contains(normilizedKey) )
    {
        return m_arguments[normilizedKey]->value();
    }
    else
    {
        return QVariant();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder CommandLineInterface::build()
{
    return CommandLineInterfaceBuilder();
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::addArgument(Argument* arg)
{
    validateArgumentName(*arg);
    m_arguments[normilizeKey( arg->name() )] = arg;

    if ( arg->hasShortName() )
    {
        validateArgumentShortName(*arg);
        m_arguments[normilizeKey( arg->shortName() )] = arg;
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::validateArgumentName(const Argument& arg) const
{
    QString normilizedName = normilizeKey( arg.name() );
    if ( m_arguments.contains( normilizedName ) )
    {
        if ( normilizedName == VERSIONARGUMENT )
        {
            // Ok to override
            qWarning("The built in version argument is being overriden");
        }
        else if (( normilizedName == HELPARGUMENT ) || ( normilizedName == "?" ))
        {
            // Ok to overide
            qWarning("The built in help argument is being overriden");
        }
        else
        {
            throw ArgumentRedefinitionException(arg.name());
        }
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::validateArgumentShortName(const Argument &arg) const
{
    QString normalizedName = normilizeKey( arg.name() );
    if ( normalizedName == HELPARGUMENT ) return;
    if ( normalizedName == VERSIONARGUMENT ) return;

    QString normilizedShortName = normilizeKey( arg.shortName() );
    if ( m_arguments.contains( normilizedShortName ) )
    {
        if ( ( normilizedShortName == VERSIONARGUMENT.at(0) ) && m_arguments.contains(VERSIONARGUMENT) )
        {
            throw VersionShortNameCollisionException( arg.name() );
        }
        else if (( normilizedShortName == HELPARGUMENT.at(0) ) || ( normilizedShortName == "?" ))
        {
            throw HelpShortNameCollisionException( arg.name() );
        }
        else
        {
            throw ShortNameCollisionException(arg.name(), m_arguments[normilizedShortName]->name());
        }
    }
}


////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::setVersion(const QString version)
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
        addArgument( new Argument( VERSIONARGUMENT, "Display version information and exit", ArgumentType::Action, versionCallback) );
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::setName(const QString name)
{
    m_applicationName = name;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::setDescription(const QString description)
{
    m_description = description;
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::addHelpArguments()
{
    action_callback helpCallback = std::bind( &CommandLineInterface::doHelpAction, this );
    addArgument( new Argument( HELPARGUMENT, "Display this help and exit", ArgumentType::Action, helpCallback) );
    addArgument( new Argument( "?", "Display this help and exit", ArgumentType::Action, helpCallback) );
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::setValue(const QString key, const QVariant value)
{
    QString normilizedKey = normilizeKey( key );
    if ( m_arguments.contains(normilizedKey) )
    {
        m_arguments[normilizedKey]->setValue(value);
    }
    else
    {
        Q_ASSERT_X( false, "CommandLineInterface::setValue", QString("No argument with name %1").arg(key).toLatin1().data() );
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
    printf( "%s", helpMessage().toLatin1().data() );
    exit(0);
}

////////////////////////////////////////////////////////////////////////////////////////////////
void CommandLineInterface::doVersionAction() const
{
    printf( "%s", generateTitle().toLatin1().data() );
    exit(0);
}
