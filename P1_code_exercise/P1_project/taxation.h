#ifndef __TAXATION_H__
#define __TAXATION_H__
#include "csv.h"

typedef struct _tDate {    
    int day; 
    int month;
    int year;
} tDate;

// Ex 1: Define data types here...

///////////////////////////
#define MAX_TENANTS 50
#define MAX_PROPERTIES 80
#define MAX_LANDLORDS 10
#define MAX_NAME 15
#define MAX_CADASTRAL_REF 7
#define MAX_STREET 25
#define MAX_PERSON_ID 9
#define AMOUNT_NO_RENT 150.0

// Ex 1: Define data types here...
typedef struct tTenant
{
    
};
typedef struct tProperty
{
};
typedef struct tLandlord
{
};

typedef struct _tProperties {
    tProperty elems[MAX_PROPERTIES];
    int count;
} tProperties;

typedef struct _tLandlords {
    tLandlord elems[MAX_LANDLORDS];
    int count;
} tLandlords;

//////////////////////////////////
// Available methods
//////////////////////////////////
// Initialize the properties data
void properties_init(tProperties* data);

// Get the number of properties
int properties_len(tLandlord data);

// Initialize the landlords data
void landlords_init(tLandlords* data);

// Get the number of landlords
int landlords_len(tLandlords data);

/////////////////////////////////////
// Ex 2: Requested methods ....
/////////////////////////////////////

// Parse input from CSVEntry
void landlord_parse(tLandlord* data, tCSVEntry entry);

// Add a new tenant
void landlords_add(tLandlords* data, tLandlord tenant);

// Copy the data from the source to destination
void landlords_cpy(tLandlords* destination, tLandlords source);

// Parse input from CSVEntry
void property_parse(tProperty* data, tCSVEntry entry);

// Add a new property
void landlord_add_property(tLandlords* data, tProperty property);

// Parse input from CSVEntry
void tenant_parse(tTenant* data, tCSVEntry entry);

// Calculate and update taxation given tenant
void landlords_process_tenant(tLandlords* data, tTenant tenant);

// Get landlord data in a string
void landlord_get(tLandlords data, int index, char* buffer);

// Get a property data in a string
void property_get(tLandlord data, int index, char* buffer);

// returns true if field tax of expected[index] is greater than the one in declarant[index]
bool mismatch_tax_declaration(tLandlords expected, tLandlords declarant, int index);


/////////////////////////////////////
// Define your aux methods here
/////////////////////////////////////


////////////////////////////////////////////
#endif
