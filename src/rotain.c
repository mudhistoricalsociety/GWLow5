/***************************************************************************
 *  Original Diku Mud copyright (C) 1990, 1991 by Sebastian Hammer,        *
 *  Michael Seifert, Hans Henrik St{rfeldt, Tom Madsen, and Katja Nyboe.   *
 *                                                                         *
 *  Merc Diku Mud improvments copyright (C) 1992, 1993 by Michael          *
 *  Chastain, Michael Quan, and Mitchell Tse.                              *
 *                                                                         *
 *  In order to use any part of this Merc Diku Mud, you must comply with   *
 *  both the original Diku license in 'license.doc' as well the Merc       *
 *  license in 'license.txt'.  In particular, you may not remove either of *
 *  these copyright notices.                                               *
 *                                                                         *
 *  Much time and thought has gone into this software and you are          *
 *  benefitting.  We hope that you share your changes too.  What goes      *
 *  around, comes around.                                                  *
 ***************************************************************************/

#if defined(macintosh)
#include <types.h>
#else
#include <sys/types.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "merc.h"

void format_string_spaces args ( (char *argument,int spaces) );

/* 
 * Donate Command
 */
void do_donate(CHAR_DATA *ch, char *argument)
{
 char Object_Name[MAX_INPUT_LENGTH];
 ROOM_INDEX_DATA *xRoom;
 OBJ_DATA *xObject;
 int DONATION_ROOM;

 argument = one_argument(argument, Object_Name);
 if ( Object_Name == '\0' )
 {
   send_to_char("Donate WHAT Object?",ch);
   return;  
 }
 if ( ( xObject= get_obj_carry(ch,Object_Name)) == NULL)
 {
   send_to_char("You can't donate that item! You have not got it!",ch);
   return;
 }
 switch(xObject->item_type)
 {
   case ITEM_WEAPON :
       DONATION_ROOM=DONATION_ROOM_WEAPON;
       break;   
   case ITEM_ARMOR  :
       DONATION_ROOM=DONATION_ROOM_ARMOR;
       break;   
   default :
       DONATION_ROOM=DONATION_ROOM_REST;
       break;   
 }
 if ( ( xRoom = get_room_index(DONATION_ROOM)) == NULL)
 {
   bug("Donate Room Does Not Exist : %d",DONATION_ROOM);
   return;
 }
 act("$p vanishes from your hands in a pink mist.",ch,xObject,NULL,TO_CHAR);
 act("$p vanishes from $n's hands in a pink mist.",ch,xObject,NULL,TO_ROOM);
 obj_from_char(xObject);
 obj_to_room(xObject,xRoom);
 act("$p appears in a pink mist in the room.",ch,xObject,NULL,TO_ROOM);
 return;
}

/* 
 * OutPuts Current Mud Code Version
 */ 
void do_version( CHAR_DATA *ch, char *argument)
{
   char buf[MAX_INPUT_LENGTH];

   sprintf(buf, "\n\r*************************************\n\rCrusade:- %d\n\r*************************************\n\r",VERSION_NUMBER);
   send_to_char(buf,ch);
   return;
}


/*
 * This procedure adds spaces to string if it is not long enough
 */

void format_string_spaces(char *argument,int spaces)
{
  int loop_counter;
  int string_length=strlen(argument);

  if (string_length < spaces)
  {
     for (loop_counter=string_length;loop_counter<=spaces;loop_counter++)
     {
        strcat(argument," ");
     }
  }
  return;
}

