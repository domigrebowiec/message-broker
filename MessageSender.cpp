#include "MessageSender.hpp"

MessageSender::MessageSender(QueueManager *qm, SerialPortMock *spm) : queueManager(qm), serialPortMock(spm) { }

void MessageSender::execute(){

    while (true) {
        std::cout << "MessageSender::execute get message from queue" << std::endl;
        Message msg = queueManager->popMessage();
        std::cout << "MessageSender::execute send message [" << msg.shortAddress << "=" << msg.text << "]" << std::endl;
        serialPortMock->sendMessage(msg);

        Message response = serialPortMock->receiveMessage();
        std::cout << "MessageSender::execute response received [" << response.shortAddress << "=" << response.text << "]" << std::endl;

        // TODO store in data storage
    }

}
