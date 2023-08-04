# Shared Pointer Design Issue

This repository presents a design achieving the following concerns described in the Medium article [here](https://medium.com/@oguzhanoztaskin/6ec4cb5d3502):
- Objects can access their own shared pointers
- Shared pointers are automatically cast if their element type is castable
- A factory can create and configure objects without prior knowledge of their specific types
- The elements are self-registering to the factory.

This is just an example and comes with no warranty.