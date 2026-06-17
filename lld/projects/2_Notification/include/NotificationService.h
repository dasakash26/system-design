#ifndef NOTIFICATION_SERVICE
#define NOTIFICATION_SERVICE

#include <vector>

class INotification;
class NotificationObservable;

class NotificationService {
  static NotificationService *instance;
  NotificationObservable *observable;
  std::vector<INotification *> history;

  NotificationService();

public:
  ~NotificationService();
  static NotificationService *getInstance();
  NotificationObservable *getObservable();
  void sendNotification(INotification *notification);
};

#endif // !NOTIFICATION_SERVICE
