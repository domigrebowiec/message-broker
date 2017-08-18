#ifndef MESSAGE_H
#define MESSAGE_H

#include <cstdint>
#include <string>

class Message {
public:
    Message(uint64_t sa, std::string t) : shortAddress(sa), text(t) { }
    uint64_t shortAddress;
    std::string text;
};

#endif
