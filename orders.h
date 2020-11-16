#ifndef ORDERS_H
#define ORDERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int orders_open();

int orders_range();

int orders_detail();

#endif /* ORDERS_H */
