/** 
 * @brief It implements the inventory interpreter
 * 
 * @file inventory.c
 * @author Profesores PPROG
 * @version 2.0 
 * @date 10-01-2020 
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include "../include/inventory.h"
/**
* @brief The inventory structure
*
* It stores information of a inventory
*/
struct _Inventory{
	Id id; /*!< the id of an inventory  */
	Set* inside; /*!< the set inside the inventory */
	int max; /*!< the max objetcs that can be stored in the inventory */
};

Inventory* inventory_create(Id id, int max){

	Inventory* new_inventory = NULL;

	if((new_inventory = (Inventory*)malloc(sizeof(Inventory))) == NULL)
		return NULL;

	new_inventory->id = id;
	new_inventory->inside = set_create();
	new_inventory->max = max;

	return 	new_inventory;
}

STATUS inventory_destroy(Inventory* inventory){

	if(!inventory)
		return ERROR;

	if(set_destroy( inventory->inside) == ERROR)
		return ERROR;

	free( inventory);

	return OK;
}

Set* inventory_get_inside(Inventory* inventory){
	if(!inventory){
		return NULL;
	}
	return inventory->inside;
}


STATUS inventory_add(Inventory* inventory, Id id){

	if(!inventory || id==NO_ID)
		return ERROR;

	if(inventory_is_object(inventory, id)==TRUE) /*the object is already in the inventory*/
		return OK;

	else if( (set_get_num(inventory->inside)+1) <= inventory->max)	/*set_add will increase the set size, so we must check it will be <= than	max size of the inventory set before adding any object*/
		return set_add( inventory->inside, id);
	return ERROR;
}

STATUS inventory_dell(Inventory* inventory, Id id){

	if(!inventory || id==NO_ID)
		return ERROR;

	if(inventory_is_object( inventory, id) == NO_ID) /*the object IS NOT in the inventory*/
		return OK;

	return set_dell( inventory->inside, id);
}

void inventory_print(FILE *f, Inventory* inventory){

	if(!inventory)
		return;

	fprintf(f, "Inventory's id: %ld Inventory's max size: %d \nInventory's contents:\n", inventory->id, inventory->max);
	set_print( f, inventory->inside);

	return;
}

BOOL inventory_is_object(Inventory *inventory, Id id){
	if(!inventory || id==NO_ID){
		return FALSE;
	}
	if(set_find_index(inventory_get_inside(inventory), id)!=-1){
		return TRUE;
	}
	return FALSE;
}

int inventory_get_max(Inventory *inventory){
	if(!inventory){
		return -1;
	}
	return inventory->max;
}

BOOL inventory_is_full(Inventory *inventory){
	if(!inventory){
		return TRUE;
	}
	if(set_get_num(inventory_get_inside(inventory))>=inventory_get_max(inventory)){
		return TRUE;
	}
	return FALSE;
}

BOOL inventory_is_emty(Inventory *inventory){
	if(!inventory){
		return TRUE;
	}
	if(set_get_num(inventory_get_inside(inventory))>0){
		return FALSE;
	}
	return TRUE;
}

Id inventory_get_id(Inventory *inv){
	if(!inv){
		return NO_ID;
	}
	return inv->id;
}