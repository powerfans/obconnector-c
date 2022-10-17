#include <stdio.h>
#include <string.h>
#include "mysql.h"
#include "test_util.h"
#include "ob_object.h"
#include "ob_protocol20.h"
#include "ob_full_link_trace.h"

int main(int argc, char** argv) {
  mysql_library_init(0, NULL, NULL);
  MYSQL *mysql = mysql_init(NULL);
  MYSQL_RES *RES;
  unsigned int timeout = 3000;
  if (6 == argc) {
    DBHOST = argv[1];
    DBUSER = argv[2];
    DBPASS = argv[3];
    DBNAME = argv[4];
    DBPORT = atoi(argv[5]);

    printf("host is %s, user is %s, pass is %s, name is %s, port is %u\n", DBHOST, DBUSER, DBPASS, DBNAME, DBPORT);
  }

  if (mysql_real_connect(mysql, DBHOST, DBUSER, DBPASS, DBNAME, DBPORT, DBSOCK, DBPCNT) == NULL)
  {
    my_log("connect failed: %s, host:%s, port:%d, user:%s, pass:%s, dbname:%s",
      mysql_error(mysql),DBHOST, DBPORT, DBUSER, DBPASS, DBNAME);
    mysql_close(mysql);
    mysql_library_end();
    return 0;
  } else {
    my_log("connect %s:%d using %s succ", DBHOST, DBPORT, DBUSER);
  }

  {
    if (mysql_query(mysql, "select sleep(2) from dual")) {
      printf("query one error, %s\n", mysql_error(mysql));
      return 0;
    } else {
      RES = mysql_store_result(mysql);
    }
  }

  {
    if (mysql_query(mysql, "commit;")) {
      printf("query four error, %s\n", mysql_error(mysql));
      return 0;
    } else {
      RES = mysql_store_result(mysql);
    }
  }

  mysql_library_end();
  return 0;
}
