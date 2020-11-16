#pragma once
#include <string>
#include<iostream>
#include"date.h"
#include "exception_input.h"

void is_double(std::istream&, double*);

void is_correct_string(std::istream&, std::string&, int);

void is_int(std::istream&, int*, int, int);

void is_name(std::istream&, std::string&, int);

void is_date(std::istream&, int*, int*, int*);