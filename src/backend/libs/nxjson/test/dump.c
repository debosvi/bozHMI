
#include "nxjson_test.h"

void dump(const nx_json* json, char* out, char** end, int indent) {
  if (!json) {
    *end=out;
    return;
  }
  int i;
  for (i=0; i<indent; i++) *out++=' ';
  if (json->key) {
    strcpy(out, json->key);
    out+=strlen(json->key);
    *out++=':';
  }
  switch (json->type) {
    case NX_JSON_NULL:
      strcpy(out, "null");
      out+=4;
      break;
    case NX_JSON_OBJECT:
      *out++='{';
      *out++='\n';
      {
        nx_json* js=json->child;
        for (js=json->child; js; js=js->next) {
          dump(js, out, &out, indent+2);
        }
      }
      for (i=0; i<indent; i++) *out++=' ';
      *out++='}';
      break;
    case NX_JSON_ARRAY:
      *out++='[';
      *out++='\n';
      {
        nx_json* js=json->child;
        for (js=json->child; js; js=js->next) {
          dump(js, out, &out, indent+2);
        }
      }
      for (i=0; i<indent; i++) *out++=' ';
      *out++=']';
      break;
    case NX_JSON_STRING:
      *out++='"';
      strcpy(out, json->text_value);
      out+=strlen(json->text_value);
      *out++='"';
      break;
    case NX_JSON_INTEGER:
      out+=sprintf(out, "%ld", json->int_value);
      break;
    case NX_JSON_DOUBLE:
      out+=sprintf(out, "%le", json->dbl_value);
      break;
    case NX_JSON_BOOL:
      *out++=json->int_value?'T':'F';
      break;
    default:
      strcpy(out, "????");
      out+=4;
      break;
  }
  *out++='\n';
  *end=out;
}
