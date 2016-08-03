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

#include "TaranisExceptions.hpp"

using namespace Taranis;

////////////////////////////////////////////////////////////////////////////////////////////////
TaranisException::TaranisException(const QString &message) :
  std::exception(),
  m_message( message )
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
const char *TaranisException::what() const throw()
{
    return m_message.toLatin1().data();
}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
ShortNameCollisionException::ShortNameCollisionException(const QString& newArgName, const QString& existingArgName) :
    TaranisException(QString("The new argument {%1} as the same short name as the existing argument {%2}.").arg(newArgName).arg(existingArgName))

{}

////////////////////////////////////////////////////////////////////////////////////////////////
ShortNameCollisionException::ShortNameCollisionException(const QString &message) :
    TaranisException( message )
{}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
ArgumentRedefinitionException::ArgumentRedefinitionException(const QString& argName) :
    TaranisException(QString("Two arguments were defined with the same name: {%1}").arg(argName))
{}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
HelpShortNameCollisionException::HelpShortNameCollisionException(const QString& argumentName) :
    ShortNameCollisionException(QString("The short name for the argument {%1} collides with the short name for the built in {help} argument.").arg(argumentName))
{}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
QApplicationDoesNotExsistException::QApplicationDoesNotExsistException() :
    TaranisException("You must initialize QApplication before building a "
                     "CommandLineInterface.")
{}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
VersionShortNameCollisionException::VersionShortNameCollisionException(const QString &argName) :
    ShortNameCollisionException(QString("The short name for the argument {%1} collides with the short name for the built in {version} argument.").arg(argName))
{}

////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
VersionArgumentRedefinitionException::VersionArgumentRedefinitionException() :
    ArgumentRedefinitionException("version")
{}
