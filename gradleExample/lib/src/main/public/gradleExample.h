/*
 * This C++ source file was generated by the Gradle 'init' task.
 */
#ifndef GRADLEEXAMPLE_H
#define GRADLEEXAMPLE_H

#ifdef _WIN32
#define GRADLEEXAMPLE_EXPORT_FUNC __declspec(dllexport)
#else
#define GRADLEEXAMPLE_EXPORT_FUNC
#endif

#include <string>

namespace gradleExample {
    class Greeter {
        public:
        std::string GRADLEEXAMPLE_EXPORT_FUNC greeting();
    };
}

#endif