#pragma once

#include <map>
#include <memory>

#include "ElementSP.h"

typedef struct ConfigDictionary {
  std::map<std::string, std::string> settings;
} ConfigDictionary;

class Element : public std::enable_shared_from_this<Element> {
 public:
  virtual ElementSP Chain(ElementSP element) {
    this->SayMyName();
    element->SayMyName();
    return element;
  }
  virtual void SayMyName() { std::cout << "My name is: Element" << std::endl; }

  std::shared_ptr<Element> ptr() { return shared_from_this(); }

  virtual bool Configure(ConfigDictionary&& dict) {
    std::cerr
        << "Element base method is called. Make sure you override this method."
        << std::endl;
    return false;
  };

  virtual bool Configure(ConfigDictionary& dict) {
    std::cerr
        << "Element base method is called. Make sure you override this method."
        << std::endl;
    return false;
  };
};
