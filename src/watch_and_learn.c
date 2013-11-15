#include <pebble.h>
#include "cards.h"

#define NEXT_INTERVAL  (15)    // seconds
#define THRESHOLD      (750)   // mg

static Window *window;
static GBitmap *image_front;
static BitmapLayer *image_layer_front;
static TextLayer *time_layer;
static uint8_t seconds_tick = 0;
static CardBack_t card_back;

static void tick_timer_handler(struct tm *tick_time, TimeUnits units_changed) {
  static char time_text[] = "00:00"; // Needs to be static because it's used by the system later.
  strftime(time_text, sizeof(time_text), "%R", tick_time);

  text_layer_set_text(time_layer, time_text);
  if (!(tick_time->tm_sec % NEXT_INTERVAL)) {
    rand_card();
    text_layer_set_text_color(time_layer, GColorWhite);
    layer_remove_from_parent((Layer*)time_layer);
    layer_add_child(window_get_root_layer(window), (Layer*)time_layer);
  }
}

static void accel_data_handler(AccelData *data, uint32_t num_samples) {
  bool hit = false;
  uint8_t i = 0;

  // Look for +y threshold
  while (i < num_samples) {
    if ((data + i)->y > THRESHOLD) {
      hit = true;;
    }

    ++i;

    if (hit) {
      break;
    }
  }

  if (!hit) {
    return;
  }

  // Reset hit
  hit = false;;

  // Look for -z threshold
  while (i < num_samples) {
    if ((data + i)->z < -THRESHOLD) {
      hit = true;
    }

    ++i;

    if (hit) {
      if (flip_card() == BACK) {
        text_layer_set_text_color(time_layer, GColorBlack);
      } else {
        text_layer_set_text_color(time_layer, GColorWhite);
      }
      return;
    }
  }
}

static void window_load(Window *window) {
  init_cards(window, image_front, image_layer_front, card_back);

  time_layer = text_layer_create(GRect(93, 0, 50, 28));
  text_layer_set_text_color(time_layer, GColorWhite);
  text_layer_set_background_color(time_layer, GColorClear);
  text_layer_set_font(time_layer, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_text_alignment(time_layer, GTextAlignmentCenter);
  layer_add_child(window_get_root_layer(window), (Layer*)time_layer);
}

static void window_unload(Window *window) {
  text_layer_destroy(time_layer);
  deinit_cards();
}


static void init(void) {
  window = window_create();
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_set_fullscreen(window, true);
  window_stack_push(window, animated);

  // Ensures time is displayed immediately (will break if NULL tick event accessed).
  // (This is why it's a good idea to have a separate routine to do the update itself.)
  time_t now = time(NULL);
  struct tm *current_time = localtime(&now);
  tick_timer_handler(current_time, SECOND_UNIT);

  tick_timer_service_subscribe(SECOND_UNIT, &tick_timer_handler);
  accel_service_set_sampling_rate(ACCEL_SAMPLING_25HZ);
  accel_data_service_subscribe(14, &accel_data_handler);
}

static void deinit(void) {
  accel_data_service_unsubscribe();
  tick_timer_service_unsubscribe();
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}
