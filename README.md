# pulse-cpp
A lightweight, header-only modern C++ event library inspired by Unity's event system design.

pulse-cpp provides a simple and flexible way to bind and dispatch events using: 
- Free Functions
- Lambdas
- Class member methods

## Installation
pulse-cpp is a header only so just simply add the header file to your project and add `using namespace pulse;` or scope calls directly with `pulse::Event<type>` 

# Usage
pulse-cpp supports multiple listener binding styles depending on your use case. Examples are shown below

## Free Function

```
void helloString(std::string str) {
	std::cout << std::format("This is from the helloString function! It says: {}\n", str);
}

int main(int argc, char* argv[])
{
  pulse::Event<std::string> helloStringEvent;
  // add the listener, what gets fired when invoke() is called; in this case our free function above.
  helloStringEvent.addListener(helloString);

  // fire the event with a string
  helloStringEvent.invoke("Hello World!");
  return 0;
}
```

## Lambdas
```
int main(int argc, char* argv[])
{
  pulse::Event<std::string> helloStringEvent;
  // add the listener, what gets fired when invoke() is called; our lambda 
  helloStringEvent.addListener([](std::string s) { std::cout << std::format("This is from a lambda! It says: {}\n", s); });

  // fire the event with a string 
  helloStringEvent.invoke("Hello World!");
  return 0;
}
```

## Class Member Methods

```
int main(int argc, char* argv[])
{
  std::unique_ptr<Foo> foo   = std::make_unique<Foo>();
  pulse::Event<std::string> helloStringEvent;
  // add the listener, what gets fired when invoke() is called; our lambda 
  helloStringEvent.addListener(pulse::EventBinder::bind(foo.get(), &Foo::AddToString));

  // fire the event with a string; this now calls our bound class member method "AddToString" on the object 'foo'
  helloStringEvent.invoke("Hello World!");
  return 0;
}
```



