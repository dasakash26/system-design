#include "NotificationObservable.h"
#include "INotification.h"
#include "IObserver.h"
#include <algorithm>
#include <iostream>

NotificationObservable::NotificationObservable() {}

void NotificationObservable::setNotification(INotification *notification) {
  std::cout << "[Notification Observable] new notification arrived.\n";
  currentNotification = notification;
  this->notify();
}

INotification *NotificationObservable::getNotification() {
  return currentNotification;
}

void NotificationObservable::addObserver(IObserver *observer) {
  auto it = std::find(observers.begin(), observers.end(), observer);

  if (it == observers.end()) {
    observers.push_back(observer);
    std::cout << "[Observable] new observer added. Observer Count: "
              << observers.size() << '\n';
  }
}

void NotificationObservable::removeObserver(IObserver *observer) {
  auto it = std::find(observers.begin(), observers.end(), observer);

  if (it != observers.end())
    observers.erase(it);
}

void NotificationObservable::notify() {
  std::cout << "[Notification Observable] Notifing " << observers.size()
            << " observers.\n";
  for (auto &observer : observers)
    observer->update();
}

NotificationObservable::~NotificationObservable() {}
