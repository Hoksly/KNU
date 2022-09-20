#include <string.h>
#include <iostream>
#pragma once
#define SURNAME_LEN 20
#define CITY_LEN 20
#define DETAIL_NAME_LEN 20
#define COLOR_NAME_LEN 10
struct provider
{
    int code_p;
    char sur[SURNAME_LEN];
    char city[CITY_LEN];

    provider(int key, char *surname, char *city)
    {
        this->code_p = key;
        strcpy(this->city, city);
        strcpy(this->sur, surname);
    }
    provider(int key, const char *surname, const char *city)
    {
        this->code_p = key;
        strcpy(this->city, city);
        strcpy(this->sur, surname);
    }
    provider() = default;
};

struct _provider_dev
{
    provider pv;

    int delivery_count = 0;
    long first_delivery = -1;
    int position;

    unsigned char to_del = 0;

    _provider_dev(provider p) : pv(p) {}
    _provider_dev() = default;
};

struct detail
{
    int code_d;
    char name[DETAIL_NAME_LEN];
    int mas;
    char color[COLOR_NAME_LEN];
    char city[CITY_LEN];

    unsigned char to_del = 0;

    detail(int key, char *name, int mas, char *color, char *city)
    {
        this->code_d = key;
        strcpy(this->city, city);
        this->mas = mas;
        strcpy(this->color, color);
        strcpy(this->name, name);
    }

    detail(int key, const char *name, int mas, const char *color, const char *city)
    {
        this->code_d = key;
        strcpy(this->city, city);
        this->mas = mas;
        strcpy(this->color, color);
        strcpy(this->name, name);
    }
    detail() = default;
};

struct delivery
{
    int code_p;
    int code_d;
    int quantity;
    int price;

    delivery(int a, int b, int c, int d) : code_p(a), code_d(b), quantity(c), price(d) {}
    delivery() = default;
};

struct _delivery_dev
{
    delivery dv;
    int next_ind = -1;
    int prev_ind = -1;
};
