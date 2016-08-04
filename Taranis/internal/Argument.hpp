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
#ifndef ARGUMENT_HPP
#define ARGUMENT_HPP

#include <QString>
#include <QVariant>
#include <functional>
#include "ArgumentType.hpp"

namespace Taranis
{
    namespace Internal
    {
        /**
         * @brief The Argument class represents a command line argument.
         * This object has a name and a short name (quite, q), a description,
         * a type, and the value provided by the user on the CLI.
         */
        class Argument
        {
        public:
            Argument(const QString name, const QString description, const ArgumentType type, std::function<void(QVariant)> callback);
            ~Argument() {}

            QString name() const;
            QString shortName() const;
            bool hasShortName() const;
            QString description() const;
            ArgumentType type() const;
            QVariant value() const;
            void setValue( QVariant value );

            /**
             * @brief callback is the function you want performed when the argument is detected on the CLI.
             * The call back could be as simple as setting a value to be read by your program later or it could
             * be a handler that performs some action when an argument is present and/or at a given value.
             */
            std::function<void(QVariant)> callback();

        private:
            QString m_name;
            QString m_description;
            ArgumentType m_type;
            QVariant m_value;
            std::function<void(QVariant)> m_actionCallback;
        };
    }
}

#endif // ARGUMENT_HPP
