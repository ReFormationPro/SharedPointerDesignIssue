#pragma once

#include <iostream>
#include <memory>

#include "Element.h"
#include "ElementFactory.h"

class MyInput : public Element, public RegisteredInFactory<MyInput> {
 public:
  void SayMyName() override { std::cout << "My name is: MyInput" << std::endl; }

  // Methods needed by element factory
  // TODO Remove
  static std::string GetFactoryName() { return "MyInput"; }

  static std::shared_ptr<MyInput> Create() {
    return std::make_shared<MyInput>();
  }

  bool Configure(ConfigDictionary&& dict) override {
    std::cerr << "MyInput configure." << std::endl;
    return false;
  };

  bool Configure(ConfigDictionary& dict) override {
    std::cerr << "MyInput configure." << std::endl;
    return false;
  };
};
