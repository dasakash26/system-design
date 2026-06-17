#ifndef INOTIFICATION_H
#define INOTIFICATION_H

#include <string>

class INotification {
public:
  virtual ~INotification() = default;
  virtual std::string getContent() = 0;
};

#endif // !INOTIFICATION_H
