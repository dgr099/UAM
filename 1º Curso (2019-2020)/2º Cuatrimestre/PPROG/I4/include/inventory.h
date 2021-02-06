/** 
 * @brief It defines the inventory interface
 * for each command
 * 
 * @file inventory.h
 * @author Diego Grande Camarero
 * @version 1.0 
 * @date 13-03-2020 
 * @copyright GNU Public License
 */

#ifndef INVENTORY_H
#define INVENTORY_H

#include "../include/types.h"
#include "../include/set.h"
#include "../include/object.h"
/*! \var typedef struct _Inventory Inventory
    \brief A type definition for a inventory.
    
    Details.
*/
typedef struct _Inventory Inventory;

/**
 * @brief Create the inventory
 *
 * inventory_create Create a new inventory
 *
 * @date 14-03-2020
 * @author: Diego Grande Camarero
 *
 * @param id id of the inventory
 * @param max max number of objects it will contain
 * @return the new inventory that has been created
 */
Inventory* inventory_create(Id id, int max);

/**
 * @brief Destroy the inventory
 *
 * inventory_destroy Destroy the inventory
 *
 * @date 14-03-2020
 * @author Diego Grande Camarero
 *
 * @param inventory Pointer to the inventory
 * @return Ok if the inventory has been destroyed
*/
STATUS inventory_destroy(Inventory* inventory);
/**
 * @brief Add the object to the inventory
 *
 * @date 14-03-2020
 * @author: Diego Grande Camarero
 *
 * @param inventory Pointer to the inventory
 * @param id The object id
 * @return Ok if there was no problem, ERROR if not
*/
STATUS inventory_add(Inventory* inventory, Id id);

/**
 * @brief Delete the object of the inventory
 *
 * @date 14-03-2020
 * @author Diego Grande Camarero
 *
 * @param inventory Pointer to the inventory
 * @param id id of the object
 * @return Ok if there was no problem, ERROR if not
*/
STATUS inventory_dell(Inventory* inventory, Id id);
/**
 * @brief Return the set of the inventory
 *
 * @date 14-03-2020
 * @author: David Teófilo Garitagoitia Romero
 *
 * @param inventory Pointer to the inventory
 * @return Ok if there was no problem, ERROR if not
*/
Set* inventory_get_inside(Inventory* inventory);
/**
 * @brief check if the object is in inventory
 *
 * @date 14-03-2020
 * @author: David Teófilo Garitagoitia Romero
 *
 * @param inventory Pointer to the inventory
 * @param id  Id of the object  
 * @return True if the object is in the inventory, false otherwise
*/
BOOL inventory_is_object(Inventory *inventory, Id id);
/**
 * @brief return the max number of objects of an inventory
 *
 * @date 14-03-2020
 * @author: David Teófilo Garitagoitia Romero
 *
 * @param inventory Pointer to the inventory
 * @return the max number of objects of an inventory
*/
int inventory_get_max(Inventory *inventory);
/**
 * @brief check if the inventory is full
 *
 * @date 14-03-2020
 * @author: David Teófilo Garitagoitia Romero
 *
 * @param inventory Pointer to the inventory
 * @return true in case that the inventory is full, false otherwise
*/
BOOL inventory_is_full(Inventory *inventory);
/**
 * @brief check if the inventory is empty
 *
 * @date 14-03-2020
 * @author: David Teófilo Garitagoitia Romero
 *
 * @param inventory Pointer to the inventory
 * @return true in case that the inventory is empty, false otherwise
*/
BOOL inventory_is_emty(Inventory *inventory);
/**
 * @brief Print the inventory and on a file given
 *
 * @date 14-03-2020
 * @author Diego Grande Camarero
 *
 * @param f Pointer to the file
 * @param inventory pointer to the inventory
 * @return
*/
void inventory_print(FILE *f, Inventory* inventory);
/**
 * @brief Print the inventory and on a file given
 *
 * @date 14-05-2020
 * @author David Teófilo Garitagoiria Romero
 *
 * @param inv pointer to the inventory
 * @return the id of the inventory
*/
Id inventory_get_id(Inventory *inv);
#endif
