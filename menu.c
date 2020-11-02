#include <stdio.h>
#include <stdlib.h>
#include "odbc.h"
#include "products.h"

/* #include "menu_template.h" */
/* #ifndef A2BIS_MENU_TEMPLATE_H */
/* #define A2BIS_MENU_TEMPLATE_H */

/* Prototypes:
 * Since in this example this functions are not used outside menu_template
 * it does not make sense to create an include file and export them
 * BUT in your code it will make sense to break this file in many files
 * and create several include files with the prototypes
 *
 * A static function in C is a function that has a scope that is limited
 * to its object file. This means that the static function is only
 * visible in its object file. Therefore,
 * you need to remove the static keyword from the declaration
 * if the function is declared in a file and used in another
 * */

static int ShowMainMenu();
static void ShowProductsMenu();
static int ShowProductsSubMenu();
static void ShowOrdersMenu();
static int ShowOrdersSubMenu();
static void ShowCustomersMenu();
static int ShowCustomersSubMenu();
static void PrintOpen();
static void PrintRange();
static void PrintDetail();
static void PrintStock();
static void PrintFind();
static void PrintCFind();
static void PrintListProducts();
static void PrintBalance();

/* #endif //A2BIS_MENU_TEMPLATE_H */

/**
 * @file menu_template.c
 * @author rmarabini
 * @date 15 April 2020
 * @brief File containing an example of a menu system with submenus
 *
 * The following program allows a user to select a nursery rhyme
 * or a fairy tail from a menu. The menu has two levels, the top
 * one allows to select between fairy tails or nursery rhymes. The
 * second level (sub-menus) allow to select either a particular
 * rhyme or tail.
 *
 * @see https://bytes.com/topic/c/answers/567136-creating-menus-sub-menus
 */


/**
 * @brief Entry point, shows and process main menu.
 *
 * This function implements a loop that prints the main
 * menu, analyze the user selection and calls the
 * corresponding submenu
 *
 * @return 0 if no error
 * @author rmarabini
 */
int main(void) {
    int nChoice = 0;

    do {
        nChoice = ShowMainMenu();
        switch (nChoice) {
            case 1: {
                ShowProductsMenu();
            }
                break;

            case 2: {
                ShowOrdersMenu();
            }
                break;

            case 3: {
                ShowCustomersMenu();
            }
                break;

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);
    return 0;
}


/**
 * @brief prints main menu and allows to select an option.
 *
 *
 * @return selected entry in the menu
 * @author rmarabini
 */

int ShowMainMenu() {
    int nSelected = 0;
    char buf[16]; /* buffer for reading user input
                     in theory we only need 1 char
                     but a large buffer will handle
                     more gracefully wrong inputs
                     as 'qwerty' */

    do {
        printf("This is where you can find all the information about the products, orders and customers \n");

        printf(" (1) Products\n"
               " (2) Orders\n"
               " (3) Customers\n"
               " (4) Quit\n\n"
               "Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief Shows and processes the rhyme menu.
 *
 * This function implements a loop that prints the rhyme
 * menu, analyze the user selection and prints
 * the selected rhyme
 * @return void
 * @author rmarabini
 */

void ShowProductsMenu() {
    int nChoice = 0;
    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {

            case 1: {
                products_stock();
            }
                break;

            case 2: {
                PrintFind();
            }
                break;

            case 3: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 3);

}

/**
 * @brief prints rhyme menu and allows to select an option.
 *
 * @return selected option
 * @author rmarabini
 */

 int ShowProductsSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Stock\n"
               " (2) Find\n"
               " (3) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");


        if ((nSelected < 1) || (nSelected > 3)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 3));

    return nSelected;
}

/**
 * @brief Shows and processes the fairy menu.
 *
 * This function implements a loop that prints the fairy
 * menu, analyze the user selection and prints
 * the selected fairy tail
 *
 * @return selected option
 * @author rmarabini
 */

void ShowOrdersMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {
            case 1: {
                PrintOpen();
            }
                break;

            case 2: {
                PrintRange();
            }
                break;

            case 3: {
                PrintDetail();
            }
                break;

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);

}

