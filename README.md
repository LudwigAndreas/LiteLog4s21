# LogLite

Minimalistic C++ logger library inspired by log4cxx.

## Table of Contents

- [About](#about)
  - [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installing](#installing)
- [Running the tests](#running-the-tests)
- [Usage](#usage)
- [Built Using](#built-using)
- [Authors](#authors)
- [Acknowledgments](#acknowledgments)
- [License](#license)

## About

A lightweight logger library inspired by log4cxx but stripped down to include
only the necessary classes for simplicity and efficiency. This logger is
designed to facilitate easy logging in your C++ projects while keeping the
overhead to a minimum.

### Features

- Easy-to-use logging functionality.
- Support for different log levels (TRACE, DEBUG, INFO, WARN, ERROR, FATAL).
- Customizable log output format.
- Ability to log to any output stream or files.
- Lightweight and efficient.
- Similar usage with Log4 family.

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes.

### Prerequisites

What things you need to install the software and how to install them.

```text
cmake >= 3.10
gcc >= 7.5.0
```

```bash
sudo apt-get install cmake
sudo apt-get install gcc
```

### Installing

A step by step series of examples that tell you how to get a development env running.

1. Clone the repository:

   ```bash
   git clone https://github.com/LudwigAndreas/LogLite.git
    ```

2. Build the library using CMake:

   ```bash
   mkdir build
   cd build
   cmake ..
   cake --build . 
    ```

3. Include the necessary header files in your C++ project:

   ```c++
    #include "<LogLite_path>/include/Logger.h"
    ```

4. Link your project with the generated library:

    ```bash
    g++ example.cc -L/path/to/LogLite/lib/LogLitelib.a
    ```

## Running the tests

## Usage

```c++
#include "logger.h"

int my_awesome_func() {
//  you don't need to handle with logger creating and deleting
  auto logger = s21::diagnostic::Logger::GetLogger("MyApp");
  
  LOG_TRACE(logger, "This is working like log4cxx");
  
  return 10;
}

int main() {
//  Initialize the logger with a log file name and log level
    auto logger = s21::diagnostic::Logger::GetLogger("MyApp");
//  Set default log layout settings and set output to std::cout 
    s21::diagnostic::LoggerConfigurator::configure();
//  Log messages at different levels
    LOG_TRACE(logger, "This is a debug message.");
    LOG_DEBUG(logger, "This is a debug message.");
    LOG_INFO(logger, "This is an info message.");
    LOG_INFO(logger, "you can also pass data in the same way as in a stream" 
             << my_awesome_func() << " " << ":)");
    LOG_WARN(logger, "This is a warning message.");
    LOG_ERROR(logger, "This is an error message.");
    LOG_FATAL(logger, "This is a fatal message.");
    return 0;  
}
```

### Configuration

The logger output can be customized as you wish. Users can modify the log level,
log format, and output destination (console or file) at any time using logger
methods.

```c++
#include "logger.h"

int main() {
//  Initialize the logger with a log file name and log level
    auto cout_logger = s21::diagnostic::Logger::GetLogger("MyApp");
    
    auto file_logger = s21::diagnostic::Logger::GetLogger("MyApp_file");

    
//  You can add any output stream, and configure the stream object control. 
    cout_logger->AddOutputStream(std::cerr, false);
    
//  If second argument is true, then stream object will be deleted automatically
    file_logger->AddOutputStream(new std::fstream("myApp.log"), true);
    
//  You can set the output pattern for all loggers in the program 
    s21::diagnostic::LoggerConfigurator::configure(
        s21::diagnostic::PatternLayout(
            "%d{%Y-%m-%d %X} %Y%5.5p%y m%-5P --- [%M] %-25.40F : %m%n"
            ));
//  or for each separately
    file_logger->SetPatternLayout(
      s21::diagnostic::PatternLayout(
          "%%Y%5.5p%y : %m%n"
          ));
    
//  You can configure log level for each logger (by default it is Trace)
    cout_logger->SetLevel(s21::diagnostic::LogLevel::Info);
    
    LOG_INFO(logger, "This is an info message.");
    return 0;  
}
```

### Log Formatting

The logger supports the following placeholders in the log format:

- `%c` / `%logger`: Used to output the name of the logger generating the logging
  event
- `%C` / `%class`: Used to output the class of the issuer of the logging event
  if the compiler used supports a macro to retrieve it
- `%Y` : Used to wrap log with color. All colors are customizable
- `%y` : Used to wrap log with color. The y is the end of a color block
- `%d` / `%date`: Used to output the date of the logging event
- `%f` : Used to output the short file name where the logging request was issued
- `%F` / `%file`: Used to output the file name where the logging request was
  issued
- `%l` : Used to output location information of the caller which generated the
  logging event
- `%L` / `%line`: Used to output the line number from where the logging request
  was issued
- `%m` / `%message`: Used to output the application supplied message associated
  with the logging event
- `%M` / `%method`: Used to output the method of the issuer of the logging event
  if the compiler used supports a macro to retrieve it
- `%n` : Outputs the platform dependent line separator character or characters
- `%p` / `%level`: Used to output the level of the logging event
- `%P` / `%pid`: Used to output the name of the process id of the logging event
- `%r` / `%relative`: Used to output the number of milliseconds elapsed since
  the start of the application until the creation of the logging event
- `%t` / `%thread`: Used to output the ID of the thread that generated the
  logging event
- `%%` : The sequence outputs a single percent sign

## Built Using

- [C++ 17](https://isocpp.org/) - Programming language
- [CMake](https://cmake.org/) - Build system
- [Google Test](https://google.github.io/googletest/) - Testing framework

## Authors

| <img src="https://avatars.githubusercontent.com/u/88089961?v=4" alt="drawing" width="50"/> |[LudwigAndreas](https://github.com/LudwigAndreas)|
| --- | --- |

## Acknowledgments

- [Log4cxx](https://logging.apache.org/log4cxx/latest_stable/) - The inspiration
  for this project

## License

This project is licensed under the MIT License - see
the [LICENSE](https://chat.openai.com/LICENSE) file for details.
