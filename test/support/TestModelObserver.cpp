#include "TestModelObserver.h"

bool TestModelObserver::hasWillChangeValueBeenFiredForKey(const std::string & key) const
{
  return (_keysOfWillChangeValue.find(key) != _keysOfWillChangeValue.end());
}

bool TestModelObserver::hasDidChangeValueBeenFiredForKey(const std::string & key) const
{
  return (_keysOfDidChangeValue.find(key) != _keysOfDidChangeValue.end());
}

void TestModelObserver::willChangeValueForKey(const std::string & key)
{
  _keysOfWillChangeValue.insert(key);
}

void TestModelObserver::didChangeValueForKey(const std::string & key)
{
  _keysOfDidChangeValue.insert(key);
}
