#include "RussianLetters.h"
#include <Wire.h>

// =============================================================================
// Реализация статических членов RussianSymbols
// =============================================================================

const byte RussianSymbols::A_RU[8] = { B00000, B00100, B01010, B10001, B11111, B10001, B10001, B00000 };      // А
const byte RussianSymbols::B_RU[8] = { B00000, B11110, B10001, B11110, B10001, B10001, B11110, B00000 };      // Б
const byte RussianSymbols::V_RU[8] = { B00000, B11110, B10001, B10001, B11110, B10001, B11110, B00000 };      // В
const byte RussianSymbols::G_RU[8] = { B00000, B11111, B10000, B10000, B10000, B10000, B10000, B00000 };      // Г
const byte RussianSymbols::D_RU[8] = { B00000, B01110, B01010, B01010, B01010, B01010, B11111, B10001 };      // Д
const byte RussianSymbols::E_RU[8] = { B00000, B11111, B10000, B11110, B10000, B10000, B11111, B00000 };      // Ё
const byte RussianSymbols::EE_RU[8] = { B01010, B00000, B11111, B10000, B11110, B10000, B11111, B00000};     // Е
const byte RussianSymbols::ZH_RU[8] = { B00000, B10101, B10101, B01110, B10101, B10101, B10101, B00000 };     // Ж
const byte RussianSymbols::Z_RU[8] = { B00000, B01110, B10001, B00010, B00100, B10001, B01110, B00000 };      // З
const byte RussianSymbols::I_RU[8] = { B00000, B10001, B10011, B10101, B11001, B10001, B10001, B00000 };      // И
const byte RussianSymbols::II_RU[8] = { B01010, B10001, B10011, B10101, B11001, B10001, B10001, B00000 };     // Й
const byte RussianSymbols::K_RU[8] = { B00000, B10001, B10010, B10100, B11000, B10100, B10010, B00000 };      // К
const byte RussianSymbols::L_RU[8] = { B00000, B00111, B01001, B01001, B01001, B01001, B10001, B00000 };      // Л
const byte RussianSymbols::M_RU[8] = { B00000, B10001, B11011, B10101, B10001, B10001, B10001, B00000 };      // М
const byte RussianSymbols::N_RU[8] = { B00000, B10001, B10001, B11111, B10001, B10001, B10001, B00000 };      // Н
const byte RussianSymbols::O_RU[8] = { B00000, B01110, B10001, B10001, B10001, B10001, B01110, B00000 };      // О
const byte RussianSymbols::P_RU[8] = { B00000, B11111, B10001, B10001, B10001, B10001, B10001, B00000 };      // П
const byte RussianSymbols::R_RU[8] = { B00000, B11110, B10001, B10001, B11110, B10000, B10000, B00000 };      // Р
const byte RussianSymbols::S_RU[8] = { B00000, B01110, B10001, B10000, B10000, B10001, B01110, B00000 };      // С
const byte RussianSymbols::T_RU[8] = { B00000, B11111, B00100, B00100, B00100, B00100, B00100, B00000 };      // Т
const byte RussianSymbols::U_RU[8] = { B00000, B10001, B10001, B10001, B01111, B00001, B01110, B00000 };      // У
const byte RussianSymbols::F_RU[8] = { B00000, B10001, B10001, B10001, B11111, B10001, B10001, B00000 };      // Ф
const byte RussianSymbols::H_RU[8] = { B00000, B10001, B10001, B01010, B00100, B00100, B00100, B00000 };      // Х
const byte RussianSymbols::C_RU[8] = { B00000, B10001, B10001, B10001, B10001, B10001, B01110, B00000 };      // Ц
const byte RussianSymbols::CH_RU[8] = { B00000, B10001, B10001, B10001, B01111, B00001, B00001, B00000 };     // Ч
const byte RussianSymbols::SH_RU[8] = { B00000, B10101, B10101, B10101, B10101, B10101, B11111, B00000 };     // Ш
const byte RussianSymbols::SHH_RU[8] = { B00000, B10101, B10101, B10101, B10101, B10101, B11111, B00001 };    // Щ
const byte RussianSymbols::TV_RU[8] = { B00000, B11000, B01000, B01000, B01110, B01001, B01110, B00000 };     // Ъ
const byte RussianSymbols::Y_RU[8] = { B00000, B10001, B10001, B10001, B11001, B10101, B11001, B00000 };      // Ы
const byte RussianSymbols::MY_RU[8] = { B00000, B10000, B10000, B11110, B10001, B10001, B11110, B00000 };     // Ь
const byte RussianSymbols::EEE_RU[8] = { B00000, B01110, B10001, B11111, B10000, B10001, B01110, B00000 };     // Э
const byte RussianSymbols::UU_RU[8] = { B00000, B10001, B10001, B10001, B11001, B10101, B11001, B00000 };     // Ю
const byte RussianSymbols::YA_RU[8] = { B00000, B01111, B10001, B10001, B01111, B00101, B01001, B00000 };     // Я

