#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#include "customers.h"


int customers_find(){ 
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    int result = 0;
    char input[BufferLength] = "\0"; /*lo que escribe el ususario*/
    char firstname[BufferLength] = "\0", lastname[BufferLength] = "\0", name[BufferLength] = "\0", query[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "select c.customernumber, c.customername, c.contactfirstname, c.contactlastname from customers c where (c.contactfirstname LIKE ? ) or (c.contactlastname LIKE ? ) order by c.customernumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }


    printf("Enter customer name > ");
    (void) fflush(stdout);
    while (scanf("%s", input) != EOF) {

        sprintf(query, "select c.customernumber, c.customername, c.contactfirstname, c.contactlastname from customers c where (c.contactfirstname LIKE '%s%%' ) or (c.contactlastname LIKE '%s%%' ) order by c.customernumber;", input, input);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, (SQLINTEGER *) &result, 0, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR *) name, BufferLength, NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR *) firstname, BufferLength, NULL);
        (void) SQLBindCol(stmt, 4, SQL_C_CHAR, (SQLCHAR *) lastname, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf(" %d %s %s %s\n", result, name, firstname, lastname);
        }

        (void) SQLCloseCursor(stmt);

        printf("Enter customer name > ");
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



int customers_list_products(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    int customernumber = 0;
    int num = 0;
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



    printf("Enter customer number > ");
    (void) fflush(stdout);
    while (scanf("%d", &customernumber) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
        
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR *) result, BufferLength, NULL);

        (void) SQLBindCol(stmt, 2, SQL_C_SLONG, (SQLINTEGER *) &num, 0, NULL);

        /* Loop through the rows in the result-set */       
	while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("  %s %d\n", result, num);
        }  

        (void) SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Enter customer number > ");
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
    double result = 0;

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

    printf("Enter customer number > ");
    (void) fflush(stdout);
    while (scanf("%d", &customernumber) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &customernumber, 0, NULL);
        
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_DOUBLE, (SQLDOUBLE *) &result, 0, NULL);

        /* Loop through the rows in the result-set */       
	while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Balance = %.2f\n", result);
        }  

        (void) SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Enter customer number > ");
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
