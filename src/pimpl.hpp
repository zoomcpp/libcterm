#ifndef pimpl_h__20131019_1211_20
#define pimpl_h__20131019_1211_20

#include <memory>
#include "make_unique.hpp"

template<class T>
class pimpl {
  public:
    typedef T private_struct_type;
    pimpl() : impl_(make_unique<private_struct_type>()) {
    }

    template<class... U>
    pimpl(U&&... u) : impl_(make_unique<private_struct_type>(std::forward<U>(u)...)) {
      }

    ~pimpl() {
    }

    pimpl(pimpl& p) : impl_(make_unique<private_struct_type>(p)) {
    }
    
    pimpl& operator=(const pimpl& rhs) {
      *(impl_.get()) = *(rhs.get());
    }

    private_struct_type* operator->() const {
      return impl_.get();
    }

    pimpl(pimpl&& p) : impl_(std::move(p.impl_)) {
    }

    pimpl& operator=(pimpl&& rhs) {
      impl_ = std::move(rhs.impl_);
    }

    private_struct_type* operator*() const {
      return impl_.get();
    }
  private:
    std::unique_ptr<private_struct_type> impl_;
};


#endif//pimpl_h__20131019_1211_20
