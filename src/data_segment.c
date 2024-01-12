#include "data_segment.h"
#include <stdio.h>
#include <stdlib.h>

void append_to_data(struct assembly_code *code, char *data) {
  int res;
  if ((res = snprintf(code->data + code->current_data_offset,
                      MAX_DATA_SIZE - code->current_data_offset, "%s", data)) <
      0) {
    fprintf(stderr, "Error: can't append to data\n");
    exit(1);
  }
  code->current_data_offset += res;
}

void write_data_to_file(struct assembly_code *code) {
  fprintf(code->out, "%s", code->data);
}