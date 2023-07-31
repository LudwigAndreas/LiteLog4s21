
INCLUDE_DIRECTORIES(${MAINFOLDER}/include)

SET (project_MOC_HEADERS include)
SET (project_LIBS )
SET (project_BIN ${PROJECT_NAME})

ADD_LIBRARY(${project_BIN} STATIC
    ../include/Logger.h
    ../include/LoggerThreading.h
    ../include/LoggerInitializer.h
    ../include/parse/PatternParser.h
    ../include/parse/LoggingEvent.h
    ../include/PatternLayout.h
    ../include/parse/converters/PatternConverter.h
    ../include/parse/converters/LiteralPatternConverter.h
    ../include/parse/converters/LoggerPatternConverter.h
    ../include/parse/converters/ClassNamePatternConverter.h
    ../include/parse/converters/ColorStartPatternConverter.h
    ../include/parse/converters/ColorEndPatternConverter.h
    ../include/parse/converters/DatePatternConverter.h
    ../include/parse/converters/ShortFileLocationPatternConverter.h
    ../include/parse/converters/FileLocationPatternConverter.h
    ../include/parse/converters/FullLocationPatternConverter.h
    ../include/parse/converters/LineSeparatorPatternConverter.h
    ../include/parse/converters/MethodLocationPatternConverter.h
    ../include/parse/converters/LevelPatternConverter.h
    ../include/parse/converters/RelativeTimePatternConverter.h
    ../include/parse/converters/ThreadPatternConverter.h
    ../include/parse/converters/PropertiesPatternConverter.h
    ../include/parse/converters/LineLocationPatternConverter.h
    ../include/parse/converters/MessagePatternConverter.h
    ../include/parse/converters/PidPatternConverter.h
    ../include/logger_type.h
    ../include/LoggerConfigurator.h
    ../include/LogManager.h

    PatternLayout.cc
    LoggerInitializer.cc
    parse/LoggingEvent.cc
    parse/converters/PidPatternConverter.cc
    parse/converters/LineSeparatorPatternConverter.cc
    parse/converters/MethodLocationPatternConverter.cc
    parse/converters/LevelPatternConverter.cc
    parse/converters/RelativeTimePatternConverter.cc
    parse/converters/ThreadPatternConverter.cc
    parse/converters/PropertiesPatternConverter.cc
    parse/converters/MessagePatternConverter.cc
    parse/converters/PatternConverter.cc
    parse/converters/LiteralPatternConverter.cc
    parse/converters/LoggerPatternConverter.cc
    parse/converters/ClassNamePatternConverter.cc
    parse/converters/ColorStartPatternConverter.cc
    parse/converters/ColorEndPatternConverter.cc
    parse/converters/DatePatternConverter.cc
    parse/converters/ShortFileLocationPatternConverter.cc
    parse/converters/FileLocationPatternConverter.cc
    parse/converters/FullLocationPatternConverter.cc
    parse/converters/LineLocationPatternConverter.cc
    parse/FormattingInfo.cc
    parse/PatternParser.cc
    LoggerConfigurator.cc
    Logger.cc
    LogManager.cc
    )

TARGET_LINK_LIBRARIES(${project_BIN} ${project_LIBS})
SET_TARGET_PROPERTIES(${project_BIN} PROPERTIES VERSION "${APPLICATION_VERSION_MAJOR}.${APPLICATION_VERSION_MINOR}" OUTPUT_NAME ${project_BIN} CLEAN_DIRECT_OUTPUT 1)
TARGET_INCLUDE_DIRECTORIES(${project_BIN} PRIVATE ../include/src)

#INSTALL(TARGETS ${project_BIN} DESTINATION bin)
