#ifndef   __CARDS_H__
#define   __CARDS_H__

#include <pebble.h>

#define TOTAL_CARDS (10)

// Public functions
extern void init_cards(Window *main_window,
                       GBitmap *main_image_front,
                       GBitmap *main_image_back,
                       BitmapLayer *main_image_layer_front,
                       BitmapLayer *main_image_layer_back);
extern void deinit_cards(void);
extern void flip_card(void);
extern void next_card(void);
extern void prev_card(void);

#endif /* __CARDS_H__ */
