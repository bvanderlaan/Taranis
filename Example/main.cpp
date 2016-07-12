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
#include <QDebug>
#include "CommandLineInterface.hpp"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    auto arguments = Taranis::CommandLineInterface("My Cool App")
            .WithVersion("1.2.3.4-abc")
            .WithFlag("mouse", "Force mouse to be displayed in release build.")
            .process();

    qDebug() << "Show Mouse? " << ( arguments["mouse"].toBool() ? "Yes" : "No" );


    /// OR ///

    bool showMouse( false );
    Taranis::CommandLineInterface("My Cool App")
            .WithVersion("1.2.3.4-abc")
            .WithFlag("mouse", "Force mouse to be displayed in release build.",
                      [&showMouse](QVariant) {
                            showMouse = true;
                       })
            .process();

    qDebug() << "Show Mouse? " << ( showMouse ? "Yes" : "No" );

    return a.exec();
}
