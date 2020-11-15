#ifndef CUSTOMERS_H
#define CUSTOMERS_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"


int customers_find();

int customers_list_products();

int customers_balance();

#endif /* CUSTOMERS_H */
