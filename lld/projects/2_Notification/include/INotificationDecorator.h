#ifndef INOTIFICATION_DECORATOR_H
#define INOTIFICATION_DECORATOR_H

#include "INotification.h"

class INotificationDecorator : public INotification {
protected:
  INotification *wrappedNotification;

public:
  INotificationDecorator(INotification *base) : wrappedNotification(base) {}
  ~INotificationDecorator() { delete wrappedNotification; }
  std::string getContent() override = 0;
};

#endif // INOTIFICATION_DECORATOR_H
