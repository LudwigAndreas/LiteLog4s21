FILE (GLOB_RECURSE test_SRCS
    main.cc
    logger_test.cc
    pattern_parser_test.cc
    )

FILE (GLOB_RECURSE project_SRCS
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

    ../src/PatternLayout.cc
    ../src/LoggerInitializer.cc
    ../src/parse/LoggingEvent.cc
    ../src/parse/converters/PidPatternConverter.cc
    ../src/parse/converters/LineSeparatorPatternConverter.cc
    ../src/parse/converters/MethodLocationPatternConverter.cc
    ../src/parse/converters/LevelPatternConverter.cc
    ../src/parse/converters/RelativeTimePatternConverter.cc
    ../src/parse/converters/ThreadPatternConverter.cc
    ../src/parse/converters/PropertiesPatternConverter.cc
    ../src/parse/converters/MessagePatternConverter.cc
    ../src/parse/converters/PatternConverter.cc
    ../src/parse/converters/LiteralPatternConverter.cc
    ../src/parse/converters/LoggerPatternConverter.cc
    ../src/parse/converters/ClassNamePatternConverter.cc
    ../src/parse/converters/ColorStartPatternConverter.cc
    ../src/parse/converters/ColorEndPatternConverter.cc
    ../src/parse/converters/DatePatternConverter.cc
    ../src/parse/converters/ShortFileLocationPatternConverter.cc
    ../src/parse/converters/FileLocationPatternConverter.cc
    ../src/parse/converters/FullLocationPatternConverter.cc
    ../src/parse/converters/LineLocationPatternConverter.cc
    ../src/parse/FormattingInfo.cc
    ../src/parse/PatternParser.cc
    ../src/LoggerConfigurator.cc
    ../src/Logger.cc
    ../src/LogManager.cc
    )

INCLUDE_DIRECTORIES(${MAINFOLDER}/include)

SET (test_LIBS ${GTest_Library})

SET (test_BIN ${PROJECT_NAME}-unittests)

ADD_EXECUTABLE(${test_BIN} ${project_SRCS}
    main.cc
    logger_test.cc
    pattern_parser_test.cc
    )

TARGET_LINK_LIBRARIES(${test_BIN} ${test_LIBS})
TARGET_INCLUDE_DIRECTORIES(${test_BIN} PRIVATE .)

ADD_CUSTOM_TARGET(check ALL "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS} ${project_SRCS})
ADD_CUSTOM_TARGET(test "${MAINFOLDER}/bin/${test_BIN}" DEPENDS ${test_BIN} COMMENT "Executing unit tests..." VERBATIM SOURCES ${test_SRCS} ${project_SRCS})

INSTALL(TARGETS ${test_bin} DESTINATION bin)