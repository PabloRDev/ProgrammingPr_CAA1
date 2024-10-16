#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include "./taxation.h"

//////////////////////////////////
// Available methods
//////////////////////////////////

// Parse a tDateTime from string information
void date_parse(tDate *date, const char *s_date) {
    // Check output data
    assert(date != NULL);

    // Check input date
    assert(s_date != NULL);
    assert(strlen(s_date) == 10);

    // Parse the input date
    sscanf(s_date, "%d/%d/%d", &(date->day), &(date->month), &(date->year));
}

// Initialize the properties
void properties_init(tProperties *data) {
    /////////////
    // Set the initial number of elements to zero.
    data->count = 0;
    /////////////
}

// Get the number of properties
int properties_len(tLandlord data) {
    //////////////
    // Return the number of elements
    return data.properties.count;
    //////////////
}

// Initialize the landlords
void landlords_init(tLandlords *data) {
    /////////////
    // Set the initial number of elements to zero.
    data->count = 0;
    /////////////
}

// Get the number of landlords
int landlords_len(tLandlords data) {
    //////////////
    // Return the number of elements
    return data.count;
    //////////////
}

//////////////////////////////////////
// EX2: Implement your methods here....
//////////////////////////////////////

// Parse input from CSVEntry:
// Given an entry in the CSV file (tCSVEntry) with the data of a tenant, it initializes a structure of type tTenant with that data
void tenant_parse(tTenant *data, tCSVEntry entry) {
    sscanf(entry.fields[0], "%d/%d/%d", &data->start_date.day, &data->start_date.month, &data->start_date.year);
    sscanf(entry.fields[1], "%d/%d/%d", &data->end_date.day, &data->end_date.month, &data->end_date.year);
    strncpy(data->tenant_id, entry.fields[2], MAX_PERSON_ID);
    data->tenant_id[MAX_PERSON_ID - 1] = '\0'; // Ensure null termination
    strncpy(data->name, entry.fields[3], MAX_NAME);
    data->name[MAX_NAME - 1] = '\0'; // Ensure null termination
    data->rent = (float) atof(entry.fields[4]);
    data->age = atoi(entry.fields[5]);
    strncpy(data->cadastral_ref, entry.fields[6], MAX_CADASTRAL_REF);
    data->cadastral_ref[MAX_CADASTRAL_REF - 1] = '\0'; // Ensure null termination
}

////////////////////////////////////////
// Update owner tax by tenant:
// Given the property rented to a tenant it updates the amount to be paid by its owner. If the property does not belong to any owner, nothing is done.
void landlords_process_tenant(tLandlords *data, tTenant tenant) {
    const char *propertyRef = tenant.cadastral_ref;
    const int rentedMonths = tenant.end_date.month - tenant.start_date.month + 1;
    const float rentedDiscount = AMOUNT_NO_RENT * (float) rentedMonths;

    for (int i = 0; i < data->count; i++) {
        tLandlord *landlord = &data->elems[i];

        for (int j = 0; j < landlord->properties.count; j++) {
            if (strcmp(landlord->properties.elems[j].cadastral_ref, propertyRef) != 0) {
                // No landlord's property
                continue;
            }

            // Tax based on tenant age
            const float rentedTax = tenant.age > 35
                                        ? (0.2f * tenant.rent * (float) rentedMonths)
                                        : (0.1f * tenant.rent * (float) rentedMonths);
            landlord->tax -= rentedDiscount;
            landlord->tax += rentedTax;
        }
    }
}

// Get a property:
// Given an owner(tLandlord), returns a character string with the property data stored in the index position of the tProperties structure.The result is only used to display it on standard output.
void property_get(tLandlord data, int index, char *buffer) {
    tProperty property = data.properties.elems[index];

    if (index < 0 || index >= data.properties.count || strcmp(data.properties.elems[index].cadastral_ref, "") == 0)
    // Index or property error
    {
        return;
    }

    sprintf(buffer, "%s;%s;%d;%s",
            property.cadastral_ref,
            property.street,
            property.number,
            property.landlord_id);
}

// Parse input from CSVEntry:
// Given an entry in the CSV file (tCSVEntry) with the data of a property, it assigns them to a structure of type tProperty
void property_parse(tProperty *data, tCSVEntry entry) {
    if (strlen(entry.fields[0]) > MAX_CADASTRAL_REF ||
        strlen(entry.fields[1]) > MAX_STREET ||
        strlen(entry.fields[3]) > MAX_PERSON_ID ||
        entry.fields[2][0] == '\0') {
        return; // Entry is valid
    }

    strncpy(data->cadastral_ref, entry.fields[0], MAX_CADASTRAL_REF);
    data->cadastral_ref[MAX_CADASTRAL_REF - 1] = '\0'; // Ensure null termination
    strncpy(data->street, entry.fields[1], MAX_STREET);
    data->street[MAX_STREET - 1] = '\0'; // Ensure null termination
    data->number = atoi(entry.fields[2]); // Convert the string to an integer
    strncpy(data->landlord_id, entry.fields[3], MAX_PERSON_ID);
    data->landlord_id[MAX_PERSON_ID - 1] = '\0'; // Ensure null termination
}

