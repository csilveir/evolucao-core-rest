
#include <stdio.h>
#include <ulfius.h>
#include <string.h>
#include <jansson.h>


extern char * print_map(const struct _u_map * map) {
  char * line, * to_return = NULL;
  const char **keys, * value;
  int len, i;
  if (map != NULL) {
    keys = u_map_enum_keys(map);
    for (i=0; keys[i] != NULL; i++) {
      value = u_map_get(map, keys[i]);
      len = snprintf(NULL, 0, "key is %s, value is %s", keys[i], value);
      line = o_malloc((size_t)(len+1));
      snprintf(line, (size_t)(len+1), "key is %s, value is %s", keys[i], value);
      if (to_return != NULL) {
        len = (int)(o_strlen(to_return) + o_strlen(line) + 1);
        to_return = o_realloc(to_return, (size_t)(len+1));
        if (o_strlen(to_return) > 0) {
          strcat(to_return, "\n");
        }
      } else {
        to_return = o_malloc((o_strlen(line) + 1));
        to_return[0] = 0;
      }
      strcat(to_return, line);
      o_free(line);
    }
    return to_return;
  } else {
    return NULL;
  }
}
extern char* getMockData() {

    char * buffer = 0;
    long length;
    FILE * file = fopen("./responses/data.json","rb");

    if (file)
        {
            fseek (file, 0, SEEK_END);
            length = ftell (file);
            fseek (file, 0, SEEK_SET);
            buffer = malloc (length);
            if (buffer)
            {
                fread (buffer, 1, length, file);
            }
            fclose (file);
        }

    return buffer;

}