#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#include "customers.h"


int customers_find(){ return EXIT_SUCCESS;}

int customers_list_products(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    int customernumber = 0;
    char result[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    ret = SQLPrepare(stmt, (SQLCHAR*) "select p.productname, sum(o1.quantityordered) as result from customers c, products p, orderdetails o1, orders o where c.customernumber = o.customernumber and c.customernumber = ? and o1.productcode = p.productcode and o.ordernumber = o1.ordernumber group by p.productname, p.productcode order by p.productcode", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }



    printf("Enter customer number to print products > ");
    (void) fflush(stdout);
    while (scanf("%d", &customernumber) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
        
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR *) result, sizeof(result), NULL);

        /* Loop through the rows in the result-set */       
	while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Products = %s\n", result);
        }  

        (void) SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Enter customer number to print products > ");
        (void) fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

int customers_balance(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt= NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    int customernumber = 0;
    int result = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "select (pa-pr) as balance from(select c1.customernumber, sum(p.amount) as pa from customers c1, payments p where c1.customernumber = p.customernumber group by c1.customernumber)as p1 join(select c2.customernumber, sum(od.priceeach*od.quantityordered) as pr from customers c2, orders o, orderdetails od where c2.customernumber=? and c2.customernumber=o.customernumber and o.ordernumber=od.ordernumber group by c2.customernumber)as p2 on p1.customernumber=p2.customernumber", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter customer number to check balance > ");
    (void) fflush(stdout);
    while (scanf("%d", &customernumber) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
        
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, (SQLINTEGER *) &result, sizeof(result), NULL);

        /* Loop through the rows in the result-set */       
	while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Balance %d\n", result);
        }  

        (void) SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Enter customer number to check balance > ");
        (void) fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}
