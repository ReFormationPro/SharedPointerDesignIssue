#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "Element.h"
#include "MyFilter.h"
#include "ElementFactory.h"

class MyDerivedFilter : public MyFilter, public RegisteredInFactory<MyDerivedFilter> {
 std::string config_name_ = "";
 public:
  void SayMyName() override {
    std::cout << "My name is: MyDerivedFilter '" << config_name_ << "'" << std::endl;
  }

  // Methods needed by element factory
  static std::string GetFactoryName() { return "MyDerivedFilter"; }

  static std::shared_ptr<MyDerivedFilter> Create() {
    return std::make_shared<MyDerivedFilter>();
  }

  static std::shared_ptr<MyDerivedFilter> Create(ConfigDictionary dict) {
    auto sp = std::make_shared<MyDerivedFilter>();
    sp->Configure(dict);
    return sp;
  }

  bool Configure(ConfigDictionary&& dict) override {
    std::cerr << "MyDerivedFilter configure." << std::endl;
    config_name_ = dict.settings["name"];
    return true;
  };

  bool Configure(ConfigDictionary& dict) override {
    std::cerr << "MyDerivedFilter configure." << std::endl;
    config_name_ = dict.settings["name"];
    return true;
  };
};
