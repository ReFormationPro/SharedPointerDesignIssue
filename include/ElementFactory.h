#pragma once

#include <iostream>
#include <map>
#include <memory>
#include <stdexcept>
#include <string>
#include <utility>

#include "Element.h"
#include "ElementSP.h"

/**
 * @brief Element to be registered needs to have virtual Configure method,
 * static GetFactoryName and static Create methods are required.
 */
class ElementFactory {
 public:
  using CreateMethodFunction = ElementSP (*)();
  using CreateMethodMap = std::map<std::string, CreateMethodFunction>;

 public:
  ElementFactory() = delete;

  static CreateMethodMap& map() {
    static CreateMethodMap static_map =
        std::map<std::string, CreateMethodFunction>();
    return static_map;
  }

  static bool Register(const std::string name,
                       CreateMethodFunction create_function) {
    std::cerr << "Registering '" << name << "'" << std::endl;
    ElementFactory::map()[name] = create_function;
    return true;
  }

  static ElementSP Create(const std::string name) {
    CreateMethodMap& map = ElementFactory::map();
    auto&& create_method = map.find(name);
    if (create_method == map.end()) {
      std::cerr << "Element with name '" << name << "' was not found!"
                << std::endl;
      return ElementSP((Element*)nullptr);
    }
    ElementSP ptr = create_method->second();
    return ptr;
  }

  template <class T>
  static ElementSP Create(const std::string name, T&& dict) {
    ElementSP ptr = Create(name);
    ptr->Configure(std::forward<T>(dict));
    return ptr;
  }
};

template <typename T>
class RegisteredInFactory {
 protected:
  // Needed for self-registeration
  static bool registered_;
  RegisteredInFactory() {
    // Do not let it get optimized out by the compiler
    registered_;
  }

 public:
  static std::shared_ptr<T> Create() { return std::make_shared<T>(); }
  // Implement the following in the derived class
  /*
  static std::string GetFactoryName() {
    throw std::runtime_error("Not implemented");
  }
  */
};

// Since our elements may inherit from an element registered in factory, we need
// to fix the ambiguity among Create methods. So we use
// "RegisteredInFactory<T>::Create"
template <typename T>
bool RegisteredInFactory<T>::registered_ =
    ElementFactory::Register(T::GetFactoryName(), []() -> ElementSP {
      return RegisteredInFactory<T>::Create();
    });
