#ifndef   __CARDS_H__
#define   __CARDS_H__

#include <pebble.h>

// Enums
enum side_t {
  FRONT, BACK
};

// Struct to hold text_layers
typedef struct CardBackStruct {
  TextLayer *full_name;
  TextLayer *tla_name;
  TextLayer *polarized;
  TextLayer *func_group;
  TextLayer *pKa;
} CardBack_t;

// Public functions
extern void init_cards(Window *main_window,
                       GBitmap *main_image_front,
                       BitmapLayer *main_image_layer_front,
                       CardBack_t main_card_back);
extern void deinit_cards(void);
extern enum side_t flip_card(void);
extern enum side_t get_side(void);
extern void rand_card(void);

#endif /* __CARDS_H__ */
