#include <stdio.h>
/*
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202301L
#define USE_C23_INIT 1
#endif
*/
// #define USE_C23_INIT 0
#define USE_C23_INIT 1

#if !USE_C23_INIT
#include <stdbool.h>
#endif

#define ARR_LEN 16
#define MAX_DOORS 5
#define MAX_WHEELS 4

int main() {

  // Door variants
  typedef enum {
    DOOR_MANUAL,
    DOOR_ELECTRIC,
  } doorVariant_t;

  // Transmission variants
  typedef enum {
    TRANSMISSION_MANUAL,
    TRANSMISSION_AUTOMATIC,
  } transmissionVariant_t;

  // Wheel variants
  typedef enum {
    WHEEL_TYPE_STEEL,
    WHEEL_TYPE_ALLOY,
  } wheelVariant_t;

  // 
  typedef struct {
    wheelVariant_t variant; // Variant of the wheel
    int size;               // Diameter of the wheel in inches
    char brand[20];         // Brand of the wheel
  } wheel_t;
  
  typedef struct {
    doorVariant_t variant;
    int color;              // Hex value
    int frontrear : 2;      // Front: 0b10  Rear: 0b01
    int leftright : 2;      // Left: 0b10   Right: 0b01
    int trunk : 1;
  } door_t;

  typedef struct {
    char model_name[40];           // Model of the car
    int year;               // Year of manufacture
    double mileage;         // Mileage in kilometers
    wheel_t wheels[MAX_WHEELS];      // Array of 4 wheels
    door_t doors[MAX_DOORS];        // Array of 4 doors
    transmissionVariant_t transmission; // Transmission type
    char drivingWheel;      // Left or Right (e.g., 'L', 'R')
    bool hasClutch;         // `True` for manual, `False` for automatic
  } car_t;

  printf("This is example1 using C2x features.\n");

  // Initialize car_t using designated initializers (C23-specific feature)
  car_t car_model_01 = {
#if USE_C23_INIT
    .model_name = "Tesla Model 3\0",

    .year = 2023,
    .mileage = 10000.0,
    .wheels = 
      { .variant = WHEEL_TYPE_ALLOY, .size = 18, .brand = "Michelin" }
      /*{ .variant = WHEEL_TYPE_ALLOY, .size = 18, .brand = "Michelin" },
      { .variant = WHEEL_TYPE_ALLOY, .size = 18, .brand = "Michelin" },
      { .brand = "Michelin", .variant = WHEEL_TYPE_ALLOY, .size = 18  },*/
    ,
#else
    // Use alternative initialization for older C versions
    .wheels = {},
    /* .wheels = {
      { WHEEL_TYPE_ALLOY, 16, "BBS" },
      { WHEEL_TYPE_ALLOY, 16, "BBS" },
      { WHEEL_TYPE_ALLOY, 16, "BBS" },
      { WHEEL_TYPE_ALLOY, 16, "BBS" },
    },*/
#endif
    .doors = { DOOR_ELECTRIC, DOOR_ELECTRIC, DOOR_ELECTRIC, DOOR_ELECTRIC },
    .transmission = TRANSMISSION_AUTOMATIC,
    .drivingWheel = 'L',
    .hasClutch = false,
  };








  // Testing Code ...
  printf("\n Model: %s", car_model_01.model_name);           // Model of the car
  printf("\n Year: %d", car_model_01.year);               // Year of manufacture
  printf("\n Mileage: %d", car_model_01.mileage);         // Mileage in kilometers
  printf("\n Wheels:");      // Array of 4 wheels
  for(int idx = 0; idx < MAX_WHEELS; idx++) {
    printf("\n\t [%d]", idx);
    printf("\n\t\t * Variant: %d", car_model_01.wheels[idx].variant);
    printf("\n\t\t * Size: %d", car_model_01.wheels[idx].size);
    printf("\n\t\t * Brand: %s", car_model_01.wheels[idx].brand);
  }
  printf("\n Doors:");        // Array of 4 doors
  for(int idx = 0; idx < MAX_DOORS; idx++) {
    printf("\n\t [%d]", idx);
    printf("\n\t\t * Variant: %d", car_model_01.doors[idx].variant);
    printf("\n\t\t * Color: %x", car_model_01.doors[idx].color);
    printf("\n\t\t * Front or rear: %b", car_model_01.doors[idx].frontrear);
    printf("\n\t\t * Left or right: %b", car_model_01.doors[idx].leftright);
    printf("\n\t\t * Trunk: %b", car_model_01.doors[idx].trunk);
  }
  printf("\n Transmission %d", car_model_01.transmission); // Transmission type
  printf("\n Driving wheel: %c", car_model_01.drivingWheel);      // Left or Right (e.g., 'L', 'R')
  printf("\n Clutch: %d", car_model_01.hasClutch);         // `True` for manual, `False` for automatic
  printf("\n");
  
  return 0;
}

