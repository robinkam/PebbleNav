#include <pebble.h>
#include "direction_window.h"

Window *window;	
	
// Key values for AppMessage Dictionary
enum {
	STATUS_KEY = 0,	
	MESSAGE_KEY = 1
};

enum {
  PNPebbleAppMsgKeyDirection = 0,
  PNPebbleAppMsgKeyDistance = 1,
  PNPebbleAppMsgKeyUnit = 2,
  PNPebbleAppMsgKeyInstruction = 3,
  PNPebbleAppMsgKeyBitmap = 4,
};

// Write message to buffer & send
void send_message(void){
	DictionaryIterator *iter;
	
	app_message_outbox_begin(&iter);
	dict_write_uint8(iter, STATUS_KEY, 0x1);
	
	dict_write_end(iter);
  	app_message_outbox_send();
}

// Called when a message is received from PebbleKitJS
static void in_received_handler(DictionaryIterator *received, void *context) {
	Tuple *tuple;
  char *direction = "";
  char *distance = "";
  char *unit = "";
  char *instruction = "";
  
  Tuple *bitmapTuple = dict_find(received, PNPebbleAppMsgKeyBitmap);
  if(bitmapTuple) {
//     APP_LOG(APP_LOG_LEVEL_DEBUG, "Received PNPebbleAppMsgKeyBitmap: %s", bitmapTuple->value->data); 
    update_bitmap(bitmapTuple);
  }
	
	tuple = dict_find(received, PNPebbleAppMsgKeyDirection);
	if(tuple) {
    direction = tuple->value->cstring;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received PNPebbleAppMsgKeyDirection: %s", direction); 
	}
	
	tuple = dict_find(received, PNPebbleAppMsgKeyDistance);
	if(tuple) {
    distance = tuple->value->cstring;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received PNPebbleAppMsgKeyDistance: %s", distance);
	}
  
  tuple = dict_find(received, PNPebbleAppMsgKeyUnit);
	if(tuple) {
    unit = tuple->value->cstring;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received PNPebbleAppMsgKeyUnit: %s", unit);
	}
  
  tuple = dict_find(received, PNPebbleAppMsgKeyInstruction);
	if(tuple) {
    instruction = tuple->value->cstring;
		APP_LOG(APP_LOG_LEVEL_DEBUG, "Received PNPebbleAppMsgKeyInstruction: %s", instruction);
	}
  update_info(direction, distance, unit, instruction);
}

// Called when an incoming message from PebbleKitJS is dropped
static void in_dropped_handler(AppMessageResult reason, void *context) {	
}

// Called when PebbleKitJS does not acknowledge receipt of a message
static void out_failed_handler(DictionaryIterator *failed, AppMessageResult reason, void *context) {
}

void init(void) {
// 	window = window_create();
// 	window_stack_push(window, true);
  
  show_direction_window();
	
	// Register AppMessage handlers
	app_message_register_inbox_received(in_received_handler); 
	app_message_register_inbox_dropped(in_dropped_handler); 
	app_message_register_outbox_failed(out_failed_handler);
		
	app_message_open(app_message_inbox_size_maximum(), app_message_outbox_size_maximum());
	
	send_message();
}

void deinit(void) {
	app_message_deregister_callbacks();
  hide_direction_window();
// 	window_destroy(window);
}

int main( void ) {
	init();
	app_event_loop();
	deinit();
}