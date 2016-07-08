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
            explicit TaranisTestSuite(QObject *parent = 0) : QObject(parent) {}

        private slots:
            void testDefaultHelpMessage();
            void testHelpMessageWithName();
            void testHelpMessageWithVersion();
            void testHelpMessageWithNameAndVersion();
            void testHelpMessageWithDescription();
            void testHelpMessageWithDescriptionAndName();
            void testHelpMessageWithDescriptionAndNameAndVersion();
            void testConstructWithNameAndVersion();
            void testSetVersionWithFluentInterface();
            void testSetDescription();

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



        };
    }
}

#endif // TARANISTESTSUITE_HPP