/**
 * @brief prints the fairy menu and allows to select an option.
 *
 * @return selected option
 * @author rmarabini
 */
 int ShowOrdersSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Open\n"
               " (2) Range\n"
               " (3) Detail\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief Shows and processes the fairy menu.
 *
 * This function implements a loop that prints the fairy
 * menu, analyze the user selection and prints
 * the selected fairy tail
 *
 * @return selected option
 * @author rmarabini
 */

void ShowCustomersMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowCustomersSubMenu();
        switch (nChoice) {
            case 1: {
                PrintCFind();
            }
                break;

            case 2: {
                PrintListProducts();
            }
                break;

            case 3: {
                PrintBalance();
            }
                break;

            case 4: {
                printf("Bye Bye\n\n");
            }
                break;
        }
    } while (nChoice != 4);

}

/**
 * @brief prints the fairy menu and allows to select an option.
 *
 * @return selected option
 * @author rmarabini
 */
 int ShowCustomersSubMenu() {
    int nSelected = 0;
    char buf[16];

    do {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nSelected =0;
        else
            /* have some input, convert it to integer: */
            nSelected = atoi(buf);
        printf("\n");

        if ((nSelected < 1) || (nSelected > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nSelected < 1) || (nSelected > 4));

    return nSelected;
}

/**
 * @brief prints Rhyme Mary
 *
 * @return void
 * @author rmarabini
 *
 */
int products_stock(){
    SQLHENV env;
    SQLHDBC dbc;
    SQLHSTMT stmt;
    SQLRETURN ret; /* ODBC API return status */
    char x[512];
    SQLCHAR quantityinstock[512];

    /* CONNECT */
    ret = odbc_connect(&env, &dbc);
    if (!SQL_SUCCEEDED(ret)) {
        return EXIT_FAILURE;
    }

    /* Allocate a statement handle */
    SQLAllocHandle(SQL_HANDLE_STMT, dbc, &stmt);

    printf("Insert productcode to show stock: ");
    fflush(stdout);
    while (fgets(x, sizeof(x), stdin) != NULL) {
        char query[512];
        sprintf(query, "SELECT p.quantityinstock FROM products p WHERE p.productcode = '%s';", x);
	printf("%s \n", query); /*comprueba el funcionamiento de la consulta*/

        SQLExecDirect(stmt, (SQLCHAR*) query, SQL_NTS);

        SQLBindCol(stmt, 1, SQL_C_CHAR, quantityinstock, sizeof(quantityinstock), NULL);

        /* Loop through the rows in the result-set */
        while (SQL_SUCCEEDED(ret = SQLFetch(stmt))) {
            printf("Quantity in stock = %s\n", quantityinstock);
        }

        SQLCloseCursor(stmt); /*Limpia el contenido del contenedor*/

        printf("Insert productcode to show stock: ");
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

/**
 * @brief prints Rhyme Jack
 *
 * @return void
 * @author rmarabini
 *
 */
void PrintFind() {
    printf("el pepe\n\n\n");
}

/**
 * @brief prints Rhyme LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */
void PrintOpen() {
    printf("DEVUELVE UN LISTADO CON TODOS LOS PEDIDOS QUE TODAVÍA NO SE HAYAN ENVIADO\n\n\n");
}

/**
 * @brief prints fairy tail LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */
 void PrintRange() {
    printf("SE SOLICITAN AL USUARIO DOS FECHAS Y SE DEVUELVE UN LISTADO CON LOS PEDIDOS\n\n\n");
}

/**
 * @brief prints fairy tail LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */
void PrintDetail() {
    printf("SE SOLICITA UN ID DE PEDIDO Y SE DEVUELVE UN LISTADO CONTENIENDO LOS DETALLES DEL PEDIDO\n\n\n");
}

/**
 * @brief prints fairy tail LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */

void PrintCFind() {
    printf("SE SOLICITA UN NOMBRE DE CONTACTO...\n\n\n");
}

/**
 * @brief prints fairy tail LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */

void PrintListProducts() {
    printf("SE SOLICITA EL ID DE UN CLIENTE Y DEVUELVE LISTADO CON LOS PRODUCTOS SOLICITADOS POR EL CLIENTE...\n\n\n");
}

/**
 * @brief prints fairy tail LittleBoPee
 *
 * @return void
 * @author rmarabini
 *
 */

void PrintBalance() {
    printf("SE SOLICITA EL ID DE UN CLIENTE Y SE DEVUELVE EL SALDO DEL MISMO...\n\n\n");
}
     
