#ifndef _MYSQL_WRAPPER_H_
#define _MYSQL_WRAPPER_H_

#include <string>
#include <mysql/mysql.h>
#include "abstract_db.h"

class mysql_wrapper : public abstract_db {
  mysql_wrapper(const std::string &dir, const std::string &db);
  ~mysql_wrapper();

  virtual void thread_init();
  virtual void thread_end();

  virtual void *new_txn();
  virtual bool commit_txn(void *txn);
  virtual void abort_txn(void *txn);

  virtual bool get(
      void *txn,
      const char *key, size_t keylen,
      char *&value, size_t &valuelen);

  virtual void put(
      void *txn,
      const char *key, size_t keylen,
      const char *value, size_t valuelen);

private:
  std::string db;
  MYSQL *new_connection();
  static __thread MYSQL *tl_conn;
};

#endif /* _MYSQL_WRAPPER_H_ */
