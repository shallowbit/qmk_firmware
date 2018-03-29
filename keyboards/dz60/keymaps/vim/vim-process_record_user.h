case VIM_A: {
  SHIFTED ? VIM_APPEND_LINE() : VIM_APPEND(); }
  return false;
}
case VIM_B: {
    switch(VIM_QUEUE) {
      case KC_NO: VIM_BACK(); break;
      case VIM_C: VIM_CHANGE_BACK(); break;
      case VIM_D: VIM_DELETE_BACK(); break;
      case VIM_V: VIM_VISUAL_BACK(); break;
    }
  }
  return false;
}
case VIM_C: {
    switch(VIM_QUEUE) {
      case KC_NO: SHIFTED ? VIM_CHANGE_LINE() : VIM_LEADER(VIM_C); break;
      case VIM_C: VIM_CHANGE_WHOLE_LINE(); break;
    }
  }
  return false;
}
case VIM_D: {
    switch(VIM_QUEUE) {
      case KC_NO: SHIFTED ? VIM_DELETE_LINE() : VIM_LEADER(VIM_D); break;
      case VIM_D: VIM_DELETE_WHOLE_LINE(); break;
    }
  }
  return false;
}
case VIM_E: {
    switch (VIM_QUEUE) {
      case KC_NO: VIM_END(); break;
      case VIM_C: VIM_CHANGE_END(); break;
      case VIM_D: VIM_DELETE_END(); break;
      case VIM_V: VIM_VISUAL_END(); break;
    }
  }
  return false;
}
case VIM_H: {
    switch (VIM_QUEUE) {
      case KC_NO: VIM_LEFT(); break;
      case VIM_C: VIM_CHANGE_LEFT(); break;
      case VIM_D: VIM_DELETE_LEFT(); break;
      case VIM_V: VIM_VISUAL_LEFT(); break;
    }
  }
  return false;
}
case VIM_I: {
    switch (VIM_QUEUE) {
      case KC_NO: layer_on(INSERT_MODE); break;
      case VIM_C: VIM_LEADER(VIM_CI); break;
      case VIM_D: VIM_LEADER(VIM_DI); break;
      case VIM_V: VIM_LEADER(VIM_VI); break;
    }
  }
  return false;
}
case VIM_J: {
    switch (VIM_QUEUE) {
      case KC_NO: SHIFTED ? VIM_JOIN() : VIM_DOWN(); break;
      case VIM_C: VIM_CHANGE_DOWN(); break;
      case VIM_D: VIM_DELETE_DOWN(); break;
      case VIM_V: VIM_VISUAL_DOWN(); break;
    }
  }
  return false;
}
case VIM_K: {
    switch (VIM_QUEUE) {
      case KC_NO: VIM_UP(); break;
      case VIM_C: VIM_CHANGE_UP(); break;
      case VIM_D: VIM_DELETE_UP(); break;
      case VIM_V: VIM_VISUAL_UP(); break;
    }
  }
  return false;
}
case VIM_L: {
    switch (VIM_QUEUE) {
      case KC_NO: VIM_RIGHT(); break;
      case VIM_C: VIM_CHANGE_RIGHT(); break;
      case VIM_D: VIM_DELETE_RIGHT(); break;
      case VIM_V: VIM_VISUAL_RIGHT(); break;
    }
  }
  return false;
}
case VIM_O: {
  SHIFTED ? VIM_OPEN_ABOVE() : VIM_OPEN();
  return false;
}
case VIM_P: {
  SHIFTED ? VIM_PUT_BEFORE() : VIM_PUT();
  return false;
}
case VIM_S: {
  SHIFTED ? VIM_CHANGE_WHOLE_LINE() : VIM_SUBSTITUTE();
  return false;
}
case VIM_U: {
  VIM_UNDO();
  return false;
}
case VIM_V: {
  VIM_LEADER(VIM_V);
  return false;
}
case VIM_W: {
    switch (VIM_QUEUE) {
      case KC_NO: VIM_WORD(); break;
      case VIM_C: VIM_CHANGE_WORD(); break;
      case VIM_CI: VIM_CHANGE_INNER_WORD(); break;
      case VIM_D: VIM_DELETE_WORD(); break;
      case VIM_DI: VIM_DELETE_INNER_WORD(); break;
      case VIM_V: VIM_VISUAL_WORD(); break;
      case VIM_VI: VIM_VISUAL_INNER_WORD(); break;
    }
  }
  return false;
}
case VIM_X: {
  VIM_CUT();
  return false;
}
case VIM_Y: {
  SHIFTED ? VIM_YANK_LINE() : VIM_YANK();
  return false;
}

// End by clearing the queue unless keycode is a
// if ((record->event.pressed) &&
//     (keycode != VIM_I ||
//     keycode != VIM_C ||
//     keycode != VIM_D ||
//     keycode != VIM_V)) {
//   VIM_LEADER(KC_NO);
// }
