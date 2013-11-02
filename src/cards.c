#include "cards.h"

// Enums
enum side_et {
  FRONT, BACK
};

enum card_et {
  ILE = 0, ALA, ARG, ASP, CYS,
  GLU, GLY, HIS, LEU, LYS,
  MET, GLN, PHE, PRO, SER,
  THR, TRP, ASN, TYR, VAL
};

// Globals
static enum side_et current_side;
static enum card_et current_card;
static Window *window;
static Layer *window_layer;
static GBitmap *image_front;
static GBitmap *image_back;
static BitmapLayer *image_layer_front;
static BitmapLayer *image_layer_back;

// Private functions
static void load_card(void);
static void load_card_images(void);
static void free_card_images(void);

void init_cards(Window *main_window,
                GBitmap *main_image_front,
                GBitmap *main_image_back,
                BitmapLayer *main_image_layer_front,
                BitmapLayer *main_image_layer_back)
{
  current_side = FRONT;
  current_card = ILE;
  window = main_window;
  window_layer = window_get_root_layer(window);
  image_front = main_image_front;
  image_back = main_image_back;
  image_layer_front = main_image_layer_front;
  image_layer_back = main_image_layer_back;
  load_card();
}

void deinit_cards(void) {
  free_card_images();
}

void flip_card(void) {
  if(current_side == FRONT) {
    layer_set_hidden(bitmap_layer_get_layer(image_layer_front), true);
    layer_set_hidden(bitmap_layer_get_layer(image_layer_back), false);
    current_side = BACK;
  } else {
    layer_set_hidden(bitmap_layer_get_layer(image_layer_back), true);
    layer_set_hidden(bitmap_layer_get_layer(image_layer_front), false);
    current_side = FRONT;
  }
}

void next_card(void) {
  free_card_images();

  if (++current_card == TOTAL_CARDS) {
    current_card = 0;
  }

  load_card();
}

void prev_card(void) {
  free_card_images();

  if (current_card == 0) {
    current_card = TOTAL_CARDS;
  }
  --current_card;

  load_card();
}

void load_card(void) {
  layer_remove_child_layers(window_layer);
  load_card_images();
  GRect bounds = layer_get_bounds(window_layer);
  image_layer_front = bitmap_layer_create(bounds);
  image_layer_back = bitmap_layer_create(bounds);
  bitmap_layer_set_bitmap(image_layer_front, image_front);
  bitmap_layer_set_alignment(image_layer_front, GAlignCenter);
  layer_add_child(window_layer, bitmap_layer_get_layer(image_layer_front));
  bitmap_layer_set_bitmap(image_layer_back, image_back);
  bitmap_layer_set_alignment(image_layer_back, GAlignCenter);
  layer_add_child(window_layer, bitmap_layer_get_layer(image_layer_back));
  layer_set_hidden(bitmap_layer_get_layer(image_layer_back), true);
}

void load_card_images(void) {
  switch(current_card) {
  case ILE:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ILE_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ILE_BACK);
    break;
  case ALA:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ALA_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ALA_BACK);
    break;
  case ARG:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARG_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ARG_BACK);
    break;
  case ASP:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASP_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASP_BACK);
    break;
  case CYS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CYS_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_CYS_BACK);
    break;
  case GLU:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLU_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLU_BACK);
    break;
  case GLY:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLY_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLY_BACK);
    break;
  case HIS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HIS_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_HIS_BACK);
    break;
  case LEU:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LEU_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LEU_BACK);
    break;
  case LYS:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LYS_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_LYS_BACK);
    break;
  /*
  case MET:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MET_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_MET_BACK);
    break;
  case GLN:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLN_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_GLN_BACK);
    break;
  case PHE:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PHE_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PHE_BACK);
    break;
  case PRO:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PRO_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_PRO_BACK);
    break;
  case SER:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SER_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_SER_BACK);
    break;
  case THR:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_THR_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_THR_BACK);
    break;
  case TRP:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRP_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TRP_BACK);
    break;
  case ASN:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASN_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_ASN_BACK);
    break;
  case TYR:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TYR_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_TYR_BACK);
    break;
  case VAL:
    image_front = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VAL_FRONT);
    image_back = gbitmap_create_with_resource(RESOURCE_ID_IMAGE_VAL_BACK);
    break;
  */
  default:
    current_card = ILE;
    break;
  }
}

void free_card_images(void) {
  gbitmap_destroy(image_front);
  gbitmap_destroy(image_back);
  bitmap_layer_destroy(image_layer_front);
  bitmap_layer_destroy(image_layer_back);
}

