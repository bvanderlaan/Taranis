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
#ifndef INPUTARGUMENTKEYVALUEPAIR_HPP
#define INPUTARGUMENTKEYVALUEPAIR_HPP

#include <QObject>
#include <QStringList>
#include <QString>

namespace Taranis
{
    namespace Internal
    {
        /**
         * @brief The InputArgumentKeyValuePair class represents input data consisting of a key and a value.
         * The key is the string used to represent a given argument. We say key here becuase it could be a
         * long name, i.e. 'help', or a short name, i.e. 'h', but will be used as the look up key in the CLI's
         * list of acceptable arguments.
         *
         * Once an argument has been detected this class will be used to parse the string to detect any values
         * attached to the argument. This class will handle a number of different seperator characters to support
         * inputs such as:
         *
         *    address:1.23.4.5
         *    address=1.23.4.5
         *    address 1.23.4.5
         */
        class InputArgumentKeyValuePair : QObject
        {
        public:
            explicit InputArgumentKeyValuePair(const QString arg, QObject *parent = 0);
            explicit InputArgumentKeyValuePair(const QString arg, QStringList acceptedArgumentPrefixs, QObject *parent = 0);
            ~InputArgumentKeyValuePair() {}

            QString key() const;
            QString value() const;
            QString seperator() const;
            bool isValid() const;

        private:
            QString m_key;
            QString m_value;
            QString m_seperator;
            QStringList m_valueSeperators;
            QString m_originalArgumentString;

            /**
             * @brief getSeperatorInfo will detect a value seperator.
             * @param argument is an argument string which may include a value.
             * @return Returns which seperator character was found and its index in the argument string.
             */
            QPair<QString,int> getSeperatorInfo(const QString argument) const;
            void updateKeyValuePair(const QPair<QString,int> seperatorInfo);
        };
    }
}

#endif // INPUTARGUMENTKEYVALUEPAIR_HPP
