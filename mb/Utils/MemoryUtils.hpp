#ifndef __MB_MEMORY_UTILS__
#define __MB_MEMORY_UTILS__

namespace mb
{
  template<typename T, typename... Args>
  static std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
}

#endif /* __MB_MEMORY_UTILS__ */
