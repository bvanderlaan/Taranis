# Taranis

[![Build Status](https://travis-ci.org/bvanderlaan/Taranis.svg?branch=master)](https://travis-ci.org/bvanderlaan/Taranis)
[![Build status](https://ci.appveyor.com/api/projects/status/bfcjgkstm2r064e2?svg=true)](https://ci.appveyor.com/project/bvanderlaan/taranis)

Taranis is a toolkit which can be used in Qt projects to provide a command line interface for inputting start up parameters into your application.

GUI applications or background processes tend to have flags now and again to allow users to alter how the application will run. They might have flags 
to change their logging level or alter server connection addresses. The code to process the command line arguments fed into an application is largely 
boiler plate but to do it nicely is a bit of a pain as there are lots of variants in how values can be inputted by the user.

*Why re-invent the wheel? Just use Taranis!*

Taranis is a class you can instantiate which will handle parsing whatever type of command line argument your application requires. It will deal with 
case sensitivity and differences in flag syntax such as backslashes (/), dashes (-), or double dashes (--) as well as differences in conventions such 
as triggering help with either an *h* or a question mark (?). Taranis will also provide long and short forms of your desired flags such as *--help* or *-h*.

## What you get with Taranis

When you use Taranis to process command line inputs you get all the niceties you come to expect as a user from a command line interface for free! 
Simply define what arguments your application will support and let Taranis do the rest.

The niceties you get with Taranis include:

* Case insensitive flag comparisons.
* Flag short names, you register an argument called server and Taranis will accept server as well as s
* Built in version argument. Tell Taranis your applications version and it will allow users to query for it on the command line.
* Built in help argument. Its always nice to have help now and again and with Taranis you'll be able to print out some help text for your users describing the command line interface for your application via the help command for free.

## Usage

TBD

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/bvanderlaan/taranis. This project is intended to be a safe, welcoming space for 
collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The library is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).