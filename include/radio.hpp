#pragma once
#include "util.hpp"

#include <HardwareSerial.h>

struct __attribute__((__packed__)) Packet {
	// Should be sorted in order of size in order to preserve alignment without
	// wasing space for padding.  The start of the sync sequence should also be
	// an invalid value for the first value listed so that receivers don't get
	// confused and interpret a valid packet as a sync word.
	uint32_t millis;
	float alt, vel, acc, raw_alt, raw_acc, lat, lon, apogee;
	uint16_t temp, batt_v;
	FlightPhase phase;
	uint8_t checksum;

	Packet(FlightPhase phase, uint32_t millis, float alt, float vel, float acc,
			float raw_alt, float raw_acc, float lat, float lon, float apogee,
			int16_t temp, uint16_t batt_v) :
		millis(millis), alt(alt), vel(vel), acc(acc),
		raw_alt(raw_alt), raw_acc(raw_acc), lat(lat), lon(lon), apogee(apogee),
		temp(temp), batt_v(batt_v), phase(phase), checksum(0)
	{
		checksum = struct_checksum(*this);
	}

	size_t getLen() const { return sizeof(Packet); }
};

static_assert(sizeof(Packet) == 42, "Packet size changed.");
static_assert(sizeof(Packet) <= SERIAL_TX_BUFFER_SIZE,
		"Packet should fit within serial TX buffer to minimize delay.");

void radio_setup();
void radio_send(const Packet &p);
