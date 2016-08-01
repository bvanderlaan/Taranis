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
#include <QDir>
#include "QVerifyExceptionThrown.hpp" // For Qt 5.2.x and lower
#include "QVerifyNoExceptionThrown.hpp"
#include "TaranisTestSuite.hpp"
#include "CommandLineInterface.hpp"
#include "InputArgument.hpp"
#include "TaranisExceptions.hpp"

using namespace Taranis::UnitTest;

/////////////////////////////////////////////////////////////////////////////
TaranisTestSuite::TaranisTestSuite(QObject *parent) : QObject(parent)
{
    m_executableName = QFileInfo( QCoreApplication::applicationFilePath() ).fileName();
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSetName()
{
    CommandLineInterface cli = CommandLineInterface::build().WithName("MyApp");
    QCOMPARE( cli.name(), QStringLiteral("MyApp") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSetVersion()
{
    CommandLineInterface cli = CommandLineInterface::build().WithVersion("1.2.3.4");
    QCOMPARE( cli.version(), QStringLiteral("1.2.3.4"));
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSetDescription()
{
    CommandLineInterface cli = CommandLineInterface::build().WithDescription("I'm a great app!");
    QCOMPARE( cli.description(), QStringLiteral("I'm a great app!") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDefaultHelpMessage()
{
    CommandLineInterface cli = CommandLineInterface::build().getCommandLineInterface();
    QString expected = QString("Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n").arg(m_executableName);



    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithName()
{
    CommandLineInterface cli = CommandLineInterface::build().WithName("MyApp");
    QString expected = QString("MyApp\n"
                       "=====\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithVersion()
{
    CommandLineInterface cli = CommandLineInterface::build().WithVersion("1.2.3.4");
    QString expected = QString("Version 1.2.3.4\n"
                       "===============\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithNameAndVersion()
{
    CommandLineInterface cli = CommandLineInterface::build()
                                                .WithName("MyApp")
                                                .WithVersion("1.2.3.4");
    QString expected = QString("MyApp - Version 1.2.3.4\n"
                       "=======================\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescription()
{
    CommandLineInterface cli = CommandLineInterface::build()
                                    .WithDescription("I'm a great app!");


    QString expected = QString("I'm a great app!\n\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescriptionAndName()
{
    CommandLineInterface cli = CommandLineInterface::build()
                                    .WithName("MyApp")
                                    .WithDescription("I'm a great app!");

    QString expected = QString("MyApp\n"
                       "=====\n"
                       "I'm a great app!\n\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithDescriptionAndNameAndVersion()
{
    CommandLineInterface cli = CommandLineInterface::build()
                                        .WithName("MyApp")
                                        .WithDescription("I'm a great app!")
                                        .WithVersion("1.2.3.4");


    QString expected = QString("MyApp - Version 1.2.3.4\n"
                       "=======================\n"
                       "I'm a great app!\n\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n"
                       "  -v, --version\tDisplay version information and exit\n").arg(m_executableName);


    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testHelpMessageWithCustomArgument()
{
    CommandLineInterface cli = CommandLineInterface::build()
                                    .WithName("MyApp")
                                    .WithDescription("I'm a great app!")
                                    .WithVersion("1.2.3.4")
                                    .WithFlag("mouse", "Force mouse to be displayed in release build.");


    QString expected = QString("MyApp - Version 1.2.3.4\n"
                       "=======================\n"
                       "I'm a great app!\n\n"
                       "Usage: %1 [OPTION]\n\n"
                       "  -?\tDisplay this help and exit\n"
                       "  -h, --help\tDisplay this help and exit\n"
                       "  -m, --mouse\tForce mouse to be displayed in release build.\n"
                       "  -v, --version\tDisplay version information and exit\n").arg(m_executableName);



    QCOMPARE( cli.helpMessage(), expected );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashHelpArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-help"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashHelpArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-HELP"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashDashHelpArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--help"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashDashHelpArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--HELP"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSlashHelpArgument()
{
    if ( QDir::separator() != QChar('/') )
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/help"}).WithAction("help", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSlashHelpArgumentCaseInsensative()
{
    if ( QDir::separator() != QChar('/') )
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/HELP"}).WithAction("help", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashHelpArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-h"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashHelpArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-H"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashDashHelpArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--h"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashDashHelpArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--H"}).WithAction("help", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortSlashHelpArgument()
{
    if ( QDir::separator() != QChar('/') )
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/h"}).WithAction("help", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortSlashHelpArgumentCaseInsensative()
{
    if ( QDir::separator() != QChar('/') )
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/H"}).WithAction("help", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashQuestionMarkArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-?"}).WithAction("?", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashDashQuestionMarkArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--?"}).WithAction("?", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSlashQuestionMarkArgument()
{
    if ( QDir::separator() != QChar('/') )
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/?"}).WithAction("?", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashVersionArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-version"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashVersionArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-VERSION"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashDashVersionArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--version"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testDashDashVersionArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--VERSION"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSlashVersionArgument()
{
    if ( QDir::separator() != QChar('/'))
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/version"}).WithAction("version", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testSlashVersionArgumentCaseInsensative()
{
    if ( QDir::separator() != QChar('/'))
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/VERSION"}).WithAction("version", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashVersionArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-v"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashVersionArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"-V"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashDashVersionArgument()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--v"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortDashDashVersionArgumentCaseInsensative()
{
    int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
    CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"--V"}).WithAction("version", "", [&callCount](QVariant){
        callCount++;
    }).getCommandLineInterface();
    QCOMPARE(callCount, 1);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortSlashVersionArgument()
{
    if ( QDir::separator() != QChar('/'))
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/v"}).WithAction("version", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testShortSlashVersionArgumentCaseInsensative()
{
    if ( QDir::separator() != QChar('/'))
    {
        int callCount(0); // Below we are overloading the built in argument so we can capture if it was caled vs. actually performing the built in action
        CommandLineInterfaceBuilder("MyApp", "1.2.3.4", {"/V"}).WithAction("version", "", [&callCount](QVariant){
            callCount++;
        }).getCommandLineInterface();
        QCOMPARE(callCount, 1);
    }
    else
    {
        QSKIP("Not applicable for this plaform");
    }
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAccessViaIndexOperatorWhenValueExists()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--mouse"})
            .WithFlag("mouse", "Force mouse to be displayed in release build.")
            .getCommandLineInterface();

    QCOMPARE( arguments["mouse"], QVariant(true) );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAccessViaIndexOperatorWhenValueDoesNotExist()
{
    auto arguments = CommandLineInterface::build()
            .WithFlag("mouse", "Force mouse to be displayed in release build.")
            .getCommandLineInterface();

    QCOMPARE( arguments["mouse"], QVariant(false) );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAccessViaIndexOperatorWhenArgumentIsUnknown()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--mouse"})
            .WithFlag("mouse", "Force mouse to be displayed in release build.")
            .getCommandLineInterface();

    QCOMPARE( arguments["force"].isValid(), false );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithUpperCaseAndProvidedWithUpperCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--Debug"})
            .WithFlag("Debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithUpperCaseAndProvidedWithLowerCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--debug"})
            .WithFlag("Debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithLowerCaseAndProvidedWithUpperCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--Debug"})
            .WithFlag("debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithLowerCaseAndProvidedWithLowerCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--debug"})
            .WithFlag("debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithUpperCaseAndProvidedWithShortUpperCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--D"})
            .WithFlag("Debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithUpperCaseAndProvidedWithShortLowerCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithFlag("Debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithLowerCaseAndProvidedWithShortUpperCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--D"})
            .WithFlag("debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentDefinedWithLowerCaseAndProvidedWithShortLowerCase()
{
    CommandLineInterface arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithFlag("debug", "Enables debug mode.");

    QCOMPARE( arguments["Debug"].toBool(), true );
    QCOMPARE( arguments["debug"].toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingEqualsNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote=1.2.3.4"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingEqualsWithEqualsInValueNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote=1.2.3.4=earth"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4=earth") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingEqualsUsingSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote=","1.2.3.4"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingColonNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote:1.2.3.4"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingColonWithColonInValueNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote:1.2.3.4:earth"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4:earth") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingColonUsingSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote:", "1.2.3.4"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote","1.2.3.4"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueNoSpaceAndSecondInvalidArgument()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote:1.2.3.4","fubar"})
            .WithValue("remote", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testARgumentWithDefaultValueWhenAbsent()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {})
            .WithValue("remote", "1.2.3.4", "This is a test, please stand by.")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("1.2.3.4") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testARgumentWithDefaultValueWhenProvided()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--remote","192.168.228.64"})
            .WithValue("remote", "1.2.3.4", "This is a test, please stand by.")
            .getCommandLineInterface();

    QCOMPARE( arguments["remote"].toString(), QString("192.168.228.64") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentsWithTheSameName()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithFlag("debug", "Enables debug mode.")
            .WithFlag("debug", "Enables debug mode."), ArgumentRedefinitionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentsWithSameNameButDifferentCase()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithFlag("debug", "Enables debug mode.")
            .WithFlag("Debug", "Enables debug mode."), ArgumentRedefinitionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingARgumentsWithSameNameButOneIsAFlagAndTheOtherIsAnArgument()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithFlag("log", "Enables logging.")
            .WithValue("log", "Set log level."), ArgumentRedefinitionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentsWithDifferentNamesButSameShortName()
{
    QVERIFY_EXCEPTION_THROWN( CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithValue("server", "Set server ip.")
            .WithValue("serial", "Set serial number."), ShortNameCollisionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentsWithDifferentNamesButSameShortNameWithDifferentCase()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--d"})
            .WithValue("server", "Set server ip.")
            .WithValue("Serial", "Set serial number."), ShortNameCollisionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentWhichCollidesWithBuiltInHelpShortName()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder()
            .WithValue("here", "Canada", "Set current location."), HelpShortNameCollisionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentWhichCollidesWithBuiltInVersionShortName()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder()
            .WithName("My Cool App")
            .WithVersion("1.2.3.4-abc")
            .WithFlag("verbose", "Enables verbose logging."), VersionShortNameCollisionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentWhichCollidesWithBuiltInVersionShortNameButNoVersionIsSet()
{
    QVERIFY_NO_EXCEPTION_THROWN(CommandLineInterfaceBuilder()
                        .WithName("My Cool App")
                                .WithFlag("verbose", "Enables verbose logging."));
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testAddingArgumentWhichCollidesWithBuiltInVersionShortNameButNoVersionIsSetHoweverAnotherArgumentWithSameShortNameIs()
{
    QVERIFY_EXCEPTION_THROWN(CommandLineInterfaceBuilder()
            .WithName("My Cool App")
            .WithFlag("victor", "Enables victor mode.")
            .WithFlag("verbose", "Enables verbose logging."), ShortNameCollisionException);
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testIsValidWhenItIs()
{
    InputArgument arg( "--help", {"--"} );
    QCOMPARE( arg.isValid(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testIsValidWhenItsNot()
{
    InputArgument arg( "help", {"--"} );
    QCOMPARE( arg.isValid(), false );

    InputArgument arg2( "--", {"--"} );
    QCOMPARE( arg2.isValid(), false );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testWhenArgumentHasPrefixInName()
{
    InputArgument arg( "--help--this", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.name(), QStringLiteral("help--this") );
    QCOMPARE( arg.prefix(), QStringLiteral("--"));
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testPrefixDash()
{
    InputArgument arg( "-help", {"-"} );
    QCOMPARE( arg.prefix(), QStringLiteral("-") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testPrefixDashDash()
{
    InputArgument arg( "--help", {"--"} );
    QCOMPARE( arg.prefix(), QStringLiteral("--") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testPrefixDashDashWhenDashIsAlsoAccepted()
{
    InputArgument arg( "--help", {"-", "--"} );
    QCOMPARE( arg.prefix(), QStringLiteral("--") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testPrefixSlash()
{
    InputArgument arg( "/help", {"/"} );
    QCOMPARE( arg.prefix(), QStringLiteral("/") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testPrefixWhenNotFound()
{
    InputArgument arg( "=help", {"-", "--", "/"} );
    QCOMPARE( arg.prefix(), QStringLiteral("") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithDashPrefix()
{
    InputArgument arg( "-help", {"-"} );
    QCOMPARE( arg.name(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithDashDashPrefix()
{
    InputArgument arg( "--help", {"--"} );
    QCOMPARE( arg.name(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithDashDashPrefixWhenDashPrefixIsAlsoAccepted()
{
    InputArgument arg( "--help", {"-", "--"} );
    QCOMPARE( arg.name(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithSlashPrefix()
{
    InputArgument arg( "/help", {"/"} );
    QCOMPARE( arg.name(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWhenPrefixNotFound()
{
    InputArgument arg( "=help", {"-", "--", "/"} );
    QCOMPARE( arg.name(), QStringLiteral("") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithUpperCase()
{
    InputArgument arg( "--HELP", {"--"} );
    QCOMPARE( arg.name(), QStringLiteral("HELP") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenFlag()
{
    InputArgument arg( "--HELP", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toBool(), true );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenNotValid()
{
    InputArgument arg( "HELP", {"--"} );
    QCOMPARE( arg.isValid(), false );
    QCOMPARE( arg.value().toBool(), false );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenEqualSeperatorNoSpaceUsed()
{
    InputArgument arg( "--world=earth", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenEqualSeperatorAndEqualsInValueNoSpaceUsed()
{
    InputArgument arg( "--world=earth=home", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth=home") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenEqualSeperatorAndSpaceInValueNoSpaceUsed()
{
    InputArgument arg( "--world=\"earth home\"", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("\"earth home\"") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenColonSeperatorNoSpaceUsed()
{
    InputArgument arg( "--world:earth", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenColonSeperatorAndColonInValueNoSpaceUsed()
{
    InputArgument arg( "--world:earth:home", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth:home") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenColonSeperatorAndSpaceInValueNoSpaceUsed()
{
    InputArgument arg( "--world:\"earth home\"", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("\"earth home\"") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenColonSeperatorAndEqualsInValueNoSpacesUsed()
{
    InputArgument arg( "--world:earth=home", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth=home") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentValueWhenEqualsSeperatorAndColonInValueNoSpacesUsed()
{
    InputArgument arg( "--world=earth:home", {"--"} );
    QCOMPARE( arg.isValid(), true );
    QCOMPARE( arg.value().toString(), QStringLiteral("earth:home") );
}
