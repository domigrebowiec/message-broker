CXXFLAGS =	-O2 -g -std=c++0x -pthread -Wall -fmessage-length=0

OBJS =		main_queue.o Message.o MessageSender.o QueueManager.o ScheduledMessagesManager.o SerialPortMock.o StorageManager.o UserInterface.o

LIBS =

TARGET =	prototype_radix

$(TARGET):	$(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
