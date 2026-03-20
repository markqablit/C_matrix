#pragma once

#include "string.h"
#include "matrix.h"

int type_select();
int action_select();

void interface();

void clear_input_buffer();
void print_error(ErrorCode err);