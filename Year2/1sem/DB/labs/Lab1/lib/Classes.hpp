#pragma once
#include <string.h>
#include <iostream>

#define SURNAME_LEN 20
#define CITY_LEN 20
#define DETAIL_NAME_LEN 20
#define COLOR_NAME_LEN 10
struct provider
{
    int code;
    char sur[SURNAME_LEN];
    char city[CITY_LEN];

    provider(int key, char *surname, char *city)
    {
        this->code = key;
        strcpy(this->city, city);
        strcpy(this->sur, surname);
    }
    provider(int key, const char *surname, const char *city)
    {
        this->code = key;
        strcpy(this->city, city);
        strcpy(this->sur, surname);
    }
    provider() = default;
};

struct _provider_dev
{
    provider master;

    int delivery_count = 0;
    long first_delivery = -1;
    int position;

    unsigned char to_del = 0;

    _provider_dev(provider p) : master(p) {}
    _provider_dev() = default;
};

struct detail
{
    int code;
    char name[DETAIL_NAME_LEN];
    int mas;
    char color[COLOR_NAME_LEN];
    char city[CITY_LEN];

    unsigned char to_del = 0;

    detail(int key, char *name, int mas, char *color, char *city)
    {
        this->code = key;
        strcpy(this->city, city);
        this->mas = mas;
        strcpy(this->color, color);
        strcpy(this->name, name);
    }

    detail(int key, const char *name, int mas, const char *color, const char *city)
    {
        this->code = key;
        strcpy(this->city, city);
        this->mas = mas;
        strcpy(this->color, color);
        strcpy(this->name, name);
    }
    detail() = default;
};

struct _detail_dev
{
    detail master;

    int detail_count = 0;
    long first_detail = -1;
    int position;

    unsigned char to_del = 0;

    _detail_dev(detail d) : master(d) {}
    _detail_dev() = default;
};

struct delivery
{
    int code_p;
    int code_d;
    int quantity;
    int price;

    delivery(int provider_code, int detail_code, int _quantity, int _price) : code_p(provider_code),
                                                                              code_d(detail_code), quantity(_quantity), price(_price) {}
    delivery() = default;
};

struct _delivery_dev
{
    delivery master;
    int next_ind = -1;
    int prev_ind = -1;
    int index = -1;
    char is_first = -1;

    _delivery_dev(delivery del) : master(del) {}
    _delivery_dev() = default;
};
