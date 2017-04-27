#ifndef OPTION_HPP_
# define OPTION_HPP_

# include <iostream>
# include <functional>
# include <cassert>

template<class T>
class Option {
public:
  constexpr Option() : _hasValue(false) {
  }

  constexpr Option(T value) : _value(value), _hasValue(true) {
  }

  constexpr T const& getOrElse(T const& def) const {
    return _hasValue ? _value : def;
  }

  template<class Throwable>
  constexpr T const& getOrThrow(Throwable const& e) const {
    return _hasValue ? _value : throw e;
  }

  constexpr operator bool() const {
    return _hasValue;
  }

  constexpr bool operator!() const {
    return !_hasValue;
  }

  T& operator*() {
    assert(_hasValue);
    return _value;
  }

  T *operator->() {
    assert(_hasValue);
    return &_value;
  }

  T const& operator*() const {
    assert(_hasValue);
    return _value;
  }

  T const *operator->() const {
    assert(_hasValue);
    return &_value;
  }

  template<class F>
  constexpr auto fmap(F f) {
    using U = decltype(f(this->_value));

    if (_hasValue) {
      return Option<U>(f(_value));
    }

    return Option<U>();
  }

  void foreach(std::function<void (T)> f) const {
    if (_hasValue) {
      f(_value);
    }
  }

private:
  T _value;
  bool _hasValue;
};

#endif /* !OPTION_HPP_ */
