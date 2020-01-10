#pragma once

#define FLIGHT_FLASH_PAGE_SIZE (256)
#define FLIGHT_FLASH_BLOCK_SIZE (32768)
#define FLIGHT_FLASH_PAGES_PER_BLOCK (FLIGHT_FLASH_BLOCK_SIZE / FLIGHT_FLASH_PAGE_SIZE)
#define FLIGHT_FLASH_PAGE_COUNT (1<<21 / FLIGHT_FLASH_PAGE_SIZE)
#define FLIGHT_FLASH_FLIGHTS (4)
#define FLIGHT_FLASH_FLIGHT_SIZE (FLIGHT_FLASH_PAGE_COUNT / FLIGHT_FLASH_FLIGHTS)

void flash_setup();
void flash_erase(size_t start_page);
void flash_write(size_t page_addr, uint8_t page[FLIGHT_FLASH_PAGE_SIZE]);
void flash_read(size_t page_addr, uint8_t page[FLIGHT_FLASH_PAGE_SIZE]);
bool flash_busy();
