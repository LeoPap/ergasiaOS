#ifndef PIZZA_APP_H
#define PIZZA_APP_H

// Constants for the pizza app
#define NUM_COOKS 2
#define NUM_OVENS 15
#define NUM_PACKERS 2
#define NUM_DELIVERERS 10

#define NUM_ORDERS_LOW 1
#define NUM_ORDERS_HIGH 3
#define NUM_ORDERS_LOW_SPECIAL 1
#define NUM_ORDERS_HIGH_SPECIAL 5

#define PERCENTAGE_PLAIN 60

#define PAYMENT_AMOUNT_LOW 1
#define PAYMENT_AMOUNT_HIGH 3

#define PERCENTAGE_FAILURE 10

#define NUM_PLAIN_PIZZAS 10
#define NUM_SPECIAL_PIZZAS 12

#define NUM_PREP_TIME 1
#define NUM_BAKE_TIME 10
#define NUM_PACK_TIME 1
#define NUM_DELIVERY_TIME_LOW 5
#define NUM_DELIVERY_TIME_HIGH 15



// Παραγγελία
typedef struct {
    int id;
    // Άλλα πεδία της παραγγελίας
} Order;

// Συγχρονισμός
pthread_mutex_t mutex;
pthread_cond_t cond_pizza_ready;
pthread_cond_t cond_order_ready;

// Κατάσταση πίτσας
enum {
    PIZZA_NOT_READY,
    PIZZA_READY
} pizza_status = PIZZA_NOT_READY;

// Σερβιτόρος
void *pizza_chef(void *arg) {
    Order *order = (Order *)arg;
    
    // Προετοιμασία πίτσας
    printf("Pizza Chef is preparing pizza for order %d\n", order->id);
    
    // Κλείδωμα mutex για την αλληλεπίδραση με τον φούρνο και τον συσκευαστή
    pthread_mutex_lock(&mutex);
    
    // Αναμονή για να γίνει διαθέσιμος ο φούρνος
    while (pizza_status == PIZZA_READY) {
        pthread_cond_wait(&cond_pizza_ready, &mutex);
    }
    
    // Ψήσιμο πίτσας
    printf("Pizza Chef is baking pizza for order %d\n", order->id);
    sleep(2); // Προσομοίωση χρόνου ψησίματος
    
    // Ολοκλήρωση ψησίματος πίτσας
    pizza_status = PIZZA_READY;
    printf("Pizza Chef has baked pizza for order %d\n", order->id);
    
    // Απελευθέρωση mutex
    pthread_mutex_unlock(&mutex);
    
    // Ειδοποίηση του συσκευαστή ότι η πίτσα είναι έτοιμη
    pthread_cond_signal(&cond_order_ready);
    
    pthread_exit(NULL);
}

// Φούρνος
void *pizza_oven(void *arg) {
    // Κλείδωμα mutex για την αλληλεπίδραση με τον σερβιτόρο
    pthread_mutex_lock(&mutex);
    
    // Αναμονή για την έτοιμη πίτσα
    while (pizza_status == PIZZA_NOT_READY) {
        pthread_cond_wait(&cond_order_ready, &mutex);
    }
    
    // Εξόδος πίτσας από τον φούρνο
    printf("Pizza Oven is releasing pizza\n");
    
    // Επαναφορά κατάστασης πίτσας
    pizza_status = PIZZA_NOT_READY;
    
    // Απελευθέρωση mutex
    pthread_mutex_unlock(&mutex);
    
    // Ειδοποίηση του σερβιτόρου ότι ο φούρνος είναι διαθέσιμος
    pthread_cond_signal(&cond_pizza_ready);
    
    pthread_exit(NULL);
}

// Συσκευαστής
void *packaging_employee(void *arg) {
    Order *order = (Order *)arg;
    
    // Αναμονή για την έτοιμη πίτσα
    pthread_mutex_lock(&mutex);
    
    while (pizza_status == PIZZA_NOT_READY) {
        pthread_cond_wait(&cond_order_ready, &mutex);
    }
    
    // Συσκευασία πίτσας
    printf("Packaging Employee is packaging pizza for order %d\n", order->id);
    sleep(1); // Προσομοίωση χρόνου συσκευασίας
    
    // Ολοκλήρωση συσκευασίας πίτσας
    printf("Packaging Employee has packaged pizza for order %d\n", order->id);
    
    // Απελευθέρωση mutex
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

// Διανομέας
void *delivery_driver(void *arg) {
    Order *order = (Order *)arg;
    
    // Παράδοση πίτσας
    printf("Delivery Driver is delivering pizza for order %d\n", order->id);
    sleep(3); // Προσομοίωση χρόνου παράδοσης
    
    // Ολοκλήρωση παράδοσης πίτσας
    printf("Delivery Driver has delivered pizza for order %d\n", order->id);
    
    pthread_exit(NULL);
}

#endif /* PIZZA_APP_H */
