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

#ifndef TARANISTESTSUITE_HPP
#define TARANISTESTSUITE_HPP

#include <QObject>

namespace Taranis
{
    namespace UnitTest
    {
        class TaranisTestSuite : public QObject
        {
            Q_OBJECT
        public:
            explicit TaranisTestSuite(QObject *parent = 0);

            QString m_executableName;

        private slots:
            /// Test Setting Name and Version
            void testConstructWithNameAndVersion();
            void testSetVersionWithFluentInterface();
            void testSetDescription();

            /// Test Help Message Generation
            void testDefaultHelpMessage();
            void testHelpMessageWithName();
            void testHelpMessageWithVersion();
            void testHelpMessageWithNameAndVersion();
            void testHelpMessageWithDescription();
            void testHelpMessageWithDescriptionAndName();
            void testHelpMessageWithDescriptionAndNameAndVersion();
            void testHelpMessageWithCustomArgument();

            /// Test Built in Argument Processing ///

            /// Help Argument
            void testDashHelpArgument();
            void testDashHelpArgumentCaseInsensative();
            void testDashDashHelpArgument();
            void testDashDashHelpArgumentCaseInsensative();
            void testSlashHelpArgument();
            void testSlashHelpArgumentCaseInsensative();

            /// Short Help Argument
            void testShortDashHelpArgument();
            void testShortDashHelpArgumentCaseInsensative();
            void testShortDashDashHelpArgument();
            void testShortDashDashHelpArgumentCaseInsensative();
            void testShortSlashHelpArgument();
            void testShortSlashHelpArgumentCaseInsensative();

            /// Question Mark Argument
            void testDashQuestionMarkArgument();
            void testDashDashQuestionMarkArgument();
            void testSlashQuestionMarkArgument();

            /// Version Argument
            void testDashVersionArgument();
            void testDashVersionArgumentCaseInsensative();
            void testDashDashVersionArgument();
            void testDashDashVersionArgumentCaseInsensative();
            void testSlashVersionArgument();
            void testSlashVersionArgumentCaseInsensative();

            /// Short Version Argument
            void testShortDashVersionArgument();
            void testShortDashVersionArgumentCaseInsensative();
            void testShortDashDashVersionArgument();
            void testShortDashDashVersionArgumentCaseInsensative();
            void testShortSlashVersionArgument();
            void testShortSlashVersionArgumentCaseInsensative();

            /// Access values
            void testAccessViaIndexOperatorWhenValueExists();
            void testAccessViaIndexOperatorWhenValueDoesNotExist();
            void testAccessViaIndexOperatorWhenArgumentIsUnknown();

            /// Arguments with Values
            void testArgumentWithValueUsingEqualsNoSpace();
            void testArgumentWithValueUsingEqualsWithEqualsInValueNoSpace();
            void testArgumentWithValueUsingColonNoSpace();
            void testArgumentWithValueUsingColonWithColonInValueNoSpace();

            /// InputArgument
            void testIsValidWhenItIs();
            void testIsValidWhenItsNot();
            void testWhenArgumentHasPrefixInName();
            void testPrefixDash();
            void testPrefixDashDash();
            void testPrefixDashDashWhenDashIsAlsoAccepted();
            void testPrefixSlash();
            void testPrefixWhenNotFound();

            void testArgumentWithDashPrefix();
            void testArgumentWithDashDashPrefix();
            void testArgumentWithDashDashPrefixWhenDashPrefixIsAlsoAccepted();
            void testArgumentWithSlashPrefix();
            void testArgumentWhenPrefixNotFound();
            void testArgumentWithUpperCase();

            void testArgumentValueWhenFlag();
            void testArgumentValueWhenNotValid();
            void testArgumentValueWhenEqualSeperatorNoSpaceUsed();
            void testArgumentValueWhenEqualSeperatorAndEqualsInValueNoSpaceUsed();
            void testArgumentValueWhenEqualSeperatorAndSpaceInValueNoSpaceUsed();
            void testArgumentValueWhenColonSeperatorNoSpaceUsed();
            void testArgumentValueWhenColonSeperatorAndColonInValueNoSpaceUsed();
            void testArgumentValueWhenColonSeperatorAndSpaceInValueNoSpaceUsed();
            void testArgumentValueWhenColonSeperatorAndEqualsInValueNoSpacesUsed();
            void testArgumentValueWhenEqualsSeperatorAndColonInValueNoSpacesUsed();
        };
    }
}

#endif // TARANISTESTSUITE_HPP
