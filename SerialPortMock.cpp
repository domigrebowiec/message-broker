#include "SerialPortMock.hpp"

void SerialPortMock::sendMessage(Message message) {

    std::cout << "Message sent over serial port to [" << message.shortAddress << "] with text [" << message.text << "]" << std::endl;
    messages.push_back(std::move(message));
}

Message SerialPortMock::receiveMessage() {
    Message m = messages.front();
    messages.erase(messages.begin());
    m.text += " response";
    return m;
}
