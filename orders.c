#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#include "orders.h"

int orders_open(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    int ordernumber = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "select o.ordernumber from orders o where o.shippeddate is NULL;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }


    (void) fflush(stdout);
     
    (void) SQLExecute(stmt);
        
    (void) SQLBindCol(stmt, 1, SQL_C_SLONG,(SQLINTEGER *) &ordernumber, 0, NULL);


    /* Loop through the rows in the result-set */
    while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
        printf(" %d\n", ordernumber);
    }

    (void) SQLCloseCursor(stmt);

    (void) fflush(stdout);
    
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

int orders_range(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    int ordernumber = 0;
    char orderdate[BufferLength] = "\0", shippeddate[BufferLength] = "\0";
    char resultorderdate[BufferLength] = "\0", resultshippeddate[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT o.ordernumber, o.orderdate, o.shippeddate FROM orders o WHERE o.orderdate >= ? AND o.orderdate <= ? ORDER BY o.ordernumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }


    printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
    (void) fflush(stdout);
    while (scanf("%s - %s", orderdate, shippeddate) != EOF) {

        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, orderdate, 0, NULL);

        (void) SQLBindParameter(stmt, 2, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, shippeddate, 0, NULL);
        
        (void) SQLExecute(stmt);
        
        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, (SQLINTEGER *) &ordernumber, 0, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR *) resultorderdate, BufferLength, NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_CHAR, (SQLCHAR *) resultshippeddate, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf(" %d %s %s\n", ordernumber, resultorderdate, resultshippeddate);
        }

        (void) SQLCloseCursor(stmt);

        printf("Enter dates (YYYY-MM-DD - YYYY-MM-DD) > ");
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



int orders_detail(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL, stmt2 = NULL;
    int ret; /* odbc.c */
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    int ordernumber = 0, quantityordered = 0;
    double priceeach = 0, total = 0;
    char orderdate[BufferLength] = "\0", status[BufferLength] = "\0", productcode[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT o.orderdate, o.status, sum(o1.quantityordered*o1.priceeach) FROM orders o join orderdetails o1 on o.ordernumber = o1.ordernumber WHERE o.ordernumber = ? GROUP BY o.orderdate, o.status;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt2);
    ret = SQLPrepare(stmt2, (SQLCHAR*) "SELECT o1.productcode, o1.quantityordered, o1.priceeach FROM orders o join orderdetails o1 on o.ordernumber = o1.ordernumber WHERE o.ordernumber = ? ORDER BY o1.orderlinenumber;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt2, SQL_HANDLE_ENV);
        return ret;
    }


    printf("Enter ordernumber > ");
    (void) fflush(stdout);
    while (scanf("%d", &ordernumber) != EOF) {

        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);
        (void) SQLBindParameter(stmt2, 1, SQL_PARAM_INPUT, SQL_C_SLONG, SQL_INTEGER, 0, 0, &ordernumber, 0, NULL);

        (void) SQLExecute(stmt);
        (void) SQLExecute(stmt2);
        
        (void) SQLBindCol(stmt, 1, SQL_C_CHAR, (SQLCHAR *) orderdate, BufferLength, NULL);
        (void) SQLBindCol(stmt, 2, SQL_C_CHAR, (SQLCHAR *) status, BufferLength, NULL);
        (void) SQLBindCol(stmt, 3, SQL_C_DOUBLE, (SQLDOUBLE *) &total, 0, NULL);

        (void) SQLBindCol(stmt2, 1, SQL_C_CHAR, (SQLCHAR *) productcode, BufferLength, NULL);
        (void) SQLBindCol(stmt2, 2, SQL_C_SLONG, (SQLINTEGER *) &quantityordered, 0, NULL);
        (void) SQLBindCol(stmt2, 3, SQL_C_DOUBLE, (SQLDOUBLE *) &priceeach, 0, NULL);

        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) 
            printf("Order Date=%s - status=%s\nTotal sum = %f\n", orderdate, status, total);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt2)))
            printf(" %s %d %.2f\n", productcode, quantityordered, priceeach);


        (void) SQLCloseCursor(stmt);
        (void) SQLCloseCursor(stmt2);

        printf("Enter ordernumber >");
        (void) fflush(stdout);
    }
    printf("\n");

    /* free up statement handle */
    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt, SQL_HANDLE_STMT);
        return ret;
    }

    ret2 = SQLFreeHandle(SQL_HANDLE_STMT, stmt2);
    if (!SQL_SUCCEEDED(ret2)) {
        odbc_extract_error("", stmt2, SQL_HANDLE_STMT);
        return ret;
    }


    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;

}

