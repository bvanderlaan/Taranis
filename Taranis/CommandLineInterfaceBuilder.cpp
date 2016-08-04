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
#include "CommandLineInterfaceBuilder.hpp"
#include "CommandLineInterface.hpp"
#include "InputArgument.hpp"
#include "Argument.hpp"
#include "TaranisExceptions.hpp"

using namespace Taranis;
using namespace Taranis::Internal;
using namespace Taranis::Exceptions;
using action_callback = std::function<void(QVariant)>;

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::CommandLineInterfaceBuilder()
    : CommandLineInterfaceBuilder( "", QCoreApplication::arguments() )
{
    if ( qApp == nullptr )
    {
        throw QApplicationDoesNotExsistException();
    }
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::CommandLineInterfaceBuilder(CommandLineInterfaceBuilder &other)
{
    *m_cli = *(other.m_cli);
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::CommandLineInterfaceBuilder(CommandLineInterfaceBuilder &&other)
{
    m_cli = other.m_cli;
    other.m_cli = nullptr;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::~CommandLineInterfaceBuilder()
{
    delete m_cli;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::CommandLineInterfaceBuilder(const QString applicationName, QStringList arguments)
{
     QStringList acceptedArgumentPrefixs = getAcceptedArgumentPrefixes();
     m_cli = new CommandLineInterface(applicationName, arguments, acceptedArgumentPrefixs);
}

////////////////////////////////////////////////////////////////////////////////////////////////
QStringList CommandLineInterfaceBuilder::getAcceptedArgumentPrefixes()
{
    QStringList acceptedArgumentPrefixs( { QStringLiteral("-"), QStringLiteral("--") } );
     if ( QDir::separator() != QChar('/') )
     {
         acceptedArgumentPrefixs.append( QStringLiteral("/") );
     }

    return acceptedArgumentPrefixs;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder::operator CommandLineInterface() const
{
    return getCommandLineInterface();
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface CommandLineInterfaceBuilder::getCommandLineInterface() const
{
    m_cli->process();
    return *m_cli;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::operator=(CommandLineInterfaceBuilder &&other)
{
    if ( this != &other )
    {
        delete this->m_cli;
        this->m_cli = other.m_cli;
        other.m_cli = nullptr;
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::operator=(CommandLineInterfaceBuilder &other)
{
    if ( this != &other )
    {
        delete this->m_cli;
        *(this->m_cli) = *(other.m_cli);
    }
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithName(const QString &name)
{
    m_cli->setName( name );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder& CommandLineInterfaceBuilder::WithVersion(const QString &version)
{
    action_callback versionCallback = std::bind( &CommandLineInterface::doVersionAction, m_cli );
    return WithVersion( version, versionCallback );
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithVersion(const QString &version, std::function<void (QVariant)> action)
{
    m_cli->setVersion( version );
    m_cli->addArgument( new Argument( CommandLineInterface::VERSIONARGUMENT, "Display version information and exit", ArgumentType::Action, action) );

    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithDescription(const QString &description)
{
    m_cli->setDescription( description );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithFlag(const QString &flag, const QString &description)
{
    m_cli->addArgument( new Argument( flag, description, ArgumentType::Boolean, [this, flag](QVariant){
        m_cli->setValue(flag, true);
    }));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithFlag(const QString &flag, const QString &description, action_callback action)
{
    m_cli->addArgument( new Argument( flag, description, ArgumentType::Boolean, action) );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithValue(const QString &name, const QString &description)
{
    m_cli->addArgument( new Argument( name, description, ArgumentType::String, [this, name](QVariant value){
        m_cli->setValue(name, value);
    }));
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithValue(const QString &name, const QString &defaultValue, const QString &description)
{
    auto arg = new Argument( name, description, ArgumentType::String, [this, name](QVariant value){
        m_cli->setValue(name, value);
    });

    arg->setValue( defaultValue );
    m_cli->addArgument( arg );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithValue(const QString &name, const QString &defaultValue, const QString &description, std::function<void (QVariant)> action)
{
    auto arg = new Argument( name, description, ArgumentType::String, action);

    arg->setValue( defaultValue );
    m_cli->addArgument( arg );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithValue(const QString &name, const QString &description, action_callback action)
{
    m_cli->addArgument( new Argument( name, description, ArgumentType::String, action) );
    return *this;
}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterfaceBuilder &CommandLineInterfaceBuilder::WithAction(const QString &name, const QString &description, action_callback action)
{
   m_cli->addArgument( new Argument( name, description, ArgumentType::Action, action) );
    return *this;
}
