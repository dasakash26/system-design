#ifndef INOTIFICATION_STRATEGY_H
#define INOTIFICATION_STRATEGY_H

#include "INotification.h"

class INotificationStrategy {
public:
  virtual ~INotificationStrategy() = default;
  virtual void sendNotification(INotification *notification) = 0;
};

#endif // !INOTIFICATION_STRATEGY_H
