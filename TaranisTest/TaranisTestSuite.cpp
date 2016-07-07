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

#include <QTest>
#include "TaranisTestSuite.hpp"
#include "CommandLineInterface.hpp"

using namespace Taranis::UnitTest;

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDefaultHelpMessage()
{
    CommandLineInterface cli;
    QString expected = "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithName()
{
    CommandLineInterface cli("MyApp");
    QString expected = "MyApp\n"
                       "=====\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithVersion()
{
    auto cli = CommandLineInterface().WithVersion("1.2.3.4");
    QString expected = "Version 1.2.3.4\n"
                       "===============\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithNameAndVersion()
{
    CommandLineInterface cli("MyApp", "1.2.3.4");
    QString expected = "MyApp - Version 1.2.3.4\n"
                       "=======================\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescription()
{
    auto cli = CommandLineInterface()
                        .WithDescription("I'm a great app!");


    QString expected = "I'm a great app!\n\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescriptionAndName()
{
    auto cli = CommandLineInterface("MyApp")
                            .WithDescription("I'm a great app!");

    QString expected = "MyApp\n"
                       "=====\n"
                       "I'm a great app!\n\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescriptionAndNameAndVersion()
{
    auto cli = CommandLineInterface("MyApp")
                        .WithDescription("I'm a great app!")
                        .WithVersion("1.2.3.4");


    QString expected = "MyApp - Version 1.2.3.4\n"
                       "=======================\n"
                       "I'm a great app!\n\n"
                       "Usage: TaranisTest.exe [OPTION]\n\n"
                       "  -h, -?, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n";


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testConstructWithNameAndVersion()
{
    CommandLineInterface cli("MyApp", "1.2.3.4");
    QCOMPARE( cli.name(), QStringLiteral("MyApp") );
    QCOMPARE( cli.version(), QStringLiteral("1.2.3.4"));
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSetVersionWithFluentInterface()
{
    auto cli = CommandLineInterface("MyApp").WithVersion("1.2.3.4");
    QCOMPARE( cli.name(), QStringLiteral("MyApp") );
    QCOMPARE( cli.version(), QStringLiteral("1.2.3.4"));
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSetDescription()
{
    auto cli = CommandLineInterface().WithDescription("I'm a great app!");
    QCOMPARE( cli.description(), QStringLiteral("I'm a great app!") );
}
