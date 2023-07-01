#include <iostream>
#include <memory>
#include <vector>

#include "Element.h"
#include "ElementFactory.h"
#include "MyFilter.h"
#include "MyDerivedFilter.h"
#include "MyInput.h"

int main(int argc, char** argv) {
  //
  std::shared_ptr<MyFilter> filter_sp_a = MyFilter::Create(),
                            filter_sp_b = MyFilter::Create(),
                            filter_sp_c = MyFilter::Create();
  std::shared_ptr<MyInput> input_sp_d = MyInput::Create(),
                           input_sp_e = MyInput::Create(),
                           input_sp_f = MyInput::Create();
  std::cout << "Test 1: Automatically cast derived class shared pointers to base class shared pointer" << std::endl;
  filter_sp_a->Chain(input_sp_d)->Chain(filter_sp_c);
  std::cout << "Test 1 is done" << std::endl;
  std::cout << "Test 2: Perfect forwarding with move constructors" << std::endl;
  std::string x = "str x", y = "str y";
  ElementSP::test(y);
  std::cout << "Value of y after 'test' call: '" << y << "'" << std::endl;
  ElementSP::test(std::move(x));
  std::cout << "2: Value of x after 'test' call: '" << x << "'" << std::endl;
  std::cout << "Test 2 is done" << std::endl;

  std::cout << "Test 3: Use factory to create elements" << std::endl;
  ConfigDictionary test;
  auto filter_factory_gen = ElementFactory::Create("MyFilter", test);
  auto input_factory_gen = ElementFactory::Create("MyInput", test);
  // See if this syntax also works
  ElementSP filter_sp_casted_to_element_sp = filter_sp_a;
  filter_factory_gen->Chain(input_factory_gen)
      ->Chain(filter_sp_a)
      ->Chain(filter_sp_casted_to_element_sp);
  filter_sp_casted_to_element_sp->Configure(test);
  std::cout << "Test 3 is done" << std::endl;
  std::cout << "Test 4: Derived element test" << std::endl;
  ConfigDictionary a, b, c;
  a.settings["name"] = "a";
  b.settings["name"] = "b";
  c.settings["name"] = "c";
  std::shared_ptr<MyDerivedFilter> derived_filter_sp_a = MyDerivedFilter::Create(a);
  ElementSP derived_filter_sp_b = MyDerivedFilter::Create(b);
  ElementSP derived_filter_sp_c = ElementFactory::Create("MyDerivedFilter", c);
  derived_filter_sp_a->Chain(derived_filter_sp_b)->Chain(derived_filter_sp_c)->Chain(derived_filter_sp_a);
  std::cout << "Test 4 is done" << std::endl;
  std::cout << "Test 5: std::make_shared(), shared_from_this() reference count test" << std::endl;
  std::shared_ptr<MyFilter> filter_sp_5 = MyFilter::Create();
  std::cout << "Reference count: " << filter_sp_5.use_count() << std::endl;
  std::cout << "Creating shared pointer with shared_from_this" << std::endl;
  auto filter_sp_5_shared_from_this = filter_sp_5->ptr();
  std::cout << "Reference count: " << filter_sp_5.use_count() << std::endl;
  std::cout << "Reference count shared from this: " << filter_sp_5_shared_from_this.use_count() << std::endl;
  std::cout << "Resetting filter_sp_5" << std::endl;
  filter_sp_5.reset();
  std::cout << "Reference count: " << filter_sp_5.use_count() << std::endl;
  std::cout << "Reference count shared from this: " << filter_sp_5_shared_from_this.use_count() << std::endl;
  std::cout << "Test 5 is done" << std::endl;
  // Skip the performance test if no one asks for it
  if (argc == 1) return 0;
  std::cout << "Test Infinity: Performance test" << std::endl;
  for (int i = 0; i < 1000000; i++) {
    std::shared_ptr<MyFilter> filter_sp_a = MyFilter::Create(),
                              filter_sp_b = MyFilter::Create(),
                              filter_sp_c = MyFilter::Create();
    ElementSP filter_sp_casted_to_element_sp = filter_sp_a;
    filter_factory_gen->Chain(input_factory_gen)
        ->Chain(filter_sp_a)
        ->Chain(filter_sp_casted_to_element_sp);
  }
  std::cout << "Test Infinity is done" << std::endl;
  return 0;
}