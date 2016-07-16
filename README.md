# Taranis

[![Build Status](https://travis-ci.org/bvanderlaan/Taranis.svg?branch=master)](https://travis-ci.org/bvanderlaan/Taranis)

Taranis is a toolkit which can be used in Qt projects to provide a command line interface for inputting start up parameters into your application.

GUI applications or background processes tend to have flags now and again to allow users to alter how the application will run. They might have 
flags to change their logging level or alter server connection addresses. The code to process the command line arguments fed into an application
is largely boiler plate but to do it nicely is a bit of a pain.

Taranis is a class you can instantiate which will handle parsing whatever type of command line argument your application requires. It will deal with
case sensitivity and differences in flag syntax such as backslashes (/), dashes (-), or double dashes (--) as well as differences in conventions such as
triggering help with either an 'h' or a question mark (?). Taranis will also provide long and short forms of your desired flags such as '--help' or '-h'.

Taranis will also take care of generating help text and printing it to the console when the help flag is provided.

## Usage

TBD

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/bvanderlaan/taranis. This project is intended to be a safe, welcoming space for 
collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The library is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).