// =============================================================================
// Таблица преобразования UTF-8 -> кастомные символы
// =============================================================================

// Структура для таблицы символов
struct SymbolMap {
  uint8_t utf8_byte1;
  uint8_t utf8_byte2;
  uint8_t cgram_slot;
  const byte* symbol_data;
};

// Таблица преобразования русских букв
static const SymbolMap russian_symbols[] = {
  // Заглавные буквы
  {0xD0, 0x90, 0, RussianSymbols::A_RU},    // А
  {0xD0, 0x91, 1, RussianSymbols::B_RU},    // Б
  {0xD0, 0x92, 2, RussianSymbols::V_RU},    // В
  {0xD0, 0x93, 3, RussianSymbols::G_RU},    // Г
  {0xD0, 0x94, 4, RussianSymbols::D_RU},    // Д
  {0xD0, 0x95, 5, RussianSymbols::EE_RU},   // Е
  {0xD1, 0x91, 6, RussianSymbols::E_RU},    // Ё
  {0xD0, 0x96, 7, RussianSymbols::ZH_RU},   // Ж
  // Добавьте остальные буквы по аналогии...
  {0xD0, 0x97, 0, RussianSymbols::Z_RU},    // З - будет перезаписывать слот 0
  {0xD0, 0x98, 1, RussianSymbols::I_RU},    // И
  {0xD0, 0x99, 2, RussianSymbols::II_RU},   // Й
  {0xD0, 0x9A, 3, RussianSymbols::K_RU},    // К
  {0xD0, 0x9B, 4, RussianSymbols::L_RU},    // Л
  {0xD0, 0x9C, 5, RussianSymbols::M_RU},    // М
  {0xD0, 0x9D, 6, RussianSymbols::N_RU},    // Н
  {0xD0, 0x9E, 7, RussianSymbols::O_RU},    // О
  // Продолжение для остальных букв...
  {0xD0, 0x9F, 0, RussianSymbols::P_RU},    // П
  {0xD0, 0xA0, 1, RussianSymbols::R_RU},    // Р
  {0xD0, 0xA1, 2, RussianSymbols::S_RU},    // С
  {0xD0, 0xA2, 3, RussianSymbols::T_RU},    // Т
  {0xD0, 0xA3, 4, RussianSymbols::U_RU},    // У
  {0xD0, 0xA4, 5, RussianSymbols::F_RU},    // Ф
  {0xD0, 0xA5, 6, RussianSymbols::H_RU},    // Х
  {0xD0, 0xA6, 7, RussianSymbols::C_RU},    // Ц
  {0xD0, 0xA7, 0, RussianSymbols::CH_RU},   // Ч
  {0xD0, 0xA8, 1, RussianSymbols::SH_RU},   // Ш
  {0xD0, 0xA9, 2, RussianSymbols::SHH_RU},  // Щ
  {0xD0, 0xAA, 3, RussianSymbols::TV_RU},   // Ъ
  {0xD0, 0xAB, 4, RussianSymbols::Y_RU},    // Ы
  {0xD0, 0xAC, 5, RussianSymbols::MY_RU},   // Ь
  {0xD0, 0xAD, 6, RussianSymbols::EEE_RU},  // Э
  {0xD0, 0xAE, 7, RussianSymbols::UU_RU},   // Ю
  {0xD0, 0xAF, 0, RussianSymbols::YA_RU},   // Я
};

static const uint8_t SYMBOLS_COUNT = sizeof(russian_symbols) / sizeof(SymbolMap);

// =============================================================================
// Реализация класса RussianLCD
// =============================================================================

RussianLCD::RussianLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) 
  : LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows), 
    utf8_state(0), 
    current_byte1(0),
    next_slot(0) {
  
  // Инициализируем таблицу загруженных символов
  for (uint8_t i = 0; i < 8; i++) {
    loaded_symbols[i] = 0xFF; // 0xFF означает, что слот пуст
  }
}

void RussianLCD::begin() {
  LiquidCrystal_I2C::begin();
  backlight();
  
  // Предзагрузка наиболее частых русских букв
  preloadCommonSymbols();
}

void RussianLCD::begin(uint8_t cols, uint8_t rows) {
  LiquidCrystal_I2C::begin(cols, rows);
  backlight();
  preloadCommonSymbols();
}

void RussianLCD::preloadCommonSymbols() {
  // Предзагрузка самых частых русских букв
  const uint8_t common_symbols[] = {0, 5, 8, 13, 14, 16, 17, 18}; // А, Е, И, Н, О, Р, С, Т
  for (uint8_t i = 0; i < 8 && i < sizeof(common_symbols); i++) {
    loadSymbol(i, russian_symbols[common_symbols[i]].symbol_data);
    loaded_symbols[i] = common_symbols[i];
  }
  next_slot = 0; // Начинаем с первого слота для новых символов
}

