#ifndef FONT_H
#define FONT_H

#define CHARACTER_HEIGHT 5
#define CHARACTER_WIDTH 4

const static uint8_t SPECIAL_CHARS[][CHARACTER_HEIGHT]
{
    {// \200
     0b1111,
     0b1111,
     0b1110,
     0b1100,
     0b1000},
    {// \201
     0b0011,
     0b0111,
     0b1110,
     0b1100,
     0b1000},
    {// \202
     0b0111,
     0b0111,
     0b0111,
     0b0111,
     0b0111},
    {// \203
     0b0001,
     0b0011,
     0b0111,
     0b1111,
     0b1111},
    {// \204
     0b1000,
     0b1100,
     0b1110,
     0b1111,
     0b1111},
    {// \205
     0b1001,
     0b0000,
     0b0000,
     0b1001,
     0b0110},
};

const static uint8_t INTEGER_MAPPING[10][CHARACTER_HEIGHT]
{
    {// 0
     0b0110,
     0b1011,
     0b1011,
     0b1101,
     0b0110},
    {// 1
     0b0110,
     0b1110,
     0b0010,
     0b0010,
     0b1111},
    {// 2
     0b0110,
     0b1001,
     0b0010,
     0b0100,
     0b1111},
    {// 3
     0b1111,
     0b0001,
     0b0010,
     0b1001,
     0b0110},
    {// 4
     0b0101,
     0b1001,
     0b1111,
     0b0001,
     0b0001},
    {// 5
     0b1111,
     0b1000,
     0b1110,
     0b0001,
     0b1110},
    {// 6
     0b0110,
     0b1000,
     0b1110,
     0b1001,
     0b0110},
    {// 7
     0b1111,
     0b0001,
     0b0010,
     0b0100,
     0b1000},
    {// 8
     0b0110,
     0b1001,
     0b0110,
     0b1001,
     0b0110},
    {// 9
     0b0110,
     0b1001,
     0b0111,
     0b0001,
     0b0110},
};


const static uint8_t PUNCTUATION[][CHARACTER_HEIGHT] = {
    {//
     0b0000,
     0b0000,
     0b0000,
     0b0000,
     0b0000},
    {// //
     0b0011,
     0b0010,
     0b0110,
     0b0100,
     0b1100},
    {// \\.
     0b1100,
     0b0100,
     0b0110,
     0b0010,
     0b0011},
    {// >>
     0b1100,
     0b0110,
     0b0011,
     0b0110,
     0b1100},
    {// <<
     0b0011,
     0b0110,
     0b1100,
     0b0110,
     0b0011},
    {// :
     0b0000,
     0b0100,
     0b0000,
     0b0100,
     0b0000},
    {// ||
     0b0110,
     0b0110,
     0b0110,
     0b0110,
     0b0110},
    {// !
     0b0110,
     0b0110,
     0b0110,
     0b0000,
     0b0110},
    {// (
     0b0110,
     0b1100,
     0b1100,
     0b1100,
     0b0110},
    {// )
     0b0110,
     0b0011,
     0b0011,
     0b0011,
     0b0110},
    {// -
     0b0000,
     0b0000,
     0b0110,
     0b0000,
     0b0000},
    {// +
     0b0000,
     0b0100,
     0b1110,
     0b0100,
     0b0000},
    {// .
     0b0000,
     0b0000,
     0b0000,
     0b0000,
     0b0100},
    {// '
     0b0100,
     0b0100,
     0b0000,
     0b0000,
     0b0000},
    {// ?
     0b1110,
     0b0001,
     0b0110,
     0b0000,
     0b0100},
};

const static uint8_t CHARACTER_MAPPING[26][CHARACTER_HEIGHT] = {
    {// A
     0b0110,
     0b1001,
     0b1111,
     0b1001,
     0b1001},
    {// B
     0b1110,
     0b1001,
     0b1110,
     0b1001,
     0b1110},
    {// C
     0b0111,
     0b1000,
     0b1000,
     0b1000,
     0b0111},
    {// D
     0b1110,
     0b1001,
     0b1001,
     0b1001,
     0b1110},
    {// E
     0b1111,
     0b1000,
     0b1110,
     0b1000,
     0b1111},
    {// F
     0b1111,
     0b1000,
     0b1110,
     0b1000,
     0b1000},
    {// G
     0b1111,
     0b1000,
     0b1011,
     0b1001,
     0b1111},
    {// H
     0b1001,
     0b1001,
     0b1111,
     0b1001,
     0b1001},
    {// I
     0b0111,
     0b0010,
     0b0010,
     0b0010,
     0b0111},
    {// J
     0b1111,
     0b0010,
     0b0010,
     0b1010,
     0b1110},
    {// K
     0b1001,
     0b1010,
     0b1100,
     0b1010,
     0b1001},
    {// L
     0b1000,
     0b1000,
     0b1000,
     0b1000,
     0b1111},
    {// M
     0b1001,
     0b1111,
     0b1101,
     0b1001,
     0b1001},
    {// N
     0b1001,
     0b1101,
     0b1101,
     0b1011,
     0b1001},
    {// O
     0b0110,
     0b1001,
     0b1001,
     0b1001,
     0b0110},
    {// P
     0b1110,
     0b1001,
     0b1110,
     0b1000,
     0b1000},
    {// Q
     0b0110,
     0b1001,
     0b1001,
     0b1010,
     0b0101},
    {// R
     0b1110,
     0b1001,
     0b1110,
     0b1010,
     0b1001},
    {// S
     0b0111,
     0b1000,
     0b0110,
     0b0001,
     0b1110},
    {// T
     0b0111,
     0b0010,
     0b0010,
     0b0010,
     0b0010},
    {// U
     0b1001,
     0b1001,
     0b1001,
     0b1001,
     0b0110},
    {// V
     0b1001,
     0b1001,
     0b1001,
     0b0110,
     0b0110},
    {// W
     0b1001,
     0b1001,
     0b1001,
     0b1101,
     0b1010},
    {// X
     0b1001,
     0b1001,
     0b0110,
     0b1001,
     0b1001},
    {// Y
     0b1001,
     0b1001,
     0b0111,
     0b0010,
     0b1100},
    {// Z
     0b1111,
     0b0010,
     0b0100,
     0b1000,
     0b1111}};

#endif