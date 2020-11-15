#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sql.h>
#include <sqlext.h>
#include "odbc.h"

#include "products.h"



int products_stock(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    SQLCHAR productcode[512];
    SQLCHAR y[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    SQLPrepare(stmt, (SQLCHAR*) "SELECT p.quantityinstock FROM products p WHERE p.productcode = ?", SQL_NTS);

    printf("Insert productcode to show stock > ");
    fflush(stdout);
    while (scanf("%s", productcode) != EOF) {
        SQLBindParameter(stmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, productcode, 0, NULL);

        SQLExecute(stmt);

        SQLBindCol(stmt, 1, SQL_C_CHAR, y, sizeof(y), NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Quantity in stock = %s\n", y);
}

        SQLCloseCursor(stmt);

        printf("Insert productcode to show stock > ");
        fflush(stdout);
    }

    printf("\n");
    
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}


int products_find(){
SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    char productname[512]; /*lo que escribe el ususario*/
    SQLCHAR name[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    printf("Insert productname to show products > ");
    fflush(stdout);
    while (fgets(productname, sizeof(productname), stdin) != NULL) {
        char query[512];
        productname[strlen(productname)-1] = '\0';
        sprintf(query, "SELECT p.productcode, p.productname FROM products p WHERE p.productname = '%s' order by p.productcode;", productname);
		printf("%s \n", query); /*comprueba el funcionamiento de la consulta*/

        SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        SQLBindCol(stmt, 2, SQL_C_CHAR, name, sizeof(name), NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Name = %s\n", name);
        }

        SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Insert productname to show products > ");
        fflush(stdout);
    }
    printf("\n");
    
    /* free up statement handle */
    SQLFreeHandle(SQL_HANDLE_STMT, stmt);

    /* DISCONNECT */
    ret = odbc_disconnect(env, dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }


    return EXIT_SUCCESS;
}

