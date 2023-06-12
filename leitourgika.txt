#include <pthread.h>
#include <stdio.h>

#define NUM_PIZZA_ORDERS 10
#define NUM_PIZZA_CHEFS 2
#define NUM_PIZZA_OVENS 1
#define NUM_PACKAGING_EMPLOYEES 3
#define NUM_DELIVERY_DRIVERS 4

pthread_mutex_t order_mutex;
pthread_cond_t order_ready_cond;
int num_orders_ready = 0;

void* pizza_chef(void* arg) {
    // Υλοποίηση κώδικα για τους παρασκευαστές πίτσας
}

void* pizza_oven(void* arg) {
    // Υλοποίηση κώδικα για τους φούρνους πίτσας
}

void* packaging_employee(void* arg) {
    // Υλοποίηση κώδικα για τους υπαλλήλους πακεταρίσματος
}

void* delivery_driver(void* arg) {
    // Υλοποίηση κώδικα για τους διανομείς
}

int main() {
    pthread_t pizza_chefs[NUM_PIZZA_CHEFS];
    pthread_t pizza_ovens[NUM_PIZZA_OVENS];
    pthread_t packaging_employees[NUM_PACKAGING_EMPLOYEES];
    pthread_t delivery_drivers[NUM_DELIVERY_DRIVERS];

    // Αρχικοποίηση mutex και μεταβλητής συνθήκης
    pthread_mutex_init(&order_mutex, NULL);
    pthread_cond_init(&order_ready_cond, NULL);

    // Δημιουργία νημάτων για τους παρασκευαστές πίτσας
    for (int i = 0; i < NUM_PIZZA_CHEFS; i++) {
        pthread_create(&pizza_chefs[i], NULL, pizza_chef, NULL);
    }

    // Δημιουργία νημάτων για τους φούρνους πίτσας
    for (int i = 0; i < NUM_PIZZA_OVENS; i++) {
        pthread_create(&pizza_ovens[i], NULL, pizza_oven, NULL);
    }

    // Δημιουργία νημάτων για τους υπαλλήλους πακεταρίσματος
    for (int i = 0; i < NUM_PACKAGING_EMPLOYEES; i++) {
        pthread_create(&packaging_employees[i], NULL, packaging_employee, NULL);
    }

    // Δημιουργία νημάτων για τους διανομείς
    for (int i = 0; i < NUM_DELIVERY_DRIVERS; i++) {
        pthread_create(&delivery_drivers[i], NULL, delivery_driver, NULL);
    }

    // Αναμονή ολοκλήρωσης των νημάτων παραγγελιών

    // Καταστροφή mutex και μεταβλητής συνθήκης
    pthread_mutex_destroy(&order_mutex);
    pthread_cond_destroy(&order_ready_cond);

    return 0;
}