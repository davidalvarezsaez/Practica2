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
    char productcode[512];
    SQLCHAR quantityinstock[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    printf("Insert productcode to show stock > ");
    fflush(stdout);
    while (fgets(productcode, sizeof(productcode), stdin) != NULL) {
        char query[512];
        sprintf(query, "SELECT p.quantityinstock FROM products p WHERE p.productcode = '%s';", productcode);
	printf("%s \n", query); /*comprueba el funcionamiento de la consulta*/

        SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        SQLBindCol(stmt, 1, SQL_C_CHAR, &quantityinstock, sizeof(quantityinstock), NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Quantity in stock = %s\n", quantityinstock);
        }

        SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

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

