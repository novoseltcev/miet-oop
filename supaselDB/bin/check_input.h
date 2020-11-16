#pragma once
#include<iostream>
#include <string>

void is_double(std::istream&, double*);

void is_correct_string(std::istream&, std::string&, int);

void is_int(std::istream&, int*, int, int);

void is_name(std::istream&, std::string&, int);

void is_date(std::istream&, int*, int*, int*);