#include "NotificationService.h"
#include "INotification.h"
#include "NotificationObservable.h"
#include <iostream>

NotificationService *NotificationService::instance = nullptr;

NotificationService::NotificationService() {
  observable = new NotificationObservable();
}

NotificationService *NotificationService::getInstance() {
  if (instance == nullptr) {
    std::cout << "Notification Service Instanciated\n";
    return instance = new NotificationService();
  }
  return instance;
}

NotificationObservable *NotificationService::getObservable() {
  return this->observable;
}

void NotificationService::sendNotification(INotification *notification) {
  history.push_back(notification);
  observable->setNotification(notification);
}

NotificationService::~NotificationService() {
  delete observable;
  for (auto &msg : history)
    delete msg;
}
