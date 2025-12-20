#include <optional>

#ifndef GLOBAL_H
#define GLOBAL_H

#define GET_CONSTED_REF_TYPE(t) *const_cast<std::vector<t>*>
#define STABLE const noexcept

template<class _Ty, class _Fn>
void _Has_Invoke(std::optional<_Ty>&& opt, _Fn func){
    if(opt)
        func(opt.value());
}

#endif // GLOBAL_H