//
// Created by Ludwig Andreas on 26.07.2023.
//

#include "LogManager.h"

#include "Logger.h"

namespace s21::diagnostic {

std::map<String, LoggerPtr> LogManager::logger_repo_;
LoggerPtr LogManager::root = nullptr;

LoggerPtr LogManager::getLogger(const String &name) {
  if (!logger_repo_.count(name)) {
    auto logger = std::make_shared<Logger>(name);
    logger_repo_.insert({name, logger});
    if (!root){
      root = logger;
    }
    return logger;
  }
  return logger_repo_.at(name);
}

std::map<String, LoggerPtr> LogManager::GetLoggerRepo() {
  return logger_repo_;
}

LoggerPtr LogManager::getRootLogger() {
  return root;
}

}