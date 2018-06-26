#pragma once

#include <boost/core/noncopyable.hpp>

namespace util {
    
    template <class T>
    class Singleton : public boost::noncopyable
    {
    public:
        static T& instance();

    protected:
        Singleton() = default;
        ~Singleton() = default;
    };

    template <class T>
    T& Singleton<T>::instance() {
        static T instanceOfClassT;
        return instanceOfClassT;
    }

}
