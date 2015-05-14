#include "direction_window.h"

#define BITMAP_WIDTH 18
#define BITMAP_HEIGHT 168
  
// BEGIN AUTO-GENERATED UI CODE; DO NOT MODIFY
static Window *s_window;
static GFont s_res_gothic_24_bold;
static GFont s_res_bitham_30_black;
static GFont s_res_gothic_28_bold;
static GFont s_res_bitham_42_bold;
static BitmapLayer *s_bitmaplayer_screen;
static TextLayer *s_textlayer_instruction;
static TextLayer *s_textlayer_distance;
static TextLayer *s_textlayer_unit;
static TextLayer *s_textlayer_direction;

static void initialise_ui(void) {
  s_window = window_create();
  window_set_fullscreen(s_window, 0);
  
  s_res_gothic_24_bold = fonts_get_system_font(FONT_KEY_GOTHIC_24_BOLD);
  s_res_bitham_30_black = fonts_get_system_font(FONT_KEY_BITHAM_30_BLACK);
  s_res_gothic_28_bold = fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD);
  s_res_bitham_42_bold = fonts_get_system_font(FONT_KEY_BITHAM_42_BOLD);
  // s_bitmaplayer_screen
  s_bitmaplayer_screen = bitmap_layer_create(GRect(0, 0, 144, 152));
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_bitmaplayer_screen);
  
  // s_textlayer_instruction
  s_textlayer_instruction = text_layer_create(GRect(0, 70, 144, 97));
  text_layer_set_background_color(s_textlayer_instruction, GColorClear);
  text_layer_set_text(s_textlayer_instruction, "进入内部路");
  text_layer_set_font(s_textlayer_instruction, s_res_gothic_24_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_instruction);
  
  // s_textlayer_distance
  s_textlayer_distance = text_layer_create(GRect(72, 0, 72, 33));
  text_layer_set_background_color(s_textlayer_distance, GColorClear);
  text_layer_set_text(s_textlayer_distance, "15");
  text_layer_set_font(s_textlayer_distance, s_res_bitham_30_black);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_distance);
  
  // s_textlayer_unit
  s_textlayer_unit = text_layer_create(GRect(72, 36, 72, 30));
  text_layer_set_background_color(s_textlayer_unit, GColorClear);
  text_layer_set_text(s_textlayer_unit, "米后");
  text_layer_set_font(s_textlayer_unit, s_res_gothic_28_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_unit);
  
  // s_textlayer_direction
  s_textlayer_direction = text_layer_create(GRect(6, 6, 60, 60));
  text_layer_set_background_color(s_textlayer_direction, GColorClear);
  text_layer_set_text(s_textlayer_direction, ">");
  text_layer_set_text_alignment(s_textlayer_direction, GTextAlignmentCenter);
  text_layer_set_font(s_textlayer_direction, s_res_bitham_42_bold);
  layer_add_child(window_get_root_layer(s_window), (Layer *)s_textlayer_direction);
}

static void destroy_ui(void) {
  window_destroy(s_window);
  bitmap_layer_destroy(s_bitmaplayer_screen);
  text_layer_destroy(s_textlayer_instruction);
  text_layer_destroy(s_textlayer_distance);
  text_layer_destroy(s_textlayer_unit);
  text_layer_destroy(s_textlayer_direction);
}
// END AUTO-GENERATED UI CODE

static void handle_window_unload(Window* window) {
  destroy_ui();
}

void show_direction_window(void) {
  initialise_ui();
  window_set_window_handlers(s_window, (WindowHandlers) {
    .unload = handle_window_unload,
  });
  window_stack_push(s_window, true);
}

void hide_direction_window(void) {
  window_stack_remove(s_window, true);
}

void update_info(char *direction, char *distance, char *unit, char *instruction) {
  text_layer_set_text(s_textlayer_direction, direction);
  text_layer_set_text(s_textlayer_distance, distance);
  text_layer_set_text(s_textlayer_unit, unit);
  text_layer_set_text(s_textlayer_instruction, instruction);
  vibes_short_pulse();
}

void update_bitmap(Tuple *bitmapData){
  uint8_t character_data[BITMAP_WIDTH * BITMAP_HEIGHT];
  GBitmap character_bitmap;
  character_bitmap = (GBitmap) {
        .addr = character_data,
        .bounds = GRect(0, 0, BITMAP_WIDTH*8, BITMAP_HEIGHT),
        .info_flags = 1,
        .row_size_bytes = 20,
    };
// 	bitmap_layer_set_background_color(s_bitmaplayer_screen, GColorWhite);
  bitmap_layer_set_bitmap(s_bitmaplayer_screen, &character_bitmap);
  memcpy(&character_data[0], bitmapData->value->data, bitmapData->length);
}