#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "taxation.h"

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse a tDateTime from string information
void date_parse(tDate *date, const char *s_date)
{
    // Check output data
    assert(date != NULL);

    // Check input date
    assert(s_date != NULL);
    assert(strlen(s_date) == 10);

    // Parse the input date
    sscanf(s_date, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Initialize the properties
void properties_init(tProperties *data)
{
    /////////////
    // Set the initial number of elements to zero.
    data->count = 0;
    /////////////
}

// Get the number of properties
int properties_len(tLandlord data)
{
    //////////////
    // Return the number of elements
    return data.properties.count;
    //////////////
}

// Initialize the landlords
void landlords_init(tLandlords *data)
{
    /////////////
    // Set the initial number of elements to zero.
    data->count = 0;
    /////////////
}

// Get the number of landlords
int landlords_len(tLandlords data)
{
    //////////////
    // Return the number of elements
    return data.count;
    //////////////
}

//////////////////////////////////////
// EX2: Implement your methods here....
//////////////////////////////////////

// Parse input from CSVEntry
void tenant_parse(tTenant *data, tCSVEntry entry)
{
    // TODO
}

////////////////////////////////////////
void landlords_process_tenant(tLandlords *data, tTenant tenant)
{
    // TODO
}

// Get a property
void property_get(tLandlord data, int index, char *buffer)
{
    // TODO
}

// Parse input from CSVEntry
void property_parse(tProperty *data, tCSVEntry entry)
{
    // TODO
}

////////////////////////////////////////

// Add a new property:
// Adds to a structure of type tLandlords, the information of a new property(tProperty). If the property belongs to an owner who does not exist in the structure, nothing is done. If the owner exists and already has the property stored, nothing is done either. If the owner does not have the property in storage, the amount to be paid in taxes by the owner is added and updated considering that the new property is not rented.
void landlord_add_property(tLandlords *tLandlords, tProperty property)
{
    for (i = 0; i < tLandlords->count; i++)
    {
        tLandlord landlord = tLandlords->elems[i];
        int noContains = 0;

        for (j = 0; j < landlord.properties.count; j++)
        {
            if (landlord.id == property.landlord_id)
            {
                if (landlord.properties.elems[j].cadastral_ref != property.cadastral_ref)
                {
                    noContains++;

                    if (noContains == landlord.properties.count) {
                        landlord.tax + 150;
                    }
                } 
            }
        }
    }
}

// Get a landlord
void landlord_get(tLandlords data, int index, char *buffer)
{
    // TODO
}

// Parse input from CSVEntry
void landlord_parse(tLandlord *data, tCSVEntry entry)
{
    // TODO
}

////////////////////////////////////////

// Add a new landlord
void landlords_add(tLandlords *data, tLandlord landlord)
{
    // TODO
}

// returns true if field tax of expected[index] is greater than the one in declarant[index]
bool mismatch_tax_declaration(tLandlords expected, tLandlords declarant, int index)
{
    // TODO
    return false;
}

// Copy the data from the source to destination
void landlords_cpy(tLandlords *destination, tLandlords source)
{
    // TODO
}
