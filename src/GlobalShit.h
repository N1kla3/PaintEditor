//
// Created by kolya on 10/1/2021.
//

#pragma once

#include <iostream>

class MainWindow;

#ifdef _DEBUG
    #define VERBOSE(...) std::cout << __func__ << ": "; Editor::print(__VA_ARGS__)
#else
    #define VERBOSE(...)
#endif

namespace Editor
{
#ifdef _DEBUG
    template <typename... Args>
    void print(Args&&... args)
    {
        ((std::cout << ' ' << std::forward<Args>(args)), ...);
        std::cout << "\n";
    }
#endif
}

