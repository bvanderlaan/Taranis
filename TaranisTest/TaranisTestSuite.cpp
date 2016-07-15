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
#include "TaranisTestSuite.hpp"
#include "CommandLineInterface.hpp"
#include "InputArgument.hpp"

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
void TaranisTestSuite::testArgumentWithValueUsingEqualsNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--hello=world"})
            .WithValue("hello", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["hello"].toString(), QString("world") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingEqualsWithEqualsInValueNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--hello=world=earth"})
            .WithValue("hello", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["hello"].toString(), QString("world=earth") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingColonNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--hello:world"})
            .WithValue("hello", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["hello"].toString(), QString("world") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithValueUsingColonWithColonInValueNoSpace()
{
    auto arguments = CommandLineInterfaceBuilder("My Cool App", "1.2.3", {"--hello:world:earth"})
            .WithValue("hello", "test")
            .getCommandLineInterface();

    QCOMPARE( arguments["hello"].toString(), QString("world:earth") );
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
    QCOMPARE( arg.argument(), QStringLiteral("help--this") );
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
    QCOMPARE( arg.argument(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithDashDashPrefix()
{
    InputArgument arg( "--help", {"--"} );
    QCOMPARE( arg.argument(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithDashDashPrefixWhenDashPrefixIsAlsoAccepted()
{
    InputArgument arg( "--help", {"-", "--"} );
    QCOMPARE( arg.argument(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithSlashPrefix()
{
    InputArgument arg( "/help", {"/"} );
    QCOMPARE( arg.argument(), QStringLiteral("help") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWhenPrefixNotFound()
{
    InputArgument arg( "=help", {"-", "--", "/"} );
    QCOMPARE( arg.argument(), QStringLiteral("") );
}

/////////////////////////////////////////////////////////////////////////////
void TaranisTestSuite::testArgumentWithUpperCase()
{
    InputArgument arg( "--HELP", {"--"} );
    QCOMPARE( arg.argument(), QStringLiteral("HELP") );
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
