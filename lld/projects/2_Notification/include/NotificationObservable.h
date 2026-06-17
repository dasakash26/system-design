#ifndef NOTIFICATION_OBSERVABLE_H
#define NOTIFICATION_OBSERVABLE_H

#include "IObservable.h"
#include <vector>

class IObserver;
class INotification;

class NotificationObservable : public IObservable {
  std::vector<IObserver *> observers;
  INotification *currentNotification;

public:
  NotificationObservable();
  void setNotification(INotification *notification);
  INotification *getNotification();
  void addObserver(IObserver *observer) override;
  void removeObserver(IObserver *observer) override;
  void notify() override;
  ~NotificationObservable();
};

#endif // !NOTIFICATION_OBSERVABLE_H
