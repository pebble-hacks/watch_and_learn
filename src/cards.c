#include "amino_acids.h"
#include "cards.h"

#define NUMBER_OF_CARDS  (NUMBER_OF_AMINO_ACIDS)

// Globals
static enum side_t current_side;
static enum amino_acid_t current_card;
static Window *window;
static GBitmap *image_front;
static BitmapLayer *image_layer_front;
static CardBack_t card_back;
static bool card_used[NUMBER_OF_CARDS];
static uint8_t card_counter = NUMBER_OF_CARDS;

// Private functions
static void load_card(void);
static void load_card_image(void);
static void free_card_image(void);
static void init_card_text(void);
static void show_card_text(void);
static void hide_card_text(void);
static void load_card_text(enum amino_acid_t aa);
static void reset_card_used(void);

void init_cards(Window *main_window,
                GBitmap *main_image_front,
                BitmapLayer *main_image_layer_front,
                CardBack_t main_card_back)
{
  reset_card_used();
  current_card = rand() % NUMBER_OF_CARDS;
  current_side = FRONT;
  window = main_window;
  image_front = main_image_front;
  image_layer_front = main_image_layer_front;
  card_back = main_card_back;
  init_card_text();

  load_card();
}

void deinit_cards(void) {
  free_card_image();
  text_layer_destroy(card_back.full_name);
  text_layer_destroy(card_back.tla_name);
  text_layer_destroy(card_back.polarized);
  text_layer_destroy(card_back.func_group);
  text_layer_destroy(card_back.pKa);
}

enum side_t flip_card(void) {
  if(current_side == FRONT) {
    layer_set_hidden((Layer*)image_layer_front, true);
    show_card_text();
    current_side = BACK;
  } else {
    layer_set_hidden((Layer *)image_layer_front, false);
    hide_card_text();
    current_side = FRONT;
  }

  return (current_side);
}

void rand_card(void) {
  free_card_image();

  while (card_used[current_card]) {
    current_card = rand() % NUMBER_OF_CARDS;
  }

  load_card();
}

void load_card(void) {
  // Remove the image layer from the parent
  if (bitmap_layer_get_layer(image_layer_front)) {
    layer_remove_from_parent((Layer*)image_layer_front);
  }

  load_card_image();
  load_card_text(current_card);
  card_used[current_card] = true;

  if (!(--card_counter)) {
    reset_card_used();
  }
}

void load_card_image(void) {
  switch(current_card) {
  case ILE:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ILE_FRONT);
    break;
  case ALA:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ALA_FRONT);
    break;
  case ARG:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARG_FRONT);
    break;
  case ASP:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASP_FRONT);
    break;
  case CYS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CYS_FRONT);
    break;
  case GLU:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLU_FRONT);
    break;
  case GLY:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLY_FRONT);
    break;
  case HIS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HIS_FRONT);
    break;
  case LEU:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LEU_FRONT);
    break;
  case LYS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LYS_FRONT);
    break;
  case MET:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MET_FRONT);
    break;
  case GLN:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLN_FRONT);
    break;
  case PHE:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PHE_FRONT);
    break;
  case PRO:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PRO_FRONT);
    break;
  case SER:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SER_FRONT);
    break;
  case THR:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_THR_FRONT);
    break;
  case TRP:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRP_FRONT);
    break;
  case ASN:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASN_FRONT);
    break;
  case TYR:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TYR_FRONT);
    break;
  case VAL:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VAL_FRONT);
    break;
  default:
    current_card = ILE;
    break;
  }

  GRect bounds = layer_get_bounds(window_get_root_layer(window));
  image_layer_front = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(image_layer_front, image_front);
  bitmap_layer_set_alignment(image_layer_front, GAlignCenter);
  layer_add_child(window_get_root_layer(window), (Layer*)image_layer_front);
}

void free_card_image(void) {
  gbitmap_destroy(image_front);
  bitmap_layer_destroy(image_layer_front);
}

void init_card_text(void) {
  // Create the various text layers
  card_back.full_name  = text_layer_create(GRect(0, 30, 150, 32));
  card_back.tla_name   = text_layer_create(GRect(0, 55, 150, 32));
  card_back.polarized  = text_layer_create(GRect(0, 88, 150, 28));
  card_back.func_group = text_layer_create(GRect(0, 118, 150, 28));
  card_back.pKa        = text_layer_create(GRect(0, 140, 150, 28));

  // Set text colors
  text_layer_set_text_color(card_back.full_name, GColorBlack);
  text_layer_set_text_color(card_back.tla_name, GColorBlack);
  text_layer_set_text_color(card_back.polarized, GColorBlack);
  text_layer_set_text_color(card_back.func_group, GColorBlack);
  text_layer_set_text_color(card_back.pKa, GColorBlack);

  // Set background colors
  text_layer_set_background_color(card_back.full_name, GColorClear);
  text_layer_set_background_color(card_back.tla_name, GColorClear);
  text_layer_set_background_color(card_back.polarized, GColorClear);
  text_layer_set_background_color(card_back.func_group, GColorClear);
  text_layer_set_background_color(card_back.pKa, GColorClear);

  // Set fonts
  text_layer_set_font(card_back.full_name, fonts_get_system_font(FONT_KEY_GOTHIC_28_BOLD));
  text_layer_set_font(card_back.tla_name, fonts_get_system_font(FONT_KEY_GOTHIC_28));
  text_layer_set_font(card_back.polarized, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_font(card_back.func_group, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_font(card_back.pKa, fonts_get_system_font(FONT_KEY_GOTHIC_24));

  // Text alignment
  text_layer_set_text_alignment(card_back.full_name, GTextAlignmentCenter);
  text_layer_set_text_alignment(card_back.tla_name, GTextAlignmentCenter);
  text_layer_set_text_alignment(card_back.polarized, GTextAlignmentCenter);
  text_layer_set_text_alignment(card_back.func_group, GTextAlignmentCenter);
  text_layer_set_text_alignment(card_back.pKa, GTextAlignmentCenter);

  // Add as child layers to window root
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.full_name);
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.tla_name);
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.polarized);
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.func_group);
  layer_add_child(window_get_root_layer(window), (Layer*)card_back.pKa);
}

void show_card_text(void) {
  layer_set_hidden((Layer*)card_back.full_name, false);
  layer_set_hidden((Layer*)card_back.tla_name, false);
  layer_set_hidden((Layer*)card_back.polarized, false);
  layer_set_hidden((Layer*)card_back.func_group, false);
  layer_set_hidden((Layer*)card_back.pKa, false);
}

void hide_card_text(void) {
  layer_set_hidden((Layer*)card_back.full_name, true);
  layer_set_hidden((Layer*)card_back.tla_name, true);
  layer_set_hidden((Layer*)card_back.polarized, true);
  layer_set_hidden((Layer*)card_back.func_group, true);
  layer_set_hidden((Layer*)card_back.pKa, true);
}

void load_card_text(enum amino_acid_t aa) {
  text_layer_set_text(card_back.full_name, aa_full_name[aa]);
  text_layer_set_text(card_back.tla_name, aa_tla_name[aa]);
  text_layer_set_text(card_back.polarized, aa_polarized[aa]);
  text_layer_set_text(card_back.func_group, aa_func_group[aa]);
  text_layer_set_text(card_back.pKa, aa_pKa[aa]);
}

void reset_card_used(void) {
  for (uint8_t i = NUMBER_OF_CARDS; i; --i) {
    card_used[NUMBER_OF_CARDS - i] = false;
  }

  card_counter = NUMBER_OF_CARDS;
  srand(time(NULL));
}
