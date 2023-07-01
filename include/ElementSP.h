#pragma once

#include <memory>
class Element;

class ElementSP : public std::shared_ptr<Element> {
 public:
  ElementSP(Element* element) : std::shared_ptr<Element>(element){};

  // Required constructor for shared pointer casting
  template <typename Type>
  ElementSP(Type&& element)
      : std::shared_ptr<Element>(std::dynamic_pointer_cast<Element>(element)){};

  /**
   * TODO Move this to another branch
   * @brief Perfect forwarding and move constructor test
   *
   * @tparam Type
   * @param element
   */
  template <typename Type>
  static void test(Type&& element) {
    std::cout << "Inside 1: " << element << std::endl;
    std::string none = std::forward<Type>(element);
    std::cout << "Inside 2: " << element << std::endl;
  };
};
