# LiteLog4s21

**Mini logger for big purposes**

## Description

A lightweight logger library inspired by log4cxx but stripped down to include
only the necessary classes for simplicity and efficiency. This logger is
designed to facilitate easy logging in your C++ projects while keeping the
overhead to a minimum.

## Features

- Easy-to-use logging functionality.
- Support for different log levels (TRACE, DEBUG, INFO, WARN, ERROR, FATAL).
- Customizable log output format.
- Ability to log to any output stream or files.
- Lightweight and efficient.
- Similar usage with Log4 family

## Installation

1. Clone the repository:
   ```shell
   git clone https://github.com/LudwigAndreas/LiteLog4s21.git
    ```
2. Build the library using CMake:
   ```shell
   mkdir build
   cd build
   cmake ..
   cake --build . 
    ```
3. Include the necessary header files in your C++ project:
   ```c++
    #include "<LiteLog4s21_path>/include/Logger.h"
    ```
4. Link your project with the generated library:
    ```shell
    g++ example.cc -L/path/to/LiteLog4s21/lib/LiteLog4s21lib.a
    ```

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

## Configuration

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

## Log Formatting

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

## Contributing

We welcome contributions to improve and enhance this logger. If you'd like to
contribute, please follow these steps:

1. Fork the repository.
2. Create a new branch for your feature or bug fix.
3. Make your changes and commit them with descriptive commit messages.
4. Push your changes to your branch on your forked repository.
5. Open a pull request to merge your changes into the main repository.

## License

This project is licensed under the MIT License - see
the [LICENSE](https://chat.openai.com/LICENSE) file for details.

## Contact

If you have any questions, suggestions, or feedback, please feel free to contact
us at [a.evstratov.work@gmail.com](mailto:a.evstratov.work@gmail.com) or open an issue
on the GitHub repository.