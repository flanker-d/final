#ifndef SESSIONS_VECTOR_H
#define SESSIONS_VECTOR_H

#include "data_types.h"
#include "client_session.h"
#include <mutex>

#include <fcntl.h>

class client_session;

class sessions_vector
{
public:
  sessions_vector()
  {
  }
  ~sessions_vector()
  {
    std::lock_guard<std::mutex> lk(mutex_);
    sessions_.clear();
  }
  void add_to_vector(std::shared_ptr<client_session> sess)
  {
    std::lock_guard<std::mutex> lk(mutex_);
    sessions_.push_back(sess);
  }
  void erase_from_vector(std::shared_ptr<client_session> sess)
  {
    std::lock_guard<std::mutex> lk(mutex_);
    auto it = std::find(sessions_.begin(), sessions_.end(), sess);
    if(it != sessions_.end())
      sessions_.erase(it);
  }

private:
  std::vector<std::shared_ptr<client_session>> sessions_;
  std::mutex mutex_;
};

#endif // SESSIONS_VECTOR_H
