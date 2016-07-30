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

To use Taranis you need to build a **CommandLineInterface** object which you do through the **CommandLineInterface::build()** method. The build method has a 
fluid interface allowing you to define the command line interface your application will have by using the *With* methods.

### Example 1 - A simple Command Line Interface
```
  #include <QCoreApplication>
  #include "Taranis/CommandLineInterface.hpp"
  #include "myWidget.hpp"
  using namespace Taranis;
  int main(int argc, char *argv[])
  {
      QCoreApplication a(argc, argv);
      MyWidget w;

      CommandLineInterface arguments = CommandLineInterface::build()
                          .WithName("My Cool App")
                          .WithVersion("1.2.3.4-abc");
      w.show();
      return a.exec();
  }
```         

With the above your application will now be sporting a command line interface which accepts two flags

* **--version:** Will print your applications version to the terminal then exit your application.
* **--help:** Will print a typical help message to the terminal then exit your application.
Users can now query your applications version by typing:
> $ myApp.exe --version

or 
> $ myApp.exe -v

Users can also get some help text which will display your applications name and version along with the description of the version and help command line arguments.
> $ myApp.exe --help

or
> $ myApp.exe -h

or 
> $ myApp.exe -?

### Example 2 - A Custom Command Line Interface
```
  #include <QCoreApplication>
  #include "Taranis/CommandLineInterface.hpp"
  #include "myWidget.hpp"
  using namespace Taranis;
  int main(int argc, char *argv[])
  {
      QCoreApplication a(argc, argv);
      MyWidget w;

      CommandLineInterface arguments = CommandLineInterface::build()
                          .WithName("My Cool App")
                          .WithDescription("This application is really good and has a CLI to boot!")
                          .WithVersion("1.2.3.4-abc");
                          .WithFlag("debug", "Enable debug mode")

      if( arguments["debug"].toBool() ) 
      {
          w.enableDebug();
      }
      
      w.show();
      return a.exec();
  }
```            

In this example you get all the same features as in Example 1 however now your application will accept the --debug flag. 
Users can type any of the following commands to enable debug mode.

> $ myApp.exe --Debug<br>
> $ myApp.exe --debug<br>
> $ myApp.exe -d

Not only does your application have a debug mode flag but your flag will now be shown in the built in help message displayed when users use the *--help* argument.

### Example 3 - A Custom Command Line Interface which Accepts Values
```
  #include <QCoreApplication>
  #include <QHostAddress>
  #include "Taranis/CommandLineInterface.hpp"
  #include "myWidget.hpp"
  using namespace Taranis;
  int main(int argc, char *argv[])
  {
      QCoreApplication a(argc, argv);
      MyWidget w;

      CommandLineInterface arguments = CommandLineInterface::build()
                          .WithName("My Cool App")
                          .WithVersion("1.2.3.4-abc");
                          .WithFlag("debug", "Enable debug mode.")
                          .WithValue("server", "The IP address to the server.")

      if ( arguments["debug"].toBool() ) {...}
      if ( arguments["server"].isValid() )
      {
          w.setServerIp( QHostAddress( arguments["server"].toString() ) );
      }
      
      w.show();
      return a.exec();
  }
```            
In this example we added another argument but this one expects a value. Users can input the value in a number of ways.
> $ myApp.exe --server 1.2.3.4<br>
> $ myApp.exe --server=1.2.3.4<br>
> $ myApp.exe --server:1.2.3.4

Just like with flags you also get a short form of your value argument.

> $ myApp.exe --s 1.2.3.4<br>
> $ myApp.exe --s=1.2.3.4<br>
> $ myApp.exe --s:1.2.3.4

Lastly the server argument also shows up in the built in help message displayed when users use the *--help* argument.

To learn more on how to use Taranis in your applications feel free to [view the documentation](https://bvanderlaan.github.io/Taranis/docs) which includes 
multiple examples.

## Donations

If you like Taranis and want to support it and other open source work that I do you can do so via [Gratipay](https://gratipay.com/~bvanderlaan/).

[![Support via Gratipay](https://cdn.rawgit.com/gratipay/gratipay-badge/2.3.0/dist/gratipay.svg)](https://gratipay.com/~bvanderlaan/)

## Contributing

Bug reports and pull requests are welcome on GitHub at https://github.com/bvanderlaan/taranis. This project is intended to be a safe, welcoming space for 
collaboration, and contributors are expected to adhere to the [Contributor Covenant](http://contributor-covenant.org) code of conduct.

## License

The library is available as open source under the terms of the [MIT License](http://opensource.org/licenses/MIT).