uint8_t RussianLCD::findSymbolInCache(uint8_t byte1, uint8_t byte2) {
  for (uint8_t i = 0; i < SYMBOLS_COUNT; i++) {
    if (russian_symbols[i].utf8_byte1 == byte1 && russian_symbols[i].utf8_byte2 == byte2) {
      // Проверяем, загружен ли уже этот символ
      for (uint8_t j = 0; j < 8; j++) {
        if (loaded_symbols[j] == i) {
          return russian_symbols[i].cgram_slot;
        }
      }
      // Символ не загружен - загружаем его
      return loadNewSymbol(i);
    }
  }
  return 0xFF; // Символ не найден
}

uint8_t RussianLCD::loadNewSymbol(uint8_t symbol_index) {
  if (symbol_index >= SYMBOLS_COUNT) return 0xFF;
  
  // Используем следующий доступный слот
  uint8_t slot = next_slot;
  
  // Загружаем символ в CGRAM
  loadSymbol(slot, russian_symbols[symbol_index].symbol_data);
  
  // Обновляем таблицу загруженных символов
  loaded_symbols[slot] = symbol_index;
  
  // Переходим к следующему слоту (циклически)
  next_slot = (next_slot + 1) % 8;
  
  return slot;
}

void RussianLCD::loadSymbol(uint8_t slot, const byte* symbol_data) {
  if (slot > 7) return;
  
  createChar(slot, (uint8_t*)symbol_data);
}

size_t RussianLCD::write(uint8_t value) {
  // Обработка UTF-8 последовательностей для русских букв
  if (utf8_state == 0) {
    if (value == 0xD0 || value == 0xD1) {
      // Первый байт русской буквы в UTF-8
      current_byte1 = value;
      utf8_state = 1;
      return 1;
    } else {
      // Обычный ASCII символ
      utf8_state = 0;
      return LiquidCrystal_I2C::write(value);
    }
  } else if (utf8_state == 1) {
    // Второй байт UTF-8 последовательности
    uint8_t byte2 = value;
    utf8_state = 0;
    
    // Ищем символ в кэше или загружаем его
    uint8_t custom_char = findSymbolInCache(current_byte1, byte2);
    
    if (custom_char != 0xFF) {
      // Выводим кастомный символ
      return LiquidCrystal_I2C::write(custom_char);
    } else {
      // Символ не найден - выводим заглушку
      return LiquidCrystal_I2C::write('?');
    }
  }
  
  return LiquidCrystal_I2C::write(value);
}

void RussianLCD::printRussian(const char* str) {
  printRussian((const unsigned char*)str);
}

void RussianLCD::printRussian(const unsigned char* str) {
  utf8_state = 0; // Сбрасываем состояние UTF-8
  
  while (*str) {
    write(*str);
    str++;
  }
}

void RussianLCD::setCursorRU(uint8_t col, uint8_t row) {
  setCursor(col, row);
}

void RussianLCD::clearRU() {
  clear();
}

// =============================================================================
// Упрощенная версия для начинающих
// =============================================================================

SimpleRussianLCD::SimpleRussianLCD(uint8_t lcd_addr, uint8_t lcd_cols, uint8_t lcd_rows) 
  : LiquidCrystal_I2C(lcd_addr, lcd_cols, lcd_rows) {}

void SimpleRussianLCD::begin() {
  LiquidCrystal_I2C::begin();
  backlight();
  loadRussianSymbols();
}

void SimpleRussianLCD::loadRussianSymbols() {
  // Загружаем фиксированный набор из 8 самых частых русских букв
  createChar(0, (uint8_t*)RussianSymbols::A_RU);   // А
  createChar(1, (uint8_t*)RussianSymbols::EE_RU);  // Е  
  createChar(2, (uint8_t*)RussianSymbols::I_RU);   // И
  createChar(3, (uint8_t*)RussianSymbols::N_RU);   // Н
  createChar(4, (uint8_t*)RussianSymbols::O_RU);   // О
  createChar(5, (uint8_t*)RussianSymbols::R_RU);   // Р
  createChar(6, (uint8_t*)RussianSymbols::S_RU);   // С
  createChar(7, (uint8_t*)RussianSymbols::T_RU);   // Т
}

void SimpleRussianLCD::printRU(const char* str) {
  // Простая реализация для фиксированного набора символов
  while (*str) {
    if (*str == (unsigned char)0xD0) {
      // Обрабатываем русские буквы
      str++;
      switch (*str) {
        case 0x90: write(0); break; // А
        case 0x95: write(1); break; // Е
        case 0x98: write(2); break; // И
        case 0x9D: write(3); break; // Н
        case 0x9E: write(4); break; // О
        case 0xA0: write(5); break; // Р
        case 0xA1: write(6); break; // С
        case 0xA2: write(7); break; // Т
        default: write('?'); break;
      }
    } else {
      // Обычные ASCII символы
      write(*str);
    }
    str++;
  }
}

void SimpleRussianLCD::setCursorRU(uint8_t col, uint8_t row) {
  setCursor(col, row);
}