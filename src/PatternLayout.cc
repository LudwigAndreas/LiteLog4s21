//
// Created by Ludwig Andreas on 25.07.2023.
//

#include "PatternLayout.h"

#include <utility>
#include <algorithm>

#include "parse/converters/LoggerPatternConverter.h"
#include "parse/converters/ClassNamePatternConverter.h"
#include "parse/converters/ColorEndPatternConverter.h"
#include "parse/converters/ColorStartPatternConverter.h"
#include "parse/converters/DatePatternConverter.h"
#include "parse/converters/ShortFileLocationPatternConverter.h"
#include "parse/converters/FileLocationPatternConverter.h"
#include "parse/converters/FullLocationPatternConverter.h"
#include "parse/converters/LineLocationPatternConverter.h"
#include "parse/converters/MessagePatternConverter.h"
#include "parse/converters/LineSeparatorPatternConverter.h"
#include "parse/converters/MethodLocationPatternConverter.h"
#include "parse/converters/LevelPatternConverter.h"
#include "parse/converters/RelativeTimePatternConverter.h"
#include "parse/converters/ThreadPatternConverter.h"
#include "parse/converters/PropertiesPatternConverter.h"
#include "parse/converters/PidPatternConverter.h"

namespace s21::diagnostic {

PatternLayout::PatternLayout() = default;

PatternLayout::PatternLayout(String pattern) :
    conversion_pattern_(std::move(pattern)) {
  activateOptions();
}

PatternLayout::~PatternLayout() {}

PatternLayout PatternLayout::GetCopy() {
  return *this;
}

void PatternLayout::setConversionPattern(const String &conversion_pattern) {
  conversion_pattern_ = conversion_pattern;
  activateOptions();
}

String PatternLayout::getConversionPattern() const {
  return conversion_pattern_;
}

String PatternLayout::ToLowerCase(String ref) {
  std::transform(ref.begin(), ref.end(), ref.begin(), ::tolower);
  return ref;
}

void PatternLayout::setOption(const String &option, const String &value) {
  if (ToLowerCase(option) == "fatalcolor") {
    fatal_color_ = value;
  } else if (ToLowerCase(option) == "errorcolor") {
    error_color_ = value;
  } else if (ToLowerCase(option) == "warncolor") {
    warn_color_ = value;
  } else if (ToLowerCase(option) == "infocolor") {
    info_color_ = value;
  } else if (ToLowerCase(option) == "debugcolor") {
    debug_color_ = value;
  } else if (ToLowerCase(option) == "tracecolor") {
    trace_color_ = value;
  }
}

void PatternLayout::activateOptions() {
  String pat = conversion_pattern_;

  if (pat.empty()) {
    pat = String("%m%n");
  }

  pattern_converters_.erase(pattern_converters_.begin(), pattern_converters_
      .end());
  pattern_fields_.erase(pattern_fields_.begin(), pattern_fields_.end());
  parse::PatternParser::parse(pat,
                              pattern_converters_,
                              pattern_fields_,
                              getFormatSpecifiers());
}

void PatternLayout::format(String &output, const parse::LoggingEvent &event) {
  auto formatter_iter = pattern_fields_.begin();

  for (auto converter_iter = pattern_converters_.begin();
       converter_iter != pattern_converters_.end();
       converter_iter++, formatter_iter++) {
    int start_field = (int) output.length();
    (*converter_iter)->format(event, output);
    (*formatter_iter).format(start_field, output);
  }
}

s21::parse::PatternMap PatternLayout::getFormatSpecifiers() {
  s21::parse::PatternMap specs;
//
  specs.insert({"c",
                s21::parse::LoggerPatternConverter::newInstance});
  specs.insert({"logger",
                s21::parse::LoggerPatternConverter::newInstance});
//
  specs.insert({"C",
                s21::parse::ClassNamePatternConverter::newInstance});
  specs.insert({"class",
                s21::parse::ClassNamePatternConverter::newInstance});
//
  specs.insert({"Y",
                std::bind(&PatternLayout::createColorStartPatternConverter,
                          this,
                          std::placeholders::_1)});
  specs.insert({"y",
                s21::parse::ColorEndPatternConverter::newInstance});
//
  specs.insert({"d",
                s21::parse::DatePatternConverter::newInstance});
  specs.insert({"date",
                s21::parse::DatePatternConverter::newInstance});
//
  specs.insert({"f",
                s21::parse::ShortFileLocationPatternConverter::newInstance});
//
  specs.insert({"F",
                s21::parse::FileLocationPatternConverter::newInstance});
  specs.insert({"file",
                s21::parse::FileLocationPatternConverter::newInstance});
//
  specs.insert({"l",
                s21::parse::FullLocationPatternConverter::newInstance});
//
  specs.insert({"L",
                s21::parse::LineLocationPatternConverter::newInstance});
  specs.insert({"line",
                s21::parse::LineLocationPatternConverter::newInstance});
//
  specs.insert({"m",
                s21::parse::MessagePatternConverter::newInstance});
  specs.insert({"message",
                s21::parse::MessagePatternConverter::newInstance});
//
  specs.insert({"n",
                s21::parse::LineSeparatorPatternConverter::newInstance});
//
  specs.insert({"M",
                s21::parse::MethodLocationPatternConverter::newInstance});
  specs.insert({"method",
                s21::parse::MethodLocationPatternConverter::newInstance});
//
  specs.insert({"p",
                s21::parse::LevelPatternConverter::newInstance});
  specs.insert({"level",
                s21::parse::LevelPatternConverter::newInstance});
//
  specs.insert({"P",
               s21::parse::PidPatternConverter::newInstance});
  specs.insert({"pid",
               s21::parse::PidPatternConverter::newInstance});
//
  specs.insert({"r",
                s21::parse::RelativeTimePatternConverter::newInstance});
  specs.insert({"relative",
                s21::parse::RelativeTimePatternConverter::newInstance});
//
  specs.insert({"t",
                s21::parse::ThreadPatternConverter::newInstance});
  specs.insert({"thread",
                s21::parse::ThreadPatternConverter::newInstance});
//
  specs.insert({"X",
                s21::parse::PropertiesPatternConverter::newInstance});
  specs.insert({"properties",
                s21::parse::PropertiesPatternConverter::newInstance});
  return specs;
}

std::shared_ptr<s21::parse::PatternConverter> PatternLayout::createColorStartPatternConverter(
    const std::vector<String> &options) {
  (void) options;
  auto color_pattern_converter = std::make_shared<parse::ColorStartPatternConverter>();

  color_pattern_converter->SetFatalColor(fatal_color_);
  color_pattern_converter->SetErrorColor(error_color_);
  color_pattern_converter->SetWarnColor(warn_color_);
  color_pattern_converter->SetInfoColor(info_color_);
  color_pattern_converter->SetDebugColor(debug_color_);
  color_pattern_converter->SetTraceColor(trace_color_);

  return color_pattern_converter;
}
const std::vector<std::shared_ptr<parse::PatternConverter> > &PatternLayout::GetPatternConverters() const {
  return pattern_converters_;
}

}