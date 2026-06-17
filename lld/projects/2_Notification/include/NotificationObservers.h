#ifndef NOTIFICATION_OBSERVERS_H
#define NOTIFICATION_OBSERVERS_H

#include "IObserver.h"
#include <vector>

class NotificationObservable;
class INotificationStrategy;

class NotificationEngine : public IObserver {
  NotificationObservable *observable;
  std::vector<INotificationStrategy *> strategies;

public:
  explicit NotificationEngine();
  void update() override;
  void addStrategy(INotificationStrategy *strategy);
  ~NotificationEngine();
};

class Logger : public IObserver {
  NotificationObservable *observable;

public:
  explicit Logger();
  void update() override;
  void addStrategy(INotificationStrategy *strategy);
};

#endif // !NOTIFICATION_OBSERVERS_H
