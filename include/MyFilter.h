#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

#include "Element.h"
#include "ElementFactory.h"

class MyFilter : public Element, public RegisteredInFactory<MyFilter> {
 public:
  void SayMyName() override {
    ElementSP test = ptr();
    std::cout << "My name is: MyFilter" << std::endl;
  }

  // Methods needed by element factory
  static std::string GetFactoryName() { return "MyFilter"; }

  static std::shared_ptr<MyFilter> Create() {
    return std::make_shared<MyFilter>();
  }

  bool Configure(ConfigDictionary&& dict) override {
    std::cerr << "MyFilter configure." << std::endl;
    return false;
  };

  bool Configure(ConfigDictionary& dict) override {
    std::cerr << "MyFilter configure." << std::endl;
    return false;
  };
};
