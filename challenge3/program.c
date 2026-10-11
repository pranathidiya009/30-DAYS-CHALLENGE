// SMART CART BILLING SYSTEM
#include <stdio.h>

int main()
{
    float purchase, distance;
    float rate = 0, discount, amount, delivery, total;
    int customer;

    printf("Enter purchase amount: Rs. ");
    if (scanf("%f", &purchase) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Customer type (1-Student, 2-Regular): ");
    if (scanf("%d", &customer) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    printf("Enter delivery distance (km): ");
    if (scanf("%f", &distance) != 1)
    {
        printf("Invalid input!\n");
        return 1;
    }

    if (purchase < 0 || distance < 0)
    {
        printf("Invalid amount or distance!\n");
        return 1;
    }

    switch (customer)
    {
        case 1:
            if (purchase >= 2000)
                rate = 15;
            else
                rate = 10;
            break;

        case 2:
            if (purchase >= 3000)
                rate = 8;
            else
                rate = 0;
            break;

        default:
            printf("Invalid customer type!\n");
            return 1;
    }

    discount = purchase * rate / 100;
    amount = purchase - discount;

    if (distance <= 5)
        delivery = 40;
    else if (distance <= 15)
        delivery = 70;
    else
        delivery = 100;

    total = amount + delivery;

    printf("\n===== SMART CART BILL =====\n");
    printf("Purchase Amount : Rs. %.2f\n", purchase);
    printf("Customer Type   : %s\n",
           customer == 1 ? "Student" : "Regular");
    printf("Discount Rate   : %.0f%%\n", rate);
    printf("Discount Amount : Rs. %.2f\n", discount);
    printf("After Discount  : Rs. %.2f\n", amount);
    printf("Delivery Charge : Rs. %.2f\n", delivery);
    printf("---------------------------\n");
    printf("Final Amount    : Rs. %.2f\n", total);
    printf("===========================\n");

    return 0;
}
