#include <thread>
#include <iostream>
#include <functional>

#include "MessageSender.hpp"
#include "QueueManager.hpp"
#include "ScheduledMessagesManager.hpp"
#include "UserInterface.hpp"

void task1(ScheduledMessagesManager &smm) {
	smm.execute();
}

void task2(UserInterface &ui) {
	ui.execute();
}

void task3(MessageSender &ms) {
	ms.execute();
}

int main(){

    QueueManager queueManager;
    ScheduledMessagesManager smm(&queueManager);
    UserInterface ui(&queueManager);
    SerialPortMock serialPortMock;
    MessageSender ms(&queueManager, &serialPortMock);

    std::cout << "main start " << std::endl;
    std::thread t1(task1, std::ref(smm));
    std::thread t2(task2, std::ref(ui));
    std::thread t3(task3, std::ref(ms));

    t1.join();
    t2.join();
    t3.join();
    
    std::cout << "main finish" << std::endl;
}
