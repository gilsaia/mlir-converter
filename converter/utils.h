#ifndef CONVERTER_UTILS
#define CONVERTER_UTILS
#include <stdexcept>

class NotImplemented : public std::logic_error {
public:
  NotImplemented() : std::logic_error("Function not yet implemented."){};
};

class NotWithPython : public std::logic_error {
public:
  NotWithPython() : std::logic_error("Converter is not built with python."){};
};

#endif