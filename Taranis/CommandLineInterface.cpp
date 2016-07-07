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
CommandLineInterface::CommandLineInterface(QObject *parent) :
    CommandLineInterface("", parent)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
CommandLineInterface::CommandLineInterface(const QString applicationName, QObject *parent)
    : QObject(parent),
      m_applicationName(applicationName)
{

}

////////////////////////////////////////////////////////////////////////////////////////////////
QString CommandLineInterface::helpMessage() const
{
    QString message;
    QString applicationExecutable = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();

    if ( !m_applicationName.isEmpty() )
    {
        message += QString("%1\n").arg(m_applicationName);
        message += QString(message.length()-1, '=') + QStringLiteral("\n");
    }


    message += QString("Usage: %1 [OPTION]\n"
            "\n"
            "-h, -?, --help\tDisplay this help and exit\n").arg(applicationExecutable);

    return message;
}
