#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#include "products.h"



int products_stock(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char productcode[BufferLength] = "\0";
    int y = 0;

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT p.quantityinstock FROM products p WHERE p.productcode = ?;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    SQLPrepare(stmt, (SQLCHAR*) "SELECT p.quantityinstock FROM products p WHERE p.productcode = ?", SQL_NTS);

    printf("Insert productcode to show stock > ");
    (void) fflush(stdout);
    while (scanf("%s", productcode) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, productcode, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, (SQLINTEGER *) &y, sizeof(y), NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Quantity in stock = %d\n", y);
}

        (void) SQLCloseCursor(stmt);

        printf("Insert productcode to show stock > ");
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


int products_find(){
    SQLHENV env = NULL;
    SQLHDBC dbc = NULL;
    SQLHSTMT stmt = NULL;
    int ret;
    SQLRETURN ret2; /* ODBC API return status */
    #define BufferLength 512
    char productname[BufferLength] = "\0"; /*lo que escribe el ususario*/
    char name[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);
    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT p.productcode, p.productname FROM products p WHERE p.productname LIKE '%?%%' order by p.productcode;", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }


    printf("Insert productname to show products > ");
    (void) fflush(stdout);
    while (scanf("%s", productname) != EOF) {
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, productname, 0, NULL); 
        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *) name, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Name = %s\n", name);
        }

        (void) SQLCloseCursor(stmt);

        printf("Insert productname to show products > ");
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

