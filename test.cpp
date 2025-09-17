#include <iostream>

using namespace std;

//=================================================
// stringify
// Create a string from a string, number, or type implementing to_string
//
// Parameters:
//  value: value to convert
//=================================================
template <typename T> string stringify(const T &value) {
  if constexpr (std::is_same_v<T, bool>) {
    if (value) {
      return "true";
    } else {
      return "false";
    }
  } else if constexpr (std::is_arithmetic_v<T>) {
    return std::to_string(value);
  } else if constexpr (std::is_same_v<T, std::string>) {
    return value;
  } else {
    return value.to_string();
  }
}

template <typename T>
void test(std::string description, const T &actual, std::string expected) {
  cout << "Running: `" << description << "`" << endl;
  if (stringify(actual) != expected) {
    cout << "FAILED: `" << description << "`" << endl;
    cout << "Expected: `" << expected << "`" << endl;
    cout << "Actual: `" << stringify(actual) << "`" << endl;

  } else {
    cout << "Successful: `" << description << "`" << endl;
  }
  cout << "------------------------------" << endl;
}
