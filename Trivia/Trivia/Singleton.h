#pragma once

#include <functional>
#include <utility>

template<class subclass, class... superclasses>
class Singleton : public superclasses...
{
protected:
    // Constructors & Destructors
    Singleton() = default;
    
    virtual ~Singleton() = default;

public:
    Singleton(const Singleton&) = delete;
    Singleton& operator=(Singleton& singleton) // Operator overloading
    {
        return singleton;
    }

    template<class... Args>
    static subclass& getInstance(Args... arguments) // Getting instance
    {
        static subclass singleton{ std::forward<Args>(arguments)... };

        return singleton;
    }

};