////////////////////////////////////////

// Add a new property:
// If the owner does not have the property in storage, the amount to be paid in taxes by the owner is added and updated considering that the new property is not rented.
void landlord_add_property(tLandlords *data, tProperty property) {
    for (int i = 0; i < data->count; i++) {
        tLandlord *landlord = &data->elems[i];

        if (strcmp(landlord->id, property.landlord_id) == 0) {
            for (int j = 0; j < data->elems[i].properties.count; j++) {
                if (strcmp(landlord->properties.elems[j].cadastral_ref, property.cadastral_ref) == 0) {
                    break;
                }
            }

            const int index = landlord->properties.count;
            strcpy(landlord->properties.elems[index].cadastral_ref, property.cadastral_ref);
            landlord->properties.elems[index].cadastral_ref[MAX_CADASTRAL_REF - 1] = '\0'; // Ensure null termination
            strcpy(landlord->properties.elems[index].landlord_id, property.landlord_id);
            landlord->properties.elems[index].landlord_id[MAX_PERSON_ID - 1] = '\0'; // Ensure null termination
            strcpy(landlord->properties.elems[index].street, property.street);
            landlord->properties.elems[index].street[MAX_STREET - 1] = '\0'; // Ensure null termination
            landlord->properties.elems[index].number = property.number;

            landlord->properties.count++;
            landlord->tax += (float) AMOUNT_NO_RENT * 12;
        }
    }
}

// Get a landlord:
// Returns a character string with the owner's data stored in the index position of the tLandlords structure.The result is only used to display it on standard output.
void landlord_get(tLandlords data, int index, char *buffer) {
    tLandlord landlord = data.elems[index];

    if (index < 0 || index >= data.count) // Index is invalid
    {
        return;
    }

    sprintf(buffer, "%s;%s, %.1f", //? print_index main?
            landlord.name,
            landlord.id,
            landlord.tax);
}

// Parse input from CSVEntry:
// Given an entry in the CSV file (tCSVEntry) with the data of an owner (without property data), it initializes a structure of type tLandlord with that data.
void landlord_parse(tLandlord *data, tCSVEntry entry) {
    strncpy(data->name, entry.fields[0], MAX_NAME);
    data->name[MAX_NAME - 1] = '\0'; // Ensure null termination
    strncpy(data->id, entry.fields[1], MAX_PERSON_ID);
    data->id[MAX_PERSON_ID - 1] = '\0'; // Ensure null termination
    data->tax = (float) atof(entry.fields[2]);

    data->properties.count = 0;
}

////////////////////////////////////////

// Add a new landlord:
// Given a structure of type tLandlord, adds it to the owners table of type tLandlords. If the owner is already at the table, it does nothing.
void landlords_add(tLandlords *data, tLandlord landlord) {
    for (i = 0; i < MAX_LANDLORDS; i++) {
        if (strcmp(data->elems[i].id, landlord.id) == 0) // Check if is not already at the table
        {
            return;
        }

        if (data->count < MAX_LANDLORDS) // Check if new landlord can be added
        {
            data->elems[data->count] = landlord;
            data->count++;

            return;
        }
    }
}

// Returns true if field tax of expected[index] is greater than the one in declarant[index]
bool mismatch_tax_declaration(tLandlords expected, tLandlords declarant, int index) {
    return expected.elems[index].tax > declarant.elems[index].tax;
}

// Copy the data from the source to destination:
// Copies a structure of type tLandlords into another structure of the same type, except the amount to pay field which is initialized to zero in all owners.
void landlords_cpy(tLandlords *destination, tLandlords source) {
    for (i = 0; i < source.count; i++) {
        destination->elems[i].tax = 0;
        destination->count++;
        destination->elems[i].properties.count = source.elems[i].properties.count;
        strcpy(destination->elems[i].id, source.elems[i].id);
        destination->elems[i].id[MAX_PERSON_ID - 1] = '\0'; // Ensure null termination
        strcpy(destination->elems[i].name, source.elems[i].name);
        destination->elems[i].name[MAX_NAME - 1] = '\0'; // Ensure null termination
    }
}
