/**
 * @file menu.c
 * @author David Alvarez Saez
 * @date 03 November 2020
 * @brief File containing an example of a menu system with submenus
 *
 * The following program allows a user to select a nursery rhyme
 * or a fairy tail from a menu. The menu has two levels, the top
 * one allows to select between fairy tails or nursery rhymes. The
 * second level (sub-menus) allow to select either a particular
 * rhyme or tail.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "products.h"
#include "orders.h"
#include "customers.h"


/* Prototypes*/
int ShowMainMenu();
void ShowProductsMenu();
int ShowProductsSubMenu();
void ShowOrdersMenu();
int ShowOrdersSubMenu();
void ShowCustomersMenu();
int ShowCustomersSubMenu();


/**
 * @brief Entry point, shows and process main menu.
 *
 * This function implements a loop that prints the main
 * menu, analyze the user selection and calls the
 * corresponding submenu
 *
 * @return 0 if no error
 * @author David Alvarez Saez
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

            case 4:
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
 * @author David Alvarez Saez
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
 * @author David Alvarez Saez
 */

void ShowProductsMenu() {
    int nChoice = 0;
    do {
        nChoice = ShowProductsSubMenu();
        switch (nChoice) {

            case 1: {
                (void) products_stock();
            }
                break;

            case 2: {
                (void)products_find();
            }
                break;

            case 3:
                break;
        }
    } while (nChoice != 3);

}

/**
 * @brief prints rhyme menu and allows to select an option.
 *
 * @return selected option
 * @author David Alvarez Saez
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
            printf("***%d***You have entered an invalid choice. Please try again\n\n\n", nSelected);
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
 * @author David Alvarez Saez
 */

void ShowOrdersMenu() {
    int nChoice = 0;

    do {
        nChoice = ShowOrdersSubMenu();
        switch (nChoice) {
            case 1: {
                (void) orders_open();
            }
                break;

            case 2: {
                (void) orders_range();
            }
                break;

            case 3: {
                (void) orders_detail();
            }
                break;

            case 4:
                break;
        }
    } while (nChoice != 4);

}

/**
 * @brief prints the fairy menu and allows to select an option.
 *
 * @return selected option
 * @author David Alvarez Saez
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
 * @author David Alvarez Saez
 */

void ShowCustomersMenu() {
    int nChoice = 0;
    char buf[16];

    do {

    do {

        printf(" (1) Find\n"
               " (2) List Products\n"
               " (3) Balance\n"
               " (4) Back\n\n");

        printf("Enter a number that corresponds to your choice > ");
        if (!fgets(buf, 16, stdin))
            /* reading input failed, give up: */
            nChoice =0;
        else
            /* have some input, convert it to integer: */
            nChoice = atoi(buf);
        printf("\n");

        if ((nChoice < 1) || (nChoice > 4)) {
            printf("You have entered an invalid choice. Please try again\n\n\n");
        }
    } while ((nChoice < 1) || (nChoice > 4));

        switch (nChoice) {
            case 1: {
                (void) customers_find();
            }
                break;

            case 2: {
                (void) customers_list_products();
            }
                break;

            case 3: {
                (void) customers_balance();
            }
                break;

            case 4:
                break;
        }
    } while (nChoice != 4);

}

/**
 * @brief prints the fairy menu and allows to select an option.
 *
 * @return selected option
 * @author David Alvarez Saez
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

/*
        do {

            printf(" (1) Find\n"
                   " (2) List Products\n"
                   " (3) Balance\n"
                   " (4) Back\n\n");

            printf("Enter a number that corresponds to your choice > ");
            if (!fgets(buf, 16, stdin))
                /* reading input failed, give up: */
/*                nChoice =0;
            else
                /* have some input, convert it to integer: */
/*                nChoice = atoi(buf);
            printf("\n");
    
            if ((nChoice < 1) || (nChoice > 4)) {
                printf("You have entered an invalid choice. Please try again\n\n\n");
            }
        } while ((nChoice < 1) || (nChoice > 4));
*/
