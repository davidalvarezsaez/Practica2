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
    #define BufferLength 254
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

    ret = SQLPrepare(stmt, (SQLCHAR*) "SELECT p.quantityinstock FROM products p WHERE p.productcode = ?", SQL_NTS);
    if (!SQL_SUCCEEDED(ret)) {
        odbc_extract_error("", stmt, SQL_HANDLE_ENV);
        return ret;
    }

    printf("Enter productcode > ");
    (void) fflush(stdout);
    while (scanf("%s", productcode) != EOF){
        (void) SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, productcode, 0, NULL);

        (void) SQLExecute(stmt);

        (void) SQLBindCol(stmt, 1, SQL_C_SLONG, (SQLINTEGER *) &y, 0, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf(" %d\n", y);
}

        (void) SQLCloseCursor(stmt);

        printf("Enter productcode > ");
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
    #define BufferLength 254
    char productname[BufferLength] = "\0"; /*lo que escribe el ususario*/
    char name[BufferLength] = "\0", query[BufferLength] = "\0";

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle*/
    ret = SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);


    printf("Enter productname > ");
    (void) fflush(stdout);
    while (scanf("%s", productname) != EOF) {
        (void) sprintf(query, "SELECT p.productcode, p.productname FROM products p WHERE p.productname LIKE '%%%s%%' order by p.productcode;", productname);

        (void) SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        (void) SQLBindCol(stmt, 1, SQL_C_CHAR,(SQLCHAR *) name, BufferLength, NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf(" %s\n", name);
        }

        (void) SQLCloseCursor(stmt);

        printf("Enter productname > ");